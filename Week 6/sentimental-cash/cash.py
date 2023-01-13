def main():
    # Ask the user how many cents the customer is owed
    cents = get_cents()

    # Calculate the number of quarters to give the customer
    quarters = calculate_quarters(cents)
    cents = cents - quarters * 25

    # Calculate the number of dimes to give the customer
    dimes = calculate_dimes(cents)
    cents = cents - dimes * 10

    # Calculate the number of nickels to give the customer
    nickels = calculate_nickels(cents)
    cents = cents - nickels * 5

    # Calculate the number of pennies to give the customer
    pennies = calculate_pennies(cents)
    cents = cents - pennies * 1

    # Print total number of coins to give the customer
    coins = quarters + dimes + nickels + pennies
    print(int(coins))


def get_cents():
    while True:
        try:
            cents = float(input("Change owed: "))
            if cents > 0:
                # Convert the user input from dollars to cents
                return int(cents * 100)
        except:
            print("Introduce a number bigger than 0")


def calculate_quarters(cents):
    return cents // 25


def calculate_dimes(cents):
    return cents // 10


def calculate_nickels(cents):
    return cents // 5


def calculate_pennies(cents):
    return cents


main()