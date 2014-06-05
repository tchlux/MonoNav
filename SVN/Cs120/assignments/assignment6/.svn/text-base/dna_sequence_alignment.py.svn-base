

# this definition will test each character to see if they match starting with the longest strings characters
# pre: the dna strings
# post: match or not in a string of ' 's for not matches and letters for matchs
def match_dna_strings_and_concat_new_string(first_dna_string, second_dna_string):
    if len(first_dna_string) >= len(second_dna_string):
        longest_dna_string = first_dna_string
        shorter_dna_string = second_dna_string
    elif len(first_dna_string) < len(second_dna_string):
        longest_dna_string = second_dna_string
        shorter_dna_string = first_dna_string
    longest_dna_string_length = len(longest_dna_string)
    match_results = ""
    current_longest_string = 0
    shorter_dna_match_start_loc = 0
    matching_string_length = 0
    for i in range (longest_dna_string_length):
        (matching_string_length, matching_string, shorter_dna_match_start_loc) = test_if_first_dna_matches_second_dna(longest_dna_string[i:], shorter_dna_string, matching_string_length, shorter_dna_match_start_loc)
        if matching_string_length > current_longest_string:
            current_longest_string = matching_string_length
            match_results = matching_string
            longer_dna_match_start_loc = i
    match_results_length = len(match_results)
    return (match_results, longer_dna_match_start_loc, shorter_dna_match_start_loc)


# this function rotates through matching characters in the shorter string and sends them to be tested for length of match
# pre: this function requires the remaining portion of the initially larger string and the entire shorter string
# post: the longest match following the first character of the remaining sequence
def test_if_first_dna_matches_second_dna(rest_of_longest_dna_string, shorter_dna_string, matching_string_length, shorter_dna_match_start_loc):
    max_character_location_in_second_string = len(shorter_dna_string)
    rest_of_longest_dna_string_length = len(rest_of_longest_dna_string)
    shorter_dna_string_length = len(shorter_dna_string)
    matching_string = ""
    current_string = ""
    integer = 0
    for i in range (shorter_dna_string_length):
        if rest_of_longest_dna_string[0] == shorter_dna_string[i]:
            (current_string_length, current_string) = while_loop_for_matching_subsequences(rest_of_longest_dna_string, shorter_dna_string, i)
            if current_string_length > matching_string_length:
                matching_string = current_string
                matching_string_length = current_string_length
                shorter_dna_match_start_loc = i
    return (matching_string_length, matching_string, shorter_dna_match_start_loc)


# this function runs a while loop that finds out how long the current strings line up
# pre: this function requires the two strings and the index of where to start looking
# post:  this function returns the length and value of the matching subsequence
def while_loop_for_matching_subsequences(rest_of_longest_dna_string,shorter_dna_string,i):
    short_temp_loc = i
    integer = 0
    current_string = ""
    while (integer < len(rest_of_longest_dna_string)) and (short_temp_loc < len(shorter_dna_string)) and (determine_if_nucleotides_are_same(rest_of_longest_dna_string[integer], shorter_dna_string[short_temp_loc]) == True):
        current_string += rest_of_longest_dna_string[integer]
        integer += 1
        short_temp_loc += 1
    current_string_length = len(current_string)
    return (current_string_length, current_string)


# this function returns whether or not two nucleotides do/could equal eachother
# pre: the two nucleotides to be compared, A,T,C,G,Y,R, or N form
# post: a True of False bool of whether or not they match
def determine_if_nucleotides_are_same(first_nucleotide, second_nucleotide):
    fn = first_nucleotide
    sn = second_nucleotide
    final_decleration = False
    if fn == "N" or sn == "N":
        final_decleration = True
    elif fn == sn:
        final_decleration = True
    elif fn == "Y" and (sn == "T" or sn == "C"):
        final_decleration = True
    elif fn == "R" and (sn == "A" or sn == "G"):
        final_decleration = True
    elif (fn == "A" or fn == "G") and sn == "R":
        final_decleration = True
    elif (fn == "T" or fn == "C") and sn == "Y":
        final_decleration = True
    else:
        final_decleration = False
    return final_decleration


# this function prompts for user input in string form and calls the working functions
# pre: the input must be valid, for the purpose of this program they must be ATC or G
# post:  this program prints the largest matching subsequence in the two dna strands
def run_the_find_matching_dna_sequences_class():
    first_dna_string = input("First DNA string? ")
    second_dna_string = input("Second DNA string? ")
    (match_results, longer_dna_match_start_loc, shorter_dna_match_start_loc) = match_dna_strings_and_concat_new_string(first_dna_string, second_dna_string)
    print(' The longest matching subsequence between the two strands of DNA is')
    print(match_results)
    print(' this starts at location', longer_dna_match_start_loc, 'for the longer DNA sequence')
    print(' this starts at location', shorter_dna_match_start_loc, 'for the shorter DNA sequence')
    print('If the sequences are the same length, it is generalized that the first is the longer')

def run_the_find_matching_dna_sequences_class_from_fasta():
    information_about_sequence = input()
    first_dna_string = input()
    information_about_second_sequence = input()
    second_dna_string = input()
    (match_results, longer_dna_match_start_loc, shorter_dna_match_start_loc) = match_dna_strings_and_concat_new_string(first_dna_string, second_dna_string)
    print(' The longest matching subsequence between the two strands of DNA is')
    print(match_results)
    print(' this starts at location', longer_dna_match_start_loc, 'for the longer DNA sequence')
    print(' this starts at location', shorter_dna_match_start_loc, 'for the shorter DNA sequence')
    print('If the sequences are the same length, it is generalized that the first is the longer')


#run_the_find_matching_dna_sequences_class()
run_the_find_matching_dna_sequences_class_from_fasta()
