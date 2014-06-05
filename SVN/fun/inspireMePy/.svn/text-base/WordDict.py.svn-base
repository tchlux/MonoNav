import pickle
import math
import random
import os

FILE_NAME = "connections.txt"
SAVE_PROMPT = 'Do you want to save over the old dictionary in '+FILE_NAME+'? '
SUCCESSFUL_SAVE = "Dictionary successfully edited in " +FILE_NAME+".txt"
UNSUCCESSFUL_SAVE = "Editing cancelled"
NON_ALPHA_ERROR = "WARNING:: There was a non-alphabetic character in the given string."
NO_WORD_ERROR = "WARNING:: The word that was given does not exist in the dictionary."
NO_CONNECTION_ERROR = "WARNING:: The connection that was given does not exist for the given word."
BAD_CONNECTION_GIVEN = "WARNING:: A bad connection was given."
REPEATED_CONNECTION_GIVEN = "WARNING:: That connection has already been made."
NO_WORD_FOUND = "Sorry, no word was found!! ERROR ERROR"

class WordDict:
    # Pre:  WordList class created
    # Post: The word_list is brough in from the file
    def __init__(self):
        self.word_dict = {}
        self._open_file()
        self.word = ''

    # Pre:  
    # Post: Prompts the user through the terminal if they are sure
    #       they want to save the updated dictionary
    def terminal_prompt_save(self):
        yes_no = input(SAVE_PROMPT)
        edit_state = ""
        while yes_no != "yes" and yes_no != "no":
            yes_no = input('\nyes or no only please: ')
        if yes_no == "yes":
            save_to_file()
            edit_state = SUCCESSFUL_SAVE
        else:
            edit_state = UNSUCCESSFUL_SAVE
        print(edit_state, "\nDone")

    # Pre:  
    # Post: The word_dict is saved to the file
    def save_to_file(self, word_dict):
        f = open(FILE_NAME, 'wb')
        pickle.dump(self.word_dict, f)
        f.close()

    # Pre:  
    # Post: if the file exists, it is opened into word_dict
    def _open_file(self):
        if os.path.exists(FILE_NAME):
            f = open(FILE_NAME, 'rb')
            self.word_dict = pickle.load(f)
            f.close()

    # Pre:  word is a string with one word in it
    # Post: The word is stripped and made lower case
    def check_and_fix_word(self, word):
        if not word.isalpha():
            raise(Exception(NON_ALPHA_ERROR))
        word = word.strip().lower()
        return word

    # Pre:  word is a string key value in word_dict
    #       connection is a string word
    # Post: word and connection are already checked by
    #       check_and_fix_word
    def add_connection(self, word, connection):
        if connection != '':
            if word in self.word_dict:
                if connection not in self.word_dict[word]:
                    self.word_dict[word].append(connection)
                else:
                    raise(Exception(REPEATED_CONNECTION_GIVEN))
            else:
                self.word_dict[word] = [connection]
            if connection not in self.word_dict:
                self.word_dict[connection] = []
        else:
            raise(Exception(BAD_CONNECTION_GIVEN))

    # Pre:  A word is given, a connection can be given, if not the
    #       entire word will be deleted.
    # Post: The given connection is removed from the word, if no
    #       connection was given then whole word is removed
    def remove_word_connection(self, word, connection=''):
        if word in self.word_dict:
            if connection == '':
                self.word_dict.remove(word)
            elif connection in self.word_dict[word]:
                self.word_dict[word].remove(connection)
            else:
                raise(Exception(NO_CONNECTION_ERROR))
        else:
            raise(Exception(NO_WORD_ERROR))

    # Pre:  
    # Post: This function will save a word that has no, or very few
    #       connections, and needs more to the word attribute
    def build_connections(self):
        search = 0
        found = False
        while not found:
            for word in self.word_dict:
                if len(self.word_dict[word]) == search:
                    self.word = word
            search += 1
        self.word = NO_WORD_FOUND

    # Pre:  word is a valid key in self.word_dict, levels (>= 1 is
    #       optionally given and represents the maximum depth of
    #       connections that should be returned
    # Post: A list of all the words that are connected to that level
    #       are returned
    def connect(self, word, levels=1):
        if word in self.word_dict:
            final_list = []
            if levels <= 1:            
                final_list = self.word_dict[word]
            else:
                for connection in self.word_dict[word]:
                    final_list += connection #add the word
                    for word in connect(connection, levels-1): #cycle its
                                                             #connections
                        if word not in final_list: #if it's not there
                            final_list += word     #add it
            return final_list

# Pre:  
# Post: The WordDict is operated on appropriately for the connections
# to be created
def inspire_me():
    main_dict = WordDict()
    response = input(PROMPT)
    while response != "__STOP__":
        WordDict.run()

    
if __name__ == "__main__":
    inspire_me()
