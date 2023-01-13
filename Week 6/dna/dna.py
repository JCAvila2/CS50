import csv
import sys


def main():

    # Check for command-line usage
    if (len(sys.argv) != 3):
        print("Use 2 command line arguments")
        return

    # Read database file into a variable
    database = []
    with open(sys.argv[1], "r") as database_file:
        for line in csv.DictReader(database_file):
            # Append the dictionary of the actual line into the list
            database.append(line)

    # Read DNA sequence file into a variable
    DNA_sequence = open(sys.argv[2], "r").read().replace("\n", "")

    # Find longest match of each STR in DNA sequence
    # Create a dictionary to save the longest STR's
    longest_STR = {}
    for sequence in database[0].keys():
        if sequence != "name":
            longest_STR[sequence] = longest_match(DNA_sequence, sequence)

    # Check database for matching profiles
    for person in database:
        found = True
        name = person.pop("name")
        for sequence in longest_STR:
            if int(person[sequence]) != int(longest_STR[sequence]):
                found = False
                break
        if found:
            print(name)
            return
    print("No match")


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
