import vigenere
import sys
import math

NUM_ARGS           = 1
FILE_ARG_NUM       = 1
COMP_LETTERS       = 6
LETTER_FREQ_SORTED = "etaoinshrdlcumwfgypbvkjxqz"
LETTERS            = "abcdefghijklmnopqrstuvwxyz"
MAX_KEY_LEN        = 100
TEST_STR_FACTOR    = 3              #How much more than the guessed
                                    #keysize to try to decrypt first
# detect_english_frequencies:  Returns a count of the number of most
#       and least common letters were close to their correct
#       locations.
# Pre:  test_text is a string of lowercase letters.
# Post: Returns an integer in the range [0,12], with 0 being no
#       relation to english, 12 meaning perfect relation.
def detect_english_frequencies(test_text):
    hist = compute_histogram(test_text, LETTERS)

    high_letters = hist[:COMP_LETTERS]
    low_letters  = hist[-COMP_LETTERS:]

    common_count = 0
    for letter in high_letters:
        if letter in LETTER_FREQ_SORTED[:COMP_LETTERS]:
            common_count += 1

    for letter in low_letters:
        if letter in LETTER_FREQ_SORTED[-COMP_LETTERS:]:
            common_count += 1

    return common_count
        

# compute_histogram: returns a sorted list of elements based on
#       frequencies.
# Pre:  iter_stream is an iterable stream of items to compute the
#       histogram of.
#       keys is an iterable object of all possible keys. (OPTIONAL)
# Post: Returns a sorted list of elements in iter_stream, ordered by
#       their frequencies.
def compute_histogram(iter_stream, keys=""):
    histogram = dict()
    letter_count = 0

    for key in keys:
        histogram[key] = 0

    #Increments counts for alphabetic characters
    for element in iter_stream:
        if element not in histogram.keys():
            histogram[element] = 1
        else:
            histogram[element] += 1

    #Sort the results
    sorted_list = sorted(histogram, key=histogram.get, reverse=True)
    return sorted_list


# create_file_strips: returns a list of strings that were all encoded
#       with the same key.
# Pre:  file_text is the text of the file, num_strips is the number of
#       strips to make.
# Post: Returns a list of strings, whose characters were encoded with
#       (hopefully) the same key.
def create_file_strips(file_text, num_strips):
    file_strips = ["" for i in range(num_strips)]

    for i in range(len(file_text)):
        file_strips[i % num_strips] += file_text[i]
    
    return file_strips

# compute_list_of_key_lengths: Computes list of likely key lengths,
#       sorted by occurances
# Pre:  input is a string of lowercase alphabetic characters
# Post: returns a list of 
def compute_list_of_key_lengths(file_text):
    sequence_repetition = get_sequence_spacing(file_text, 3)
    all_factors = compute_all_factors(sequence_repetition)
    return compute_histogram(all_factors)


# get_sequence_spacing: Get's a list of all repeaded sequences of n
#       letters.
# Pre:  file_text is a string of lowercase alphabetic characters.
#       size is an integer, signifying the length of the repeated
#       characters.
# Post: returns a list of integers, the unique distances between
#       recurring elements
def get_sequence_spacing(file_text, size):
    #Stores the previous location of found sequences in the text file
    previous_occurance_location = dict()
    
    #Stores the distances between recurring elements
    spacing_distances = []

    start = 0
    end   = start + size
    while end < len(file_text):
        #get current sequence
        sequence = file_text[start:end]
        if sequence in previous_occurance_location.keys():
            distance = start - previous_occurance_location[sequence]

            if distance not in spacing_distances:
                spacing_distances.append(distance)
        previous_occurance_location[sequence] = start

        #Increment counters
        start += 1
        end    = start + size

    return spacing_distances

# compute_all_factors: Factor number into all possible factors
# Pre:  numbers is an list of integers >= 2
# Post: Returns a list containing all factors of 
def compute_all_factors(numbers):
    factors = []
    for number in numbers:
        factors = factors + compute_factors(number)

    return factors


# compute_factors: Factor number into all possible factors
# Pre:  Input is an integer >= 2
# Post: Returns a list containing all factors of num
def compute_factors(num):
    factors = [num]
    for i in range(2, min((num // 2) + 1, MAX_KEY_LEN)):
        if num % i == 0:
            factors.append(i)
        
    return factors

# compute_possible_decodings: returns a list of tuples, the key and
#       the english match score.
# Pre:  strip is a string of lowercase characters
# Post: Returns a list of tuples, the key and it's match score
def compute_possible_decodings(strip):
    possible_list = []
    for letter in LETTERS:
        test_message = vigenere.vigenere_encode_string(strip,
                                                       letter, 
                                                       -1)
        possible_list.append((letter, 
                             detect_english_frequencies(test_message)))
    return possible_list

def try_keys(test_str, possible_keys, chosen_keys=[], curr_index=0):
    if curr_index == len(possible_keys):
        key = "".join(chosen_keys)
        print(key, vigenere.vigenere_encode_string(test_str,
                                              key,
                                              -1))
        return

    for key in possible_keys[curr_index]:
        chosen_keys.append(key[0])
        try_keys(test_str, possible_keys, chosen_keys, curr_index + 1)
        chosen_keys.pop()

if __name__ == '__main__':
    if len(sys.argv) < NUM_ARGS:
        print("Error, not enough arguments")
        sys.exit(1)

    input_file = open(sys.argv[FILE_ARG_NUM])

    file_text = input_file.read()

    input_file.close()

    possible_key_lens = compute_list_of_key_lengths(file_text)
    print(possible_key_lens)

    done = False
    while not done:
        possible_key_len = possible_key_lens.pop(0)
        print("Looking for keys of length:", possible_key_len)
        file_strips = create_file_strips(file_text, possible_key_len)
        possible_keys = []
        strip_num = 0
        for strip in file_strips:
            possible_decodings = compute_possible_decodings(strip)
            possible_key = []
            possible_key.append(possible_decodings.pop(0))
            for decoding in possible_decodings:
                if decoding[1] > possible_key[0][1]:
                    possible_key = [decoding]
                elif decoding[1] == possible_key[0][1]:
                    possible_key.append(decoding)
            possible_keys.append(possible_key)
            strip_num += 1

        test_str = file_text[:TEST_STR_FACTOR * possible_key_len]
        
        #Now try all combinations of those on test_str
        try_keys(test_str, possible_keys)

        done = (len(possible_key_lens) == 0 or 
                input("Type \"D\" if Done: ") == "D")
    
    # for letter in LETTERS:
    #     test_message = vigenere.vigenere_encode_string(file_strips[0], 
    #                                                    letter, 
    #                                                    -1)
    #     print(letter, 
    #           detect_english_frequencies(test_message))
