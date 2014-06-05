import math
# math is used to do a math.floor() calculation
import os
# os is used for testing if a file is already there or not
import pickle
# pickle is used to open and save the dictionary
import random
# random is used to generat responses
import sys
# sys is used to flush print statements to the terminal
import time
# time is used to make the response appear like typing
import chat_bot_editor
#this is how i access all my editor functions


#this function returns the a_file as it was last saved
#pre: nothing needs to go into this function
#post: returns the a_file
def return_a_file(a_file):
    if os.path.exists(a_file +'.txt'):
# i know this is not the traditional means of file opening i was just testing it out
        with open(a_file +'.txt', 'rb') as f:
            a_file = pickle.load(f)
            f.close()
    else:
        file_name = a_file+".txt"
        input(a_file +" not found, one can be created if you press enter otherwise close the current window without continuing")
        a_file = {'hello':['hello'], 'goodbye':['goodbye']}
        dictionary_file = open(file_name, 'wb')
        pickle.dump(a_file, dictionary_file)
        dictionary_file.close()
    return a_file

#this function is used to confirm that the user wants to save over the last dictionary
#pre: the most recent updated dictionary to save
#post: the dictionary is saved for later use
def save_a_dictionary(a_dictionary, a_file):
    yes_no = input('Do you want to save over the old dictionary in '+a_file+'.txt? ')
    edit_state = ""
    while yes_no != "yes" and yes_no != "no":
        print('')
        yes_no = input('yes or no: ')
    if yes_no == "yes":
        with open(a_file+'.txt', 'wb') as f:
            pickle.dump(a_dictionary, f)
            f.close()
        edit_state = ("Dictionary successfully edited in " + a_file+".txt")
    else:
        edit_state = "Editing cancelled"
    print(edit_state)
    print('Done')

#this function finds a specified value in a list and returns the location if it does exist, otherwise it returns False
#pre: this function requires a list and a value; the value must be a string
#post: the function returns the index location in the list of the specified value
def value_in_list_finder(lst, value):
    if value in lst:
        return lst.index(value)
    else:
        for item in lst:
            if value in item:
                return lst.index(item)
    return False

    # for item in lst:
    #     if item == value:
    #         return lst.index(item)
    #     else:
    #         if type(item) is list:
    #             for obj in item:
    #                 if obj == value:
    #                     return lst.index(item)
    #                     pass
    # return False

#this function is used to edit the values list for a dictionary key, it adds one to the occurance of already existent values and it creates a new [value,1] list if it does not exist
#pre: the dictionary key must already be a list and the item should be a string
#post: the new list of dictionary[key] values and their occurances
def edit_dictionary(dictionary_key, item):
    new_dictionary_values = dictionary_key
    if (value_in_list_finder(dictionary_key, item) != False):
        location = value_in_list_finder(dictionary_key, item)
        new_dictionary_values[location][1] += 1
    else:
        new_dictionary_values.append([item,1])
    return new_dictionary_values

#this function adds the new entries into the dictionary, if there is only one current response it makes the values into a list, if there is currently no response it adds one
#pre: the dictionary, the key and the value latter two should be strings
#post: the dictionary with additions
def dictionary_value_list_editor(dictionary, key, new_item):
    if (key in dictionary):
        if (type(dictionary[key]) is str):
            vlist = []
            vlist.append(dictionary[key])
            dictionary[key] = vlist
        current_values = dictionary[key]
    else:
        if key in dictionary:
            current_values = edit_dictionary(dictionary[key], new_item)
            dictionary[key] = current_values
        else:
            current_values = edit_dictionary([], new_item)
            dictionary[key] = current_values
    return dictionary

#this function returns a random response from a list put into it
#pre: this function requires a list
#post: a random value from the list
def random_response_from_list(lst):
    if type(lst) is str:
        return("ERROR:  A STRING WAS PUT INTO RANDOM_RESPONSE_FROM_LIST FUNCTION\n\n")
        pass
    if lst == []:
        return('ERROR: A LIST WITH NO VALUES WAS PUT INTO RANDOM_RESPONSE_FROM_LIST FUNCTION\n\n')
        pass
    full_list = []
    try:
        for item in lst:
            for i in range(item[1]):
                full_list.append(item[0])
        choice = random.choice(full_list)
    except IndexError:
        choice = random.choice(lst)
    return choice

