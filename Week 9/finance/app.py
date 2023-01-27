import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

import datetime

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
# API KEY: pk_ef15d5d796234b2987a00c5c55de26c7
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_info = db.execute("SELECT * FROM users WHERE id=?;", session["user_id"])
    user_transactions = db.execute(
        "SELECT symbol, SUM(amount) AS n_shares FROM transactions WHERE user_id = ? GROUP BY symbol;", session["user_id"])
    total_in_stocks = float(user_info[0]["cash"])
    for t in user_transactions:
        symbol_data = lookup(t["symbol"])
        t["name"] = symbol_data["name"]
        t["price"] = symbol_data["price"]
        t["total"] = float(symbol_data["price"]) * int(t["n_shares"])
        total_in_stocks += float(t["total"])

    content = {
        "rows": user_transactions,
        "cash": user_info[0]["cash"],
        "total": total_in_stocks
    }

    return render_template("index.html", content=content)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        symbol = symbol.lower()

        # Ensure symbol and shares were submitted
        if not symbol:
            return apology("Missing Symbol", 400)
        elif lookup(request.form.get("symbol")) == None:
            return apology("Invalid Symbol", 400)
        elif (not shares.isdigit()) or (float(shares) < 0):
            return apology("Invalid amount of Shares", 400)

        # Ensure symbol exist
        symbols = lookup(symbol)
        if symbols:
            user = db.execute("SELECT * FROM users WHERE id=?", session["user_id"])
            user_cash = float(user[0]["cash"])
            total_price = float(symbols["price"]) * float(shares)
            if user_cash >= total_price:
                # Save the transaction in the database and update user cash
                time = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")
                transaction = db.execute("INSERT INTO transactions (user_id, symbol, amount, total_price, time) VALUES (?, ?, ?, ?, ?);",
                                         session["user_id"], symbol, shares, total_price, str(time))
                if transaction:
                    db.execute("UPDATE users SET cash = ? WHERE id = ?;", (user_cash - total_price), session["user_id"])
                    return redirect("/")
                else:
                    return apology("Error on the transaction, try again", 400)
            else:
                return apology("Cant afford", 400)

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    data = db.execute("SELECT * FROM transactions WHERE user_id = ?;", session["user_id"])
    return render_template("history.html", data=data)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Invalid Symbol", 400)
        else:
            q = lookup(request.form.get("symbol"))
            if q:
                content = {
                    "symbol": q["symbol"],
                    "name": q["name"],
                    "price": q["price"]
                }
                return render_template("quoted.html", content=content)
            else:
                return apology("Invalid Symbol", 400)

    return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    if request.method == "POST":
        user = request.form.get("username")
        password1 = request.form.get("password")
        password2 = request.form.get("confirmation")

        # Ensure username was submitted
        if not user:
            return apology("must provide username", 400)

        # Ensure password was submitted and both are equal
        elif not password1:
            return apology("must provide password", 400)
        elif (not password2) or (password1 != password2):
            return apology("The passwords are different", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", user)
        if len(rows) > 0:
            return apology("That username already exist", 400)
        else:
            # Save the new user into de database
            password = generate_password_hash(password1, method='pbkdf2:sha256', salt_length=8)
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", user, password)

            # Log in the user
            user_id = db.execute("SELECT id FROM users where username=?;", user)
            session["user_id"] = int(user_id[0]["id"])
            return redirect("/")

    return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        symbol = symbol.lower()

        # Ensure symbol and shares were submitted
        if not symbol:
            return apology("Missing Symbol", 400)
        elif lookup(request.form.get("symbol")) == "Symbol":
            return apology("Invalid Symbol", 400)
        elif (not shares) or (int(shares) < 0):
            return apology("Invalid amount of Shares", 400)

        # Ensure symbol exist
        symbols = lookup(symbol.lower())
        if symbols:
            user = db.execute(
                "SELECT * FROM users WHERE id=?", session["user_id"])
            user_cash = float(user[0]["cash"])
            total_price = float(symbols["price"]) * int(shares)

            user_shares = db.execute(
                "SELECT SUM(amount) FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol;", session["user_id"], symbol)
            if int(shares) <= user_shares[0]["SUM(amount)"]:
                # Save the transaction in the database and update user cash
                time = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S.%f")
                transaction = db.execute("INSERT INTO transactions (user_id, symbol, amount, total_price, time) VALUES (?, ?, ?, ?, ?);",
                                         session["user_id"], symbol, -abs(int(shares)), total_price, str(time))
                if transaction:
                    db.execute("UPDATE users SET cash = ? WHERE id = ?;", (user_cash + total_price), session["user_id"])
                    return redirect("/")
                else:
                    return apology("Error on the transaction, try again", 400)
            else:
                return apology("Not enough shares", 400)

    user_s = db.execute(
        "SELECT symbol, SUM(amount) AS n_shares FROM transactions WHERE user_id = ? GROUP BY symbol;", session["user_id"])
    user_symbols = []
    for s in user_s:
        if int(s["n_shares"]) > 0:
            user_symbols.append(s["symbol"].upper())
    content = {
        "symbols": user_symbols
    }
    return render_template("sell.html", content=content)