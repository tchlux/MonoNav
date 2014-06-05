###########################################################################
# File:    caesar.py
# Author:  Scotty Smith
#
# Purpose: Perform a caesar cipher on some plain text
# Pre:     Command line arguments
#          1) The plaintext file, containing only lower case letters,
#          punctuation, and new lines.
#          2) The ciphertext file, which we have permission to write
#          to.
#          3) The key, an integer number in the range [-25,25]
# Post:    Writes to the file in argument 2 the encrypted version of
#          the file specified in argument 1.  All non-alphabetic
#          characters are left intact.
###########################################################################

import sys;
NUM_ARGS          = 4
IN_FILE_POSITION  = 1
OUT_FILE_POSITION = 2
KEY_POSITION      = 3
ASCII_START       = ord('0')
RING_SIZE         = 10


# caesar_encode_char: returns the passed character, cyclically shifted
#       by key
# Pre:  char is a valid alphabetic character.
#       key is an integer value in the range [-25,25]
# Post: returns the passed char cyclically shifted by key number of
#       characters. 
def caesar_encode_char(char, key):
    char_number = (ord(char) - ASCII_START)
    encrypted_char_number = ((char_number + key) % RING_SIZE)
    encrypted_char = chr(encrypted_char_number + ASCII_START)

    return encrypted_char



# caesar_encode_file: Reads in_file, encodes using caesar shift
#       cipher using key, and write to out_file
# Pre:  in_file is an open file object that we have permission to read
#       from.
#       out_file is an open file object that we have permission to
#       write to.
#       key is an integer value in the range [-25,25]
# Post: Writes each alphabetic character from in_file to out_file,
#       cyclically shifted by key amount.  All other characters are
#       just written out unaltered.
def caesar_encode_file(in_file, out_file, key):
    for line in in_file:
        for char in line:
            encrypted_char = char
#            if encrypted_char.isalpha():
            encrypted_char = caesar_encode_char(char, key)
            out_file.write(encrypted_char)

if __name__ == "__main__":
    if len(sys.argv) < NUM_ARGS:
        sys.exit(1)

    read_file  = open(sys.argv[IN_FILE_POSITION], "r")
    write_file = open(sys.argv[OUT_FILE_POSITION], "w")
    key        = 734#int(sys.argv[KEY_POSITION])

    caesar_encode_file(read_file, write_file, key)

    read_file.close()
    write_file.close()
