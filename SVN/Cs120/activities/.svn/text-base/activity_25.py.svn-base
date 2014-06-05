
## this first activity took a text file, read it, and returned the number of words in the file

# def prompt_file_name():
#     file_name = input("What is the name of the file? :) ")
#     return file_name

# def count_words_in_file():
#     file_name = prompt_file_name()
#     print('file name:"'+ file_name + '"')
#     file_one = open(file_name, "r")
#     list_of_words = []
#     words_in_file = 0
#     for line in file_one:
#         list_of_words = line.split("")
#         words_in_file += len(list_of_words)
#     file_one.close()
#     return words_in_file

# print("Number of words in file.", count_words_in_file())

## this second activity took an input file, capitalized everything in it and put it in a specified output file

def prompt_for_files():
    input_file = input('Input file name?')
    output_file = input('Output file name?')
    return (input_file, output_file)

def create_and_write_output_file():
    (input_file, output_file) = prompt_for_files()
    data = open(input_file, "r")
    string_of_data = data.read()
    data.close()
    string_of_data = string_of_data.upper()
    output = open(output_file, "w")
    output.write(string_of_data)
    output.close()

create_and_write_output_file()
