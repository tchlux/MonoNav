import pickle
# pickle is used to open and save the dictionary
import random
# random is used to generat responses
import time
# time is used to make the response appear like typing
import math
# math is used to do a math.floor() calculation
import os
# os is used for testing if a file is already there or not
import sys
# sys is used to flush print statements to the terminal


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
        a_file = {'hello':[], 'goodbye':[]}
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
        current_values = []
    current_values.append(new_item)
    dictionary[key] = current_values
    return dictionary

#this function returns a random response from a list put into it
#pre: this function requires a list
#post: a random value from the list
def random_response_from_list(lst):
    if type(lst) is str:
        print("ERROR:  A STRING WAS PUT INTO RANDOM_RESPONSE_FROM_LIST FUNCTION\n\n")
    if lst == []:
        print('ERROR: A LIST WITH NO VALUES WAS PUT INTO RANDOM_RESPONSE_FROM_LIST FUNCTION\n\n')
    length = len(lst)
    indx = int(random.random()*length)
#note that on occasion this lst[indx] returns an error message saying index out of range
#I have run thousands of tests of this function through for loops and recieved no errors
#there is some sort of fundamental memory error coming from python that im not aware of
#and that i can not predict, any help would be appriciated
    return lst[indx]

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
#    curses.initscr()
    yes_no = input('Do you want to edit? ')
    if yes_no == "yes":
        big_dictionary_editor()
    else:
         input_and_response()






#####################################################################################
###########THE FOLLOWING LINES ARE FOR MANUALLY EDITING THE DICTIONARY###############
#####################################################################################



#this function goes through any keys in chatbot's dictionary that have no response and straight out asks the proper response, it also tells you how many words it doesnt know before you start
#pre: a dictionary to be edited and returned
#post: the dictionary with a response to everything

#A KNOWN ERROR IN THIS FUNCTION IS WHEN YOU PRESS ENTER WITHOUT TYPING IT SAVES ANOTHER BLANK IN THE WORD AND THEN ONCE THE CLEANER FUNCTION IS USED THE LISTS WITH TWO BLANKS WILL BE LEFT EMPTY, THIS WILL CAUSE THE PROGRAM TO CRASH IF AN EMPTY VALUE KEY IS CALLED BE WEARY ONCE YOU START YOU MUST FINISH "HELPING" CHATBOT UNLESS YOU CLOSE THE TERMINAL EARLY
def chat_bot_helper(dictionary):
    count = 0
    for key in dictionary:
        if dictionary[key] == [""] or dictionary[key] == []:
            count += 1
    print('There are', count,'Keys with no value')
    for key in dictionary:
        if dictionary[key] == [""] or dictionary[key] == []:
            print(key)
            response = input("Response to this? ")
            dictionary = dictionary_value_list_editor(dictionary, key, response)
    return dictionary

#this function cleans out specific values from keys that already have other responses
#pre: a dictionary
#post: the dictionary with specific responses removed from keys that have other options
def clean_out_specified_responses(dictionary):
    specific_response = input('\nThe exact phrase you would like to remove entirely from the dictionary: ')
    for key in dictionary:
        if dictionary[key] != [""]:
            if specific_response in dictionary[key]:
                current_list = dictionary[key]
                new_list = []
                for item in current_list:
                    if item != specific_response:
                        new_list.append(item)
                dictionary[key] = new_list
                print('Key adjusted', key)
    return dictionary

#this function is solely for editing purpuses, it allows me to manually alter/insert/delete the values in the dictionary
#pre: no input is required, it does strictly edit the big_dictionary associated with this program
#post: the edited dictionary is saved and the program is terminated
def big_dictionary_editor():
    big_dictionary = return_a_file('big_dictionary')
    words_dictionary = return_a_file('words_dictionary')
    response = ""
    count = 0
    for key in big_dictionary:
        count += 1
    print('I can say',count,'phrases now! Im learning fast!')
    while response != "exit":
        response = input("\nAdd (edit responses) , delete , view, help (chatbot learn), clean\n (specific phrase out of dictionary), create words dictionary, view words_dictionary \n or exit? ")

# this is where the user edits the dictionary by entering a key and value, it appends only
# if the key is not already in the dictionary it adds it
        if response == "add":
            key = input('The key you want edit: ')
            if key in big_dictionary:
                print('Key exists')
                print('\nThe current value for that key is: ', big_dictionary[key],'\n')
            else:
                print('Key does not already exist, it will be created')
                big_dictionary[key] = []
            value = input('What is the value you want to take place for that key? ')
            big_dictionary = dictionary_value_list_editor(big_dictionary, key, value)
