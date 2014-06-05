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
import editor
# editor is used to manually change the chatbot's dictionary


DICTIONARY = "big_dictionary" #save location
PKL = ".pkl" #pickle file extension
TXT = ".txt" #txt file extension
DEFAULT_DICTIONARY = {"hello":{"hello":1}, "goodbye":{"goodbye":1}}
INITIAL_PAUSE = .3 #time in seconds paused before response
SPACE_PAUSE = .1 #time in seconds paused for typing spaces
CHAR_PAUSE = .05 #time in seconds paused for typeing characters
SMALLEST_SUBPHRASE = 2 #smallest sub phrase searched for in a response

NORMAL_PRINT_MODE = False #set to true to limit responses to simple
                          #print statements with no fancy typing

# ======================
#    Prompts / Strings
# ======================

EXIT_RESPONSES = ["goodbye", "see you later", "ive got to go", "im leaving"]

SPACE = " "
INIT_STR = ""
USER_NAME = "Human  : " #user prompt location
BOT_NAME =  "Chatbot: " #chatbot username
SIMPLE_PROMPT = "> " #the prompt for users in normal_print_mode

WELCOME_EDIT = "Welcome to edit mode, I appreciate all your contributions."
ENTER_EDIT_MODE = "Would you like to specifically edit / interact with the current dictionary? "
DICT_NOT_FOUND =  " not found, one can be created if you press enter otherwise close the current window without continuing"
SAVE_OVER = "Do you want to save over the old dictionary in %s ? "
SUCCSESSFUL_SAVE = "Dictionary successfully edited in "
SAVE_CANCELLED = "Save cancelled."
DONE = "Done"
YES = "yes"
NEW_EXPRESSION_RESPONSE = "That's new."
FOUND_SUBPHRASE = "Subphrase found: "
FOUND_POSSIBILITES = "According to you I could say any of these things: "
PHRASE_LENGTH_PROMPT = "How long of a random phrase do you want? "
KEY_NO_VALUE = "Well you've said '%s' before but I don't know how to respond"
BLOCKED_POST = "I had a bad thought :P sorry"

#responses that are currently deactivated / blocked
DEACTIVATED_RESPONSES = [FOUND_POSSIBILITES, FOUND_SUBPHRASE,
                         NEW_EXPRESSION_RESPONSE, KEY_NO_VALUE]

# Pre:  Prompt is a string ready to be presented to the user, 
#       answer is an all lower case string with no white space on ends
# Post: Boolean => (if response == answer)
def prompt(prompt, answer):
    return (input(prompt).strip().lower() == answer)

# Pre:  string is a string
# Post: all non alphabetic characters w/ exception of spaces are
#       removed
def simplify(string):
    final = ""
    for char in string:
        if char.isalpha() or char==" ":
            final += char
    return final.lower()

