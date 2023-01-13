def main():
    # Get user input
    text = input("Text: ")

    # Counting letters
    letters = count_letters(text)

    # Counting words
    words = count_words(text)

    # Counting sentences
    sentences = count_sentences(text)

    # Putting it all together
    L = (letters / words) * 100
    S = (sentences / words) * 100
    index = 0.0588 * L - 0.296 * S - 15.8
    grade = round(index)

    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {grade}")


# Function to count letters
def count_letters(text):
    counter = 0
    for c in text:
        if c.isalpha():
            counter += 1
    return counter


# Function to count words
def count_words(text):
    counter = 1
    for c in text:
        if c == " ":
            counter += 1
    return counter


# Function to count sentences
def count_sentences(text):
    counter = 0
    for c in text:
        if c == "." or c == "!" or c == "?":
            counter += 1
    return counter


main()