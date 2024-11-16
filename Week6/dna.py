import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py [database.csv] [sequence.txt]")
        return

    # TODO: Read database file into a variable
    STRs = []
    database = []
    with open(sys.argv[1]) as csvfile:
        reader = csv.DictReader(csvfile) # DAMN!NOT csv.Dictreader!
        for row in reader:
            database.append(row)
        STRs = reader.fieldnames # notice that index 0 is "name"
        STRs.remove('name')


    # TODO: Read DNA sequence file into a variable
    sequence = ''
    with open(sys.argv[2]) as txt:
        sequence = txt.read()

    # TODO: Find longest match of each STR in DNA sequence
    match_dict = {}
    for s in STRs:
        match_dict[s] = longest_match(sequence,s)

    # TODO: Check database for matching profiles
    for row in database: # returned row is a dict type
        # all() returns True if all elements of the iterable are true
        is_subset = all(int(row.get(key)) == value for key, value in match_dict.items())
        if is_subset:
            print(row['name'])
            break
    else: # if no break in the loop
        print("No match")


    return


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
