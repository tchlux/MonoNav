import os
import pickle
import random

# ============
#   Prompts
# ============

I_CAN_SAY = "I can now say %d phrases!"
INIT_STR = ""
EXIT_RESPONSES = ["exit", "quit", "q", "e"]

ADD = "add"
DELETE = "delete"
VIEW = "view"
HELP = "help"
CLEAN = "clean"
CREATE_WORDS_DICTIONARY = "create words dictionary"
VIEW_WORDS_DICTIONARY = "view words dictionary"

QUESTION = "? "
OPTIONS_ARE = "Your options are: "
OPTIONS = [ADD, DELETE, VIEW, HELP, CLEAN, CREATE_WORDS_DICTIONARY,
           VIEW_WORDS_DICTIONARY, EXIT_RESPONSES]

WHICH_KEY = "Which key do you have in mind? "
WHAT_RESPONSE = "What new response should be added? "
KEY_NOT_FOUND = "That key didn't exist."
CONTINUE = "Press enter to continue"
WAS_DELETED = "%s was deleted from the dictionary."
HELP_ME_WITH = "What do I say for this :: %s :: \n? "
THIS_MANY = "There are %d phrases that I don't know responses to."


# Pre:  
# Post: Pauses execution and alerts user of how to continue
def pause():
    input(CONTINUE)

# Pre:  
# Post: All options for editing are printed
def print_options():
    print(OPTIONS_ARE)
    for opt in OPTIONS:
        print(opt)

# Pre:  string is a string
# Post: all non alphabetic characters w/ exception of spaces are
#       removed
def simplify(string):
    final = ""
    for char in string:
        if char.isalpha() or char==" ":
            final += char
    return final.lower()

# Pre:  chatbot is defined and initialized
# Post: All phrases that have no responses in chatbot are filled
def help_chatbot(chatbot):
    for key in chatbot.dict:
        if len(chatbot.dict[key]) == 0:
            print(HELP_ME_WITH%key)
            response = simplify(input(WHAT_RESPONSE))
            chatbot._add_new_response(key, response)
            

# Pre:  chatbot is defined and initialized, value is a string
# Post: responses with given value are removed
def remove_value(chatbot, value):
    for key in chatbot.dict:
        for pair in chatbot.dict[key]:
            if pair[0] == value:
                chatbot.dict[key].remove(pair)


# Pre:  chatbot is a chatbot class that has been initialized fully
# Post: The editing sequences are saved
def edit(chatbot):
    chatbot.post(I_CAN_SAY%(len(chatbot.dict)))
    response = INIT_STR

    count = 0
    for key in chatbot.dict:
        if len(chatbot.dict[key]) == 0:
            count += 1
    print(THIS_MANY%count)

    while response not in EXIT_RESPONSES:
        print_options()
        response = simplify(input(QUESTION))

        if response == ADD:
            key = simplify(input(WHICH_KEY))
            response = simplify(input(WHAT_RESPONSE))
            if key not in chatbot.dict:
                print(KEY_NOT_FOUND)
                chatbot._add_new_expression(key)
            chatbot._add_new_response(key, response)

        elif response == VIEW:
            key = simplify(input(WHICH_KEY))
            if key not in chatbot.dict:
                print(KEY_NOT_FOUND)
            else:
                print(chatbot.dict[key])
            pause()

        elif response == DELETE:
            key = simplify(input(WHICH_KEY))
            if key in chatbot.dict:
                del(chatbot.dict[key])
                print(WAS_DELETED%key)
            else:
                print(KEY_NOT_FOUND)

        elif response == HELP:
            help_chatbot(chatbot)

        elif response == CLEAN:
            value = simplify(input(WHAT_RESPONSE))
            remove_value(chatbot, value)

        elif response == CREATE_WORDS_DICTIONARY:
            pass

        elif response == VIEW_WORDS_DICTIONARY:
            pass

    chatbot._save_my_dictionary()


# #this function is solely for editing purpuses, it allows me to manually alter/insert/delete the values in the dictionary
# #pre: no input is required, it does strictly edit the big_dictionary associated with this program
# #post: the edited dictionary is saved and the program is terminated
# def big_dictionary_editor():
# #            words_dictionary = clean_out_specified_responses(words_dictionary)
# #this is where the user can update or create a dictionary of all words in the big_dictionary
#         elif response == 'create words dictionary':
#             words_dictionary = create_dictionary_of_words(big_dictionary)
#             save_a_dictionary(words_dictionary, 'words_dictionary')
#         elif response == 'view words_dictionary':
#             words_dictionary = return_a_file('words_dictionary')
#             print('Words dictionary\n',words_dictionary)
#     save_a_dictionary(big_dictionary, 'big_dictionary')
