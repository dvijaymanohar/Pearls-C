#!/usr/bin/env python3

# Van Eck sequence
#
# The 'Van Eck' sequence starts with a zero. Then, for any next term the term is:
# * Zero if the previous term is new in the sequence
# * Else it is the distance to the previous occurrence of the term
#
# Implement a function to print the first N values of the sequence.

def vanEckSequence(n):
    sequence = [0] * (n + 1)
    # Initialize sequence array
    for i in range(n):
        sequence[i] = 0

    # Loop to generate sequence
    for i in range(n):

        # Check if sequence[i] has occurred previously or is new to sequence
        for j in range(i - 1, -1, -1):
            if (sequence[j] == sequence[i]):

                # If occurrence found then the next term will be how far back this last term
                # occurred previously
                sequence[i + 1] = i - j
                break

    for i in sequence:
        print(i)


if __name__ == "__main__":
    try:
        n = int(input('Enter the value of N: '))
    except ValueError:
        exit('Enter a valid number')

    vanEckSequence(n)