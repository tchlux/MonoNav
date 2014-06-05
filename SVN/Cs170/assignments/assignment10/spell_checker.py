import sys
import trie

#Search Term:  todo
NUMBER_OF_SUGGESTIONS = 6


#Class:   This is the spell checker class
#Runtime: < 1 second
#Mainloop:Yes, for interactive mode
class SpellChecker:
    #Method:Consructor, creates all necessary attributes for the spch class
    #Pre:   The word file can be given as a command line argument or
    #       regular argument
    #Att's: self.dictionary (type=Trie class)
    #Post:  The spell checker is initialized
    def __init__(self, word_file=None):
        self.dictionary = trie.Trie()
        self._create_dictionary(self._import_dict(word_file))

    #Method:This method imports the dictionary and returns it as a
    #       list of words
    #Pre:   A filename is given as a string or None
    #Att's: None required
    #Post:  A list of each line in the specified file are returned, an
    #       exception is raised if no filename was given
    def _import_dict(self, filename):
        #This is a check to see if the filename was given on
        #initialization or as a system argument, if neither raises
        #exception
        try:
            filename = sys.argv[1]
            print("I see you at the command line.")
        except IndexError:
            if filename == None:
                raise Exception("There needs to be file name given either upon initialization or as a system argument.")
        #This is what opens the file
        with open(filename) as dictionary:
            line_list = dictionary.readlines()
            dictionary.close()
        return line_list

    #Method:This method creates the dictionary trie given the list of lines
    #Pre:   Line list is given as a list of strings (one word per string)
    #Att's: self.add_word (type=Method)
    #Post:  self.dictionary is filled with words from the line_list
    def _create_dictionary(self, line_list):
        for word in line_list:
            if word.strip().isalpha():
                self.add_word(word.strip().lower())

    #Method:This method will add a word to the dictionary trie
    #Pre:   The word is given as a string
    #Att's: self.dictionary (type=Trie class)
    #Post:  The word is added to the trie
    def add_word(self, word):
        self.dictionary.add_word(word)

    #Method:This method will return true or false for if a word exists
    #       in self.dictionary
    #Pre:   a word is given as a string
    #Att's: self.dictionary (type=Trie class)
    #Post:  Boolean response for if the word exists in the trie
    def find_word(self, word):
        return self.dictionary.word_exists(word)

    #Method:This method gives the hamming distance between two words
    #Pre:   The two words are given as strings
    #Att's: None
    #Post:  The hamming distance is returned
    def hamming_distance(self, word1, word2):
        difference = 0
        for char in range(len(word1)):
            if word1[char] != word2[char]:
                difference += 1
        return difference

    #Method:This method will provied similarly spelled words given a word
    #Pre:   A word is given as a string
    #Att's: self.dictionary (type=Trie)
    #       self.hamming_distance (type=Method)
    #Post:  A list of other words possible is given
    def provide_suggestion(self, word):
        store = None
        for level in self.dictionary:
            if len(level[0]) == len(word):
                store = level
                hamming_distance = dict([(self.hamming_distance(word, palabra),palabra) for palabra in level])
                break
        suggestions = []
        for i in range(NUMBER_OF_SUGGESTIONS):
            try:
                hd = min(list(hamming_distance.keys()))
                suggestions.append(hamming_distance.pop(hd))
            except ValueError: #This happens if the length of
                #possible words is shorter than the
                #NUMBER_OF_SUGGESTIONS global variable
                break
        return suggestions

    #Method:This method will run the terminal mainloop
    #Pre:   None
    #Att's: self.find_word (type=Method)
    #       self.provide_suggestion (type=Method)
    #Post:  The interactive spell checker is run
    def mainloop(self):
        response = input("Word? ")
        while response != "":
            if not self.find_word(response):
                print("One of these?")
                print(self.provide_suggestion(response))
            else:
                print(self.find_word(response))
            response = input("Word? ").strip().lower()

if __name__ == "__main__":
    spch = SpellChecker("words.txt")
    spch.mainloop()


