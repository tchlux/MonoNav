
class LinkedList:

    class _Node:
        #Method:Constructor, this will create a Node object
        #Pre:   The value for the object, and the next Node in the list
        #Post:  The node is created in memory
        def __init__(self, obj, nxt):
            self.object = obj
            self.next = nxt

        #Method:This method returns the string version of the stored
        #object comma separated
        #Pre:   None, the string method is called
        #Post:  The string version of the self.object is returned
        def __str__(self):
            if self.next == None:
                return str(self.object)
            else:
                return str(self.object)+str(self.next)

    #Method:Constructor, this method initializes the linked list size
    #and first attributes
    #Pre:   None, the class is created
    #Post:  The attributes are initialized for later use
    def __init__(self):
        self.size = 0
        self.first = None

    #Method:This method adds a value to the end of the LinkedList
    #Pre:   The new object value is given
    #Post:  The new object is added to the end of the LinkedList
    def add_last(self, new_object):
        if self.size == 0:
            self.first = self._Node(new_object, None)
            self.size = 1
        else:
            nxt = self.first
            while nxt.next != None:
                nxt = nxt.next
            nxt.next = self._Node(new_object, None)
            self.size += 1

    #Method:This method returns the first element in the LinkedList
    #Pre:   The method is called
    #Post:  Whatever self.first references is returned
    def get_first(self):
        return self.first

    #Method:This method removes the first item in the LinkedList
    #Pre:   The method is called
    #Post:  IndexError for empty list, otherwise the self.first is
    #removed and the size is incremented down by one
    def remove_first(self):
        if self.first == None:
            raise(IndexError("The current list is empty"))
        elif self.first.next != None:
            self.first = self.first.next
            self.size -= 1
        else:
            self.first = None
            self.size -= 1

    #This method will print all of the values of the linked list class
    #Pre: The string method is called
    #Post: Either the whole list is printed or the list is said to be empty
    def __str__(self):
        if self.size >= 1:
            return str(self.first)
        else:
            return "Sorry this linked list is empty."


class BigInteger:
    #Method:Constructor, this method initializes an arbitrarily
    #long integer
    #Pre:   An integer is given
    #Post:  A linked list is created 
    def __init__(self, integer):
        string = str(integer)
        self.integer = LinkedList()
        for number in string:
            self.integer.add_last(int(number))

    #Method:This method will return the size of the integer in terms
    #of actual numerical length
    #Pre:   The len method is called
    #Post:  the length of the linked list containing each integer is
    # returned
    def __len__(self):
        return self.integer.size

    #Method:This method will return the string form of the integer 
    #Pre:   The string method is called
    #Post:  The number is printed
    def __str__(self):
        return str(self.integer)
        
    #Method:This method will return whether or not two
    #ArbitrarIntegers are equal
    #Pre:   The other BigInteger is given
    #Post:  True or false is returned for equality
    def __eq__(self, other):
        mynxt = self.integer.first
        urnxt = other.integer.first
        equal = mynxt.object == urnxt.object
        while mynxt.next != None or urnxt.next != None:
            equal = mynxt.next.object == urnxt.next.object
            mynxt, urnxt = mynxt.next, urnxt.next
        return equal

    #Method:This method will add two BigIntegers together
    #Pre:   The other BigInteger is given
    #Post:  A new BigInteger with the value of the addition of
    #the current and the other is returned
    def __add__(self, other):
        int1 = int(str(self))
        int2 = int(str(other))
        return BigInteger(int1+int2)