class Chatbot:
    # Pre:  
    # Post: 
    def __init__(self, dictionary):
        self.d_file = dictionary
        self._load_dictionary()

    # Pre:  dict_file is a string filename for a pickled python
    #       dictionary
    # Post: the dictionary itself is loaded into the class
    def _load_dictionary(self):
        if os.path.exists(self.d_file+PKL):
            f = open(self.d_file+PKL, 'rb')
            self.dict = pickle.load(f)
            f.close()
        else:
            self.dict = DEFAULT_DICTIONARY

    # Pre:  
    # Post: self.dict is written to a pickled file
    def _save_my_dictionary(self):
        yes = prompt(SAVE_OVER%(self.d_file+PKL), YES)
        state = INIT_STR #holds the edit state (success, fail, denied, cancelled)
        if yes:
            f = open(self.d_file+PKL, 'wb')
            a_dict = pickle.dump(self.dict, f)
            f.close()
            state = SUCCSESSFUL_SAVE+self.d_file+PKL
        else:
            state = SAVE_CANCELLED
        self.post(state)
        self.post(DONE)

    # Pre:  string is a string type
    # Post: String is printed to the terminal in a manner that
    #       resembles typing by a person
    def post(self, string):
        valid = True
        #test if this string is allowed
        for blocked_response in DEACTIVATED_RESPONSES:
            valid = valid and (blocked_response not in string)
        #if the string isn't blocked
        if valid:
            if NORMAL_PRINT_MODE:
                print(string)
            else:
                print(BOT_NAME, end = "")
                sys.stdout.flush()
                time.sleep(INITIAL_PAUSE)
                for char in string:
                    print(char, end = "")
                    sys.stdout.flush()
                    if char == " ":
                        time.sleep(SPACE_PAUSE)
                    else:
                        time.sleep(CHAR_PAUSE)
                print("") #print new line character

    # Pre:  
    # Post: A random response from self.dict is returned
    def random_response(self):
        return (random.choice(list(self.dict.keys())))

    # Pre:  valid key exists in self.dict.keys()
    # Post: A response from self.dict[valid_key]
    def _decide_what_to_say(self, valid_key):
        #if the phrase has been heard but has no responses
        if len(self.dict[valid_key]) == 0:
            self.post(KEY_NO_VALUE%valid_key)
            return (self.random_response())
        else:
            possibilities = []
            for word in self.dict[valid_key]:
                possibilities += [word for i in range(self.dict[valid_key][word])]

            # possibilities = [self.dict[valid_key][curr] for i in
            #                  range(self.dict[valid_key][curr]) for
            #                  curr in self.dict[valid_key]]
            self.post(FOUND_POSSIBILITES+str(possibilities))
            return (random.choice(possibilities))

    # Pre:  some_input not in self.dict.keys() and of type string
    # Post: All sub strings > len(SMALLEST_SUBPHRASE) are tested for
    #       responses in self.dict, if no response is found, then a
    #       random response is returned
    def _test_sub_expressions(self, some_input):
        words = some_input.split()
        #for sub_phrases of all lengths down to the smallest accepted
        for phrase_len in range(len(words)-1, SMALLEST_SUBPHRASE, -1):
            #for all valid sub phrases
            for start in range(0, len(words)-phrase_len+1):
                sub_phrase = INIT_STR
                #build the sub phrase
                for word in range(phrase_len): 
                    sub_phrase += words[start+word] + SPACE
                sub_phrase = sub_phrase.strip()
                if sub_phrase in self.dict:
                    self.post(FOUND_SUBPHRASE+sub_phrase)
                    return self._decide_what_to_say(sub_phrase)
        return self.random_response()

    # Pre:  key is a valid key in self.dict, new is the new response
    #       to be added to that key
    # Post: If new already existed, it's occurance is incremented,
    #       otherwise it is added with an occurance of 1
    def _add_new_response(self, key, new):
        if new in self.dict[key]:
            self.dict[key][new] += 1
        else:
            self.dict[key][new] = 1

    # Pre:  new is a string that will be added to self.dict
    # Post: That new expression is initialized
    def _add_new_expression(self, new):
        self.dict[new] = {}

    # Pre:  some_input not in self.dict.keys() and of type string
    # Post: the new expression is added to self.dict, and the input is
    #       sent to be processed for subphrase responses
    def _im_lost(self, some_input):
        self.post(NEW_EXPRESSION_RESPONSE)
        self._add_new_expression(some_input)
        return (self._test_sub_expressions(some_input))

    # Pre:  some_input is a possible key in self.dict (string type)
    # Post: A response
    def respond(self, some_input):
        if some_input in self.dict:
            return (self._decide_what_to_say(some_input))
        else:
            return (self._im_lost(some_input))

    # Pre:  
    # Post: Chatbot protocol begins
    def run_chatbot(self):
        user_input = INIT_STR #holder for user input
        response = INIT_STR #holder for the current response
        previous_response = INIT_STR #holder for previous chatbot response
        while user_input not in EXIT_RESPONSES:
            if NORMAL_PRINT_MODE:
                user_input = simplify(input(SIMPLE_PROMPT).strip())
            else:
                user_input = simplify(input(USER_NAME).strip())

            response = self.respond(user_input) #respond to what
                                                #the user said 
            #ASSERT: user_input is a key in self.dict, if it wasn't
            #        already, it should have been created in _im_lost
            if previous_response != INIT_STR:
                #if the last expression said wasn't already a key
                if previous_response not in self.dict:
                    #make it a key with an empty dictionary
                    self.dict[previous_response] = {}
                self._add_new_response(previous_response, user_input)
            #   ^^ adds what the user said as a valid response
            self.post(response) #talk to the user
            previous_response = response
        self._save_my_dictionary()

    # Pre:  
    # Post: Prompt for edit mode, accordingly a fxn is executed
    def start_session(self):
        if not NORMAL_PRINT_MODE:
            edit = prompt(ENTER_EDIT_MODE, YES)
            if not edit:
                self.run_chatbot()
            else:
                self.post(WELCOME_EDIT)
                editor.edit(self)
        else:
            self.run_chatbot()

if __name__ == "__main__":
    main = Chatbot(DICTIONARY)
    main.start_session()
