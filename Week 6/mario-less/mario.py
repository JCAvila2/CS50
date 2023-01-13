# Get user input
while True:
    try:
        n = int(input("Height: "))
        if n < 9 and n > 0:
            break
    except:
        print("Insert an integer between 1 and 8")

# Print the half-pyramid
for r in range(1, n + 1):
    print(" " * (n - r) + "#" * r)