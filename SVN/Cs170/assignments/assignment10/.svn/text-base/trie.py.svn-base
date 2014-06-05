
#Class:   This is the class for the word trie
#Mainloop:No
class Trie:
    #Class:   This is the private class for a node in the trie
    class _Node:
        #Method:Constructor, creates all attributes
        #Pre:   parent node (_Node), letter (String), and next level
        #       (List) can be provided
        #Att's: created here
        #Post:  The _Node is essentially inserted into the trie
        def __init__(self, parent, letter):
            self.parent = parent
            self.letter = letter
            self.terminator = False
            self.next_level = []

        #Method:This will return the string of the word in reverse order
        #Pre:   The string method is called on this node
        #Att's: self.parent (type=_Node)
        #       self.letter (type=String)
        #Post:  The string from the current node and up to root is
        #       returned 
        def __str__(self):
            if self.parent == None:
                return self.letter
            else:
                return str(self.parent)+str(self.letter)

        #Method:This method checks self.letter's equality with a given letter
        #Pre:   A letter is given as a string
        #Att's: self.letter (type=String)
        #Post:  the equality of the two strings are returned
        def __eq__(self, letter):
            return self.letter == letter

    #Class:   This class iterates through words in the trie
    class _Iterator:
        #Method:Constructor
        #Pre:   trie is given (Trie)
        #Att's: created here
        #Post:  the trie is iterated through
        def __init__(self, trie):
            self.node_list = [trie.root]

        #Method:This method cycles through the words in each level of
        #       the trie
        #Pre:   called by iterator
        #Att's: self.node_list (type=List)
        #Post:  the next level (list of words of certain length) is
        #       given, this list can be empty.  They are all strings
        def __next__(self):
            #As long as the 'Queue' has something in it
            if len(self.node_list) > 0:
                curr_level_list = []
                #Cycle through the current nodes
                for node in self.node_list:
                    #Add all the child nodes to a new list
                    [curr_level_list.append(new_node) for new_node in node.next_level]
                #Set the attribute equal to the new list (next level)
                self.node_list = curr_level_list[:]
                #Return the words that are in the current level
                return [str(node) for node in curr_level_list if node.terminator]
            else:
                raise(StopIteration)

    #Method:Constructor for Trie
    #Pre:   Trie is created
    #Att's: self.root =>> _Node
    #Post:  the trie is ready to be added to
    def __init__(self):
        self.root = self._Node(None,None)

    #Method:This method adds all necessary nodes and values for the
    #       given word to the self
    #Pre:   Word is given as a string
    #Att's: self.root (type=_Node)
    #       self._add_letter (type=Method)
    #Post:  The word is added to the trie
    def add_word(self, word):
        parent = self.root
        for letter in word:
            temp = parent
            if letter in parent.next_level:
                parent = parent.next_level[parent.next_level.index(letter)]
            else:
                parent = self._add_letter(parent, letter)
        parent.terminator = True

    #Method:This method adds a letter to the node provided
    #Pre:   a node (_Node) is given, and  a letter (String)
    #Att's: self._Node (type=Private Class)
    #Post:  the node.next_level is given another letter node (_Node)
    def _add_letter(self, node, letter):
        new = self._Node(node, letter)
        node.next_level.append(new)
        return new

    #Method:This method returns a bool for whether or not a given word
    #       exists in self
    #Pre:   A word is given as a string
    #Att's: self.root (type=_Node)
    #Post:  A boolean is returned for if the word does exist
    def word_exists(self, word):
        early_break = False
        parent = self.root
        for letter in word:
            if letter in parent.next_level:
                parent = parent.next_level[parent.next_level.index(letter)]
            else:
                early_break = True
                break
        return not early_break and parent.terminator

    #Method:This method iterates through the Trie
    #Pre:   A loop or form of iterator is called
    #Att.s: self (type=Trie), _Iterator (type=Class)
    #Post:  The iterator instance is returned
    def __iter__(self):
        return self._Iterator(self)
