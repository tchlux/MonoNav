#! /usr/bin/env python3

import sys
import os

# Print a ppm file equivalent to the specified pnm file.
# PRE pnm_file is a binary pnm file
# POST the text of an equivalent ppm file will be printed
def print_ppm(pnm_file):
    pnm_file.readline()
    print("P3")
    for i in range(2):
        line_bytes = pnm_file.readline()
        line_string = line_bytes.decode()
        print(line_string, end="")
    pixel_data = pnm_file.read()
    for intensity in pixel_data:
        print(str(intensity))

# Print a ppm file equivalent to the specified pnm file.  A pnm file
# is specified either as a file name commandline argument or with
# standard input.
# PRE the specified pnm file is a valid binary pnm file
# POST the text of an equivalent ppm file will be printed
def main():
    number_of_arguments = len(sys.argv)
    if number_of_arguments == 2:
        file_name = sys.argv[1]
        if os.path.isfile(file_name):
            in_file = open(file_name, "rb")
            print_ppm(in_file)
        else:
            print("Error: could not read file '%s'." % file_name)
    elif number_of_arguments == 1:
        print_ppm(sys.stdin)
    else:
        print("Usage: pnmtoppm.py [FILE]")

if __name__ == "__main__":
    main()
