from linked_list import LinkedList

WORD_LENGTH_QUESTION = " How many letters long of a word do you want?? "
GUESS_LETTER_QUESTION = " Uh oh.. I can sense your failure. What letter will you guess? "
PLAY_AGAIN_QUESTION = " Would you like to try again you desperate fool?? (yes/no) "
NO_WORDS_THAT_LENGTH_ERROR = " Sorry, we don't have any evil words that length.\n Maybe you could try another length word?"
WRONG_TYPE_ERROR = "\n That is not the right type response!"
ALREADY_GUESSED_MESSAGE = "\n You've already guessed that letter!\n"
NOT_VALID_GUESS_MESSAGE = "\nThat's not a valid guess!\n"
TOO_MANY_LETTERS_MESSAGE = "\nOne letter only please!\n"
EVIL_WINS = " MWHAhahahHAHahHahAH, EVILhangman enterprise wins again!!!\n The answer was "
EVIL_LOOSES = " This is impossible!! How did you win??\n NOOOOoOoooooOOOooOooooooOOoO!"

#The above Global Variables are the texts that are posted to the user
#upon certain occasions, they are sort of self explanitory, if you
#want to know where they appear I recommend Ctrl+s "Global Variable"

ALLOWED_GUESSES = 8 #This is the set number of allowed guesses for the
                    #user before the game ends
WORD_FILENAME = "words.txt" #This is the name of the file that
                            #contains a list of words seperated by new
                            #line characters
HANGMAN_FILENAME = "hangman_drawing.txt"



