###########################################################################
# File:    vigenere.py
# Author:  Scotty Smith
#
# Purpose: Perform a caesar cipher on some plain text
# Pre:     Command line arguments
#          1) The plaintext file, containing only lower case letters,
#          punctuation, and new lines.
#          2) The ciphertext file, which we have permission to write
#          to.
#          3) The key, a string of lower case letters
#          4) Mode (e - encryption, d - decryption)
# Post:    Writes to the file in argument 2 the encrypted version of
#          the file specified in argument 1.  All non-alphabetic
#          characters are left intact.
###########################################################################

import sys;
NUM_ARGS          = 5
IN_FILE_POSITION  = 1
OUT_FILE_POSITION = 2
KEY_POSITION      = 3
MODE_POSITION     = 4
ASCII_START       = ord('a')
RING_SIZE         = 26
ENCRYPT_MODE_STR  = 'e'

# get_char_number: Returns the characters number, 0 based at 'a'.
# Pre:  char is a lower case alphabetic character.
# Post: Returns an integer, the distance from 'a' char is in the
#       alphabet.
def get_char_number(char):
    return (ord(char) - ASCII_START)

# caesar_encode_char: returns the passed character, cyclically shifted
#       by key
# Pre:  char is a valid alphabetic character.
#       key is an integer value in the range [-25,25]
# Post: returns the passed char cyclically shifted by key number of
#       characters. 
def caesar_encode_char(char, key):
    char_number = get_char_number(char)
    encrypted_char_number = ((char_number + key) % RING_SIZE)
    encrypted_char = chr(encrypted_char_number + ASCII_START)

    return encrypted_char

# vigenere_encode_file: Reads in_file, encodes using caesar shift
#       cipher using key, and write to out_file
# Pre:  in_file is an open file object that we have permission to read
#       from.
#       out_file is an open file object that we have permission to
#       write to.
#       key is a string of characters.
#       mode is an integer in the set {1, -1}, 1 for encode, -1 for
#       decode.
# Post: Writes each alphabetic character from in_file to out_file,
#       cyclically shifted by key amount.  All other characters are
#       just written out unaltered.
def vigenere_encode_file(in_file, out_file, key, mode):
    key_position = 0
    key_len      = len(key)

    for line in in_file:
        for char in line:
            encrypted_char = char
            if encrypted_char.isalpha():
                letter_key = mode * get_char_number(key[key_position])
                encrypted_char = caesar_encode_char(char, letter_key)
                out_file.write(encrypted_char)
                key_position = (key_position + 1) % key_len

# vigenere_encode_file: Reads in_file, encodes using caesar shift
#       cipher using key, and write to out_file
# Pre:  in_str is a string of lowercase characters to encode.
#       key is a string of lowercase characters.
#       mode is an integer in the set {1, -1}, 1 for encode, -1 for
#       decode.
# Post: returns the vigenere encoded version of in_str.
def vigenere_encode_string(in_str, key, mode):
    encoded_str = ""
    key_position = 0
    key_len      = len(key)

    for char in in_str:
        encrypted_char = char
        if encrypted_char.isalpha():
            letter_key = mode * get_char_number(key[key_position])
            encrypted_char = caesar_encode_char(char, letter_key)
            encoded_str += encrypted_char
            key_position = (key_position + 1) % key_len

    return encoded_str
    
if __name__ == "__main__":
    if len(sys.argv) < NUM_ARGS:
        sys.exit(1)

    read_file    = open(sys.argv[IN_FILE_POSITION], "r")
    write_file   = open(sys.argv[OUT_FILE_POSITION], "w")
    key          = sys.argv[KEY_POSITION]
    mode_str     = sys.argv[MODE_POSITION]
    mode         = 1 if mode_str == ENCRYPT_MODE_STR else -1

    vigenere_encode_file(read_file, write_file, key, mode)


    read_file.close()
    write_file.close()