#this function ruturns a phrase of a specified length starting at a specified location in a list of words
#pre: the list of words, the start location, and the phrase length
#post: a string of that length from that specified start location created from the list with spaces in between
def cycle_words_in_phrase(words_list, start_location, phrase_length):
    phrase = ""
    return_string = ""
    finish = (start_location + phrase_length)
    for i in range(start_location, finish):
        phrase += words_list[i] + " "
    for i in range(len(phrase)-1):
        return_string += phrase[i]
    return return_string

#this function tests all possible phrases of all possible lengths in a line given to see if they exist in a dictionary
#pre: the line that needs to be tested and the dictionary to cross reference
#post: the key that exists in the dictionary and in part in the line
def test_phrases_in_line(line, dictionary):
    key = False
    words_list = line.split(' ')
    list_length = len(words_list)
    phrase_length = list_length
    while phrase_length != 0:
        start_location = 0
        while start_location < ((list_length - phrase_length)+1):
            phrase = cycle_words_in_phrase(words_list, start_location, phrase_length)
            if phrase in dictionary:
                key = phrase
                return key
                pass
            else:
                start_location += 1
        phrase_length -= 1
    return key

#this function determines the response to the users input, if it is in the dictionary it uses that otherwise it uses a random key in the dictionary
#pre: the current line is the users input, the previous line is the last response by the computer and the big_dictionary is what has all the keys and responses in it
#post: the response and the transitioned current and previous line strings
def find_in_dictionary(current_line, previous_line, big_dictionary):
    list_big_dictionary = list(iter(big_dictionary))
    if current_line == "":
        key = random_response_from_list(list_big_dictionary)
        response = random_response_from_list(big_dictionary[key])
        return(response, previous_line, big_dictionary)
        pass
    elif test_phrases_in_line(current_line, big_dictionary) != False:
        key = test_phrases_in_line(current_line, big_dictionary)
    else:
        key = random_response_from_list(list_big_dictionary)
    response = random_response_from_list(big_dictionary[key])
    while (response == ""):
        key = random_response_from_list(list_big_dictionary)
        response = random_response_from_list(big_dictionary[key])
    previous_line = response
    (big_dictionary) = dictionary_value_list_editor(big_dictionary, previous_line, current_line)
    return (response, previous_line, big_dictionary)

#this function calls the dictionary from a folder, then prompts for input and runs another function to determine the response based off of the given dictionary
#pre: this function requires its partner functions, no input parameters
#post: this function "talks" to the user until goodbye is said
def input_and_response():
    big_dictionary = return_a_file('big_dictionary')
    current_line = ""
    previous_line = ""
    while current_line != "goodbye":
        current_line = lower_and_remove_punctuation(input("Human face: "))
        (response, previous_line, big_dictionary) = find_in_dictionary(current_line, previous_line, big_dictionary)
        respond_to_user(response)
        previous_line = lower_and_remove_punctuation(response)
    save_a_dictionary(big_dictionary, 'big_dictionary')

#this function times the output so it looks like it is typing
#pre: the response to be printed
#post: the response is printed like a person is typing it
def respond_to_user(response):
    print("Dark blade:", end = " ")
    sys.stdout.flush()
    time.sleep(.3)
    for char in response:
        print(char, end = "")
        sys.stdout.flush()
        if char == " ":
            time.sleep(.1)
        else:
            time.sleep(.05)
    print("")

#this function rebuilds an input string without punctuation and leaves spaces between words
#pre: this function will remove all non alpha characters except spaces
#post: the input string with only alpha characters and spaces seperating words
def lower_and_remove_punctuation(string):
    new_string = ""
    for i in range(len(string)):
        if string[i].isalpha() or string[i] == " ":
            new_string += string[i]
    new_string = new_string.lower()
    return new_string

#this function begins the chat bot
#pre: this function has no input
#post: the editor is offered, if refused the chat bot begins
def start_chatbot():
    yes_no = input('Do you want to edit? ')
    if yes_no == "yes":
        chat_bot_editor.big_dictionary_editor()
    else:
         input_and_response()

def create_random_phrase():
    words_dictionary = return_a_file('words_dictionary')
    phrase_length = int(input('The length of the random phrase you would like to see? '))
    number_of_phrases = int(input('How many of them? '))
    list_of_words = list(words_dictionary.keys())
    word = random_response_from_list(list_of_words)
    print('the list of the following words is', words_dictionary[word])
    for i in range(number_of_phrases):
        phrase = word+' '
        for i in range (phrase_length-1):
            previous_word = word
            word = random_response_from_list(words_dictionary[previous_word])
            phrase += word+" "
        print("Random Phrase: ", phrase)

#create_random_phrase()








###################################START CHATBOT###################################
start_chatbot()
###################################START CHATBOT###################################