#Class:   Hangman the wrong way.. Mwhahaha
#Runtime: < 5 seconds per loop
#Mainloop:Yes
class EvilHangman:
    #Method:This will construct all necessary attributes for the class
    #Pre:   Class is initialized
    #Post:  EvilHangman begins
    def __init__(self):
        self.remaining_guesses = ALLOWED_GUESSES
        self.words_list = LinkedList()
        self.game_over = False
        self.guessed_letters = []
        self.length_word = 0
        self.correct_letters = []

    #Method:This method will build the words dictionary based on the
    #       word length specified by the user
    #Pre:   The method is called
    #Att's: self.words_list (type=None)
    #       self.length_word (type=Integer)
    #Post:  self.words_list is filled with all words that contain only
    #       alphabetic characters
    def _build_words_dictionary(self):
        with open(WORD_FILENAME) as words:
            word_list = words.readlines()
            words.close()
        for word in word_list:
            w = word.strip()
            usable = True
            for char in w:
                if not char.isalpha():
                    usable = False
            if len(w) != self.length_word:
                usable = False
            if usable:
                self.words_list.append(w)
        if len(self.words_list) == 0:
            print(NO_WORDS_THAT_LENGTH_ERROR)

    #Method:This will ask the user the given question and return their
    #       answer.  It will also preform a series of checks to see if
    #       the type is the type specified and if the user wants to exit
    #Pre:   A question is given in string format, optionally the type
    #       of answer expected is given.  The question doesn't need to
    #       have a new line character before it.
    #Att's: self.game_over (type=Boolean)
    #       self._return_user_input (type=Method)
    #Post:  The response is returned in string format
    def _return_user_input(self, question, type_expected=str):
        response = input("\n"+question)
        response = response.strip()
        if response == "exit":
            self.game_over = True
            return "exit"
        if type_expected == int:
            try:
                response = int(response)
            except ValueError:
                print(WRONG_TYPE_ERROR)
                return self._return_user_input(question, type_expected)
        else:
            response = response.lower()
        print("\n")
        return response


    #Method:This will draw the hangman based on how many guesses the
    #       user has left
    #Pre:   
    #Att's: self.remaining_guesses
    #Post:  
    def _draw_hangman(self):
        with open(HANGMAN_FILENAME) as pic:
            drawing = pic.readlines()
            pic.close()
        pic_percent = 1 - (self.remaining_guesses/ALLOWED_GUESSES)
        for i in range(len(drawing)):
            percent_drawn = (i/len(drawing))
            if percent_drawn < pic_percent or i <= 1:
                print(drawing[i][0:-1], end="\n")
            else:
                print(drawing[i][0:7], end="\n")

    #Method:This ugly set of loops goes through the correct letters
    #       and finds out where they commonly appear in the words
    #       family of a letter in self.words_list. Once the letter is
    #       found in a place, it's index is recorded (letter key in
    #       the dictionary is created if it does not exist)
    #Pre:   the method is called
    #Att's: self.correct_letters (type=List)
    #       self.words_list (type=LinkedList)
    #       self._return_word_family (type=Method)
    #Post:  The locations dictionary is returned, with keys as letters
    #       that exist in the words, and their values are the indices
    #       into the word where the letter exists
    def _build_locations_in_word_dictionary(self):
        locations = {}
        for letter in self.correct_letters:
            word = self.words_list.first.object
            w_fam = self._return_word_family(word, letter)
            for ind in range(len(w_fam)):
                if w_fam[ind] == "1":
                    if letter in locations:
                        locations[letter].append(ind)
                    else:
                        locations[letter] = [ind]
        return locations

    #Method:This method will draw the spaces for the word and fill
    #       them in with the correct guesses in the appropriate
    #       locations 
    #Pre:   The method is called
    #Att's: self.length_word (type=Integer)
    #       self.game_over (type=Boolean)
    #       self._build_locations_in_word_dictionary (type=Method)
    #Post:  The little word panel is drawn to the screen with "_" for
    #       unknown letters and the correctly guessed letters in their
    #       locations
    def _draw_word(self):
        locations = self._build_locations_in_word_dictionary()
        string = ": "
        for i in range(self.length_word):
            changed = False
            for key in locations:
                if i in locations[key]:
                    string += key+" "
                    changed = True
            if not changed:
                string += "_ "
        if "_" not in string:
            self.game_over = True
        print(string)

    #Method:Thie method takes a dictionary and returns the key with
    #       the highest numerical value
    #Pre:   A dictionary is given with keys as stings and values as
    #       integers
    #Att's: None required
    #Post:  A key that has the highest value in the dictionary
    def _return_max_of_dictionary(self, dictionary):
        key_list = list(dictionary.keys())
        value_list = list(dictionary.values())
        index = value_list.index(max(value_list))
        return key_list[index]

    #Method:This method returns the binary string family of a word
    #Pre:   The word is given as a string, as well as the letter
    #Att's: None required
    #Post:  The family of the word is returned as a string of 0's and
    #       1's 
    def _return_word_family(self, word, letter):
        family = ""
        for char in word:
            if char == letter:
                family += "1"
            else:
                family += "0"
        return family

    #Method:This method will remove the words not in a given family
    #       from the answer list
    #Pre:   The family THAT WILL BE KEPT is given as a string of 0's
    #       and 1's (1 for the letter) The lette is given as a string
    #       as well 
    #Att's: self.words_list (type=LinkedList)
    #       self._return_word_family (type=Method)
    #Post:  The words not in the given family are removed from the
    #       linked list self.words_list
    def _remove_words_not_in_family(self, family, letter):
        for word in self.words_list:
            w_fam = self._return_word_family(word, letter)
            if w_fam != family:
                self.words_list.remove(word)

    #Method:This method will build the word family dictionary for a
    #       guessed letter
    #Pre:   The guessed letter is given as a string
    #Att's: self.words_list (type=LinkedList)
    #       self._return_word_family (type=Method)
    #Post:  The family dictionary is returned
    def _build_family_dictionary(self, guessed_letter):
        dictionary = {}
        for word in self.words_list:
            family = self._return_word_family(word, guessed_letter)
            if family in dictionary:
                dictionary[family] += 1
            else:
                dictionary[family] = 1
        return dictionary

    #Method:This method adjusts the dictionary of responses according
    #       to the users response, this is what makes the game evil in
    #       a sense.  A dictionary of word families is built, then the
    #       word family with the most possible answers is used as the
    #       answer choice, special case: if there is only one word in
    #       the remaining dictioanries, the program will try to take
    #       the one with no occurances of the guessed letter
    #Pre:   The guessed letter is given as a string
    #Att's: self.words_list (type=LinkedList)
    #       self.correct_letters (type=List)
    #       self.guessed_letters (type=List)
    #       self.remaining_guesses (type=Integer)
    #       self._build_family_dictionary (type=Method)
    #       self._return_max_of_dictionary (type=Method)
    #       self._remove_words_not_in_family (type=Method)
    #Post:  The self.words_list is adjusted according to the words
    #       families produced, and the remaining guesses,
    #       correct_guesses, and correct_letters attributes are
    #       adjusted according to the new situation
    def _adjust_answer_accordingly(self, guessed_letter):
        current_length = len(self.words_list)
        dictionary = self._build_family_dictionary(guessed_letter)
        family = self._return_max_of_dictionary(dictionary)
        if max(dictionary.values()) == 1:
            for key in dictionary:
                if "1" not in key:
                    family = key
        self._remove_words_not_in_family(family, guessed_letter)
        if "1" in family:
            self.correct_letters.append(guessed_letter)
        else:
            self.guessed_letters.append(guessed_letter)
            self.remaining_guesses -= 1

    #Method:This method is used to check the various types of response
    #       the user could give, it will respond accordingly, or
    #       otherwise call self._adjust_anwer with the guess
    #Pre:   The guess is given as a string
    #Att's: self._return_user_input (type=Method)
    #       self.correct_letters (type=List)
    #       self.guessed_letter (type=List)
    #       self._adjust_answer_accordingly (type=Method)
    #Post:  The corresponding function is preformed, either a print
    #       statement asking for a new entry, or the game continues as
    #       it normally would
    def _check_guess(self, guess):
        if guess == "exit":
            print(" I understand")
        elif guess in self.guessed_letters or guess in self.correct_letters:
            print(ALREADY_GUESSED_MESSAGE)
            self._check_guess(self._return_user_input(GUESS_LETTER_QUESTION))
        elif guess == "":
            print(NOT_VALID_GUESS_MESSAGE)
            self._check_guess(self._return_user_input(GUESS_LETTER_QUESTION))
        elif len(guess) > 1:
            print(TOO_MANY_LETTERS_MESSAGE)
            self._check_guess(self._return_user_input(GUESS_LETTER_QUESTION))
        else:
            self._adjust_answer_accordingly(guess)

    #Method:This method will continue looping and asking the user to guess
    #       letters, then printing the results
    #Pre:   The method is called
    #Att's: self.game_over (type=Boolean)
    #       self.words_list (type=LinkedList)
    #       self.guessed_letters (type=List)
    #       self.remaining_guesses (type=Integer)
    #       self._draw_hangman (type=Method)
    #       self._draw_word (type=Method)
    #       self._check_guess (type=Method)
    #       self._return_user_input (type=Method)
    #       self._game_over (type=Method)
    #Post:  The game is run as it should be, there is a special case
    #       after self._draw_word is run that may end the game so
    #       there is an if statement that informally breaks the while
    #       loop if they guess every letter in the word
    def _main_loop(self):
        while not self.game_over:
            self._draw_hangman()
            print("")
            print(self.guessed_letters)
            self._draw_word()
            #Informal break on special case: completed word
            if self.game_over:
                break
            print("You only have "+str(self.remaining_guesses)+" guesses remaining!")
            self._check_guess(self._return_user_input(GUESS_LETTER_QUESTION))
            if self.remaining_guesses == 0:
                self.game_over = True
        self._game_over()

    #Method:This method displays the gameover screen, win/loss and
    #       prompts if they want to play again
    #Pre:   The method is called
    #Att's: self.remaining_guesses (type=Integer)
    #       self.words_list (type=LinkedList)
    #       self._return_user_input (type=Method)
    #       self.__init__ (type=Method)
    #       self.game (type=Method)
    #Post:  The game is either ended or started over, based on user
    #       response
    def _game_over(self):
        print("\n The game is over..")
        if self.remaining_guesses > 0:
            print(EVIL_LOOSES)
        else:
            print(EVIL_WINS+'"'+self.words_list.first.object+'"!')
        play_again = self._return_user_input(PLAY_AGAIN_QUESTION)
        if play_again == "yes":
            self.__init__()
            self.game()

    #Method:This will show the intro to hangman once it begins
    #Pre:   called
    #Att's: None required
    #Post:  The introduction is printed to the terminal
    def _intro_to_hangman(self):
        print("\n\n\n        Welcome all, ladies and gentlemen alike")
        print("  Do you think you can win the wonderful game of hangman??")
        print("      We here at EVILhangman enterprise don't think so.")
        print("         Lets put you to the test!  Mwhahahahaa")

    #Method:This is the method that will be called to run the game
    #Pre:   The method is called
    #Att's: self.words_list (type=LinkedList)
    #       self.length_word (type=Integer)
    #       self._intro_to_hangman (type=Method)
    #       self._return_user_input (type=Method)
    #       self._build_words_dictionary (type=Method)
    #       self._main_loop (type=Method)
    #Post:  The game is initialized
    def game(self):
        self._intro_to_hangman()
        while len(self.words_list) == 0:
            self.length_word = self._return_user_input(WORD_LENGTH_QUESTION, int)
            self._build_words_dictionary()
        self._main_loop()

if __name__ == "__main__":
    a = EvilHangman()
    a.game()

