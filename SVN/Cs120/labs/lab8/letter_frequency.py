list_of_twenty_six = [0]*26


##### THIS FUNCTION ALTERS A LIST OUTSIDE OF ITSELF #####
## this function adds one to the value in the list that represents the incoming character
## pre: the character must be alpha and lower case
## post: the list is altered by one in one location
def add_to_list(char, list_of_twenty_six):
    location = ord(char) - ord('a')
    new_value = list_of_twenty_six[location] + 1
    list_of_twenty_six[location] = new_value


# this function prints all the letters and the number of them based of values stored in a list
# pre: the list that has the number of each letter
# post: all of the letters with corresponding numbers of occurance
def print_final_values(list_of_twenty_six):
    for i in range (ord('a'), (ord('z')+1) ):
        list_location = (i - ord('a'))
        print(chr(i),"-",list_of_twenty_six[list_location])


# this function initializes the string, user input, calls a new function based on whether the character is alpha or not and lower cases the whole string
# pre: a pre-initialized list full of 26 0's
# post: calls the print final value function
def for_loop_and_string_input(list_of_twenty_six):
    string_of_stuff = input("anything you really want, only letters  will count though..")
    string_of_stuff = string_of_stuff.lower()
    for char in (string_of_stuff):
        if (ord('a') <= ord(char) <= ord('z')):
            add_to_list(char, list_of_twenty_six)
    print('Final number of letters.')
    print_final_values(list_of_twenty_six)



for_loop_and_string_input(list_of_twenty_six)