#this is where the user views the current values for a key in the dictionary
        elif response == 'view':
            key = input('\nThe key phrase you would like to view? ')
            if key in big_dictionary:
                print('The current value for that key is')
                print(big_dictionary[key])
            else:
                print('That key is not currently in the big dictionary')
            pause = input('\nPress enter when you are done')
#this is where the user can delete keys and their values from the dictionary
        elif response == "delete":
            key = input('\nKey name you would like to delete? ')
            del big_dictionary[key]
            print('Key,',key,"was deleted from the dictionary")
#this is where the user can give responses for keys that have no known response
        elif response == 'help':
            big_dictionary = chat_bot_helper(big_dictionary)
#this is where the user cleans out all specified responses from the dictionary
        elif response == 'clean':
            big_dictionary = clean_out_specified_responses(big_dictionary)
#            words_dictionary = clean_out_specified_responses(words_dictionary)
#this is where the user can update or create a dictionary of all words in the big_dictionary
        elif response == 'create words dictionary':
            words_dictionary = create_dictionary_of_words(big_dictionary)
            save_a_dictionary(words_dictionary, 'words_dictionary')
        elif response == 'view words_dictionary':
            words_dictionary = return_a_file('words_dictionary')
            print('Words dictionary\n',words_dictionary)
    save_a_dictionary(big_dictionary, 'big_dictionary')


#this function creates a key for each individual word in the given dictionary with an empty list value
#pre: a dictionary
#post: the words in that dictionary
def create_dictionary_of_words(phrases_dictionary):
    words_dictionary = {}
    for key in phrases_dictionary:
        words_dictionary = add_to_words_dictionary_for_word_if_not_in(words_dictionary, key)
        for item in phrases_dictionary[key]:
            words_dictionary = add_to_words_dictionary_for_word_if_not_in(words_dictionary, item)
    words_dictionary = build_words_that_follow(words_dictionary, phrases_dictionary)
    return words_dictionary

#this function is partner to create_dictioanary_of_words and it is used to clean up and seperate a for loop and if statement that is repeated
#pre: a dictionary to check and edit and a string
#post: the dictionary updated with the words in the string
def add_to_words_dictionary_for_word_if_not_in(dictionary, phrase):
    phrase_list = phrase.split(' ')
    for word in phrase_list:
        if word not in dictionary:
            dictionary[word] = []
    return dictionary

#this function cycles through all keys and responses to look at words that follow words
#pre: the dictionary with every word as a key and the dictionary of all phrases
#post: the words dictionary now has all following words for keys saved as values lists
def build_words_that_follow(dictionary_of_words, phrase_dictionary):
    for key in phrase_dictionary:
        phrase = key.split(' ')
        if len(phrase) > 1:
            for i in range(len(phrase)-1):
                dictionary_value_list_editor(dictionary_of_words, phrase[i], phrase[i+1])
        for item in phrase_dictionary[key]:
            phrase = item.split(' ')
            if len(phrase) > 1:
                for i in range(len(phrase)-1):
                    dictionary_of_words = dictionary_value_list_editor(dictionary_of_words, phrase[i], phrase[i+1])
    return dictionary_of_words

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








#################################BACKUP  FUNCTIONS################################




## this function should be run after error statements suggesting there is a string in the dcitionary of values, all of which should be lists

# def make_all_dictionary_values_lists():
#     dictionary = return_a_file('big_dictionary')
#     for key in dictionary:
#         if type(dictionary[key]) is str:
#             vlist = []
#             vlist.append(dictionary[key])
#             print(key,",", dictionary[key],"      =====>>>  ",key,",",vlist)
#             dictionary[key] = vlist
#     save_big_dictionary(dictionary)

# make_all_dictionary_values_lists()


# #this definition finds any of the words in the line in the dictionary to give a semi relavent response
# #pre: the line the user last entered and the dictionary
# #post: a response to one of the words in the users last line
# def test_phrases_in_line(current_line, big_dictionary):
#     key = False
#     current_line_words = current_line.split(" ")
#     for word in current_line_words:
#         if word in big_dictionary:
#             key = word
#     return key
