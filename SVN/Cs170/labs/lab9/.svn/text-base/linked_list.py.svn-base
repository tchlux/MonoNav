
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
                return str(self.object)+","+str(self.next)

    class _Iterator:
        #Method:This method initializes the iterator
        #Pre:   A type=LinkedList object is given
        #Att.s: LinkedList.first (type=Node)
        #Post:  self.node is set to LinkedList.first
        def __init__(self, linked_list):
            self.node = linked_list.first

        #Method:This method returns the next object of the iterator
        #Pre:   No given arguments
        #Att.s: self.node (type=Node), self.node.object (type=data)
        #Post:  the object stored
        def __next__(self):
            if self.node != None:
                current = self.node
                self.node = self.node.next
                return current.object
            else:
                raise(StopIteration)

##############################LINKED LIST BEGINS#####################

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

    #Method:This method removes the first item in the LinkedList and
    #       pops it back
    #Pre:   The method is called
    #Post:  IndexError for empty list, otherwise the self.first is
    #       removed and the size is incremented down by one, return
    #       first.object
    def remove_first(self):
        first = self.first
        if self.first == None:
            raise(IndexError("The current list is empty"))
        elif self.first.next != None:
            self.first = self.first.next
            self.size -= 1
        else:
            self.first = None
            self.size -= 1
        return first.object
        


    #Method: This method removes an arbitrary element from the list.
    #Pre:    an element is given (which is of the same type as the
    #        objects in the linked list being searched.
    #Att.s:  self.first (type=Node)
    #Post:   The element specified is removed from the linked list,
    #        otherwise a ValueError is raised
    def remove(self, element):
        previous_node = None
        node = self.first
        while element != node.object:
            #Special case, empty list
            if node == None:
                raise(IndexError("Empty list."))
            #Special case, value not in list
            elif node.next == None:
                raise(ValueError("That value is not in this linked list."))
            else:
                previous_node = node
                node = node.next
        #Special case, last element in linked list
        if node.next == None:
            previous_node.next = None
        #Special case, first element in linked list
        elif previous_node == None:
            self.first = node.next
        #Normal case
        else:

            previous_node.next = node.next
        self.size -= 1

    #Method:This method iterates through the linked list
    #Pre:   A loop or form of iterator is called
    #Att.s: self (type=LinkedList), _Iterator (type=Class)
    #Post:  The iterator instance is returned
    def __iter__(self):
        return self._Iterator(self)

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
    #       long integer
    #Pre:   An integer is given
    #Post:  A linked list is created 
    def __init__(self, integer):
        string = str(integer)
        self.integer = LinkedList()
        for number in string:
            self.integer.add_last(int(number))

    #Method:This method will return the size of the integer in terms
    #       of actual numerical length
    #Pre:   The len method is called
    #Post:  the length of the linked list containing each integer is
    #       returned
    def __len__(self):
        return self.integer.size

    #Method:This method will return the string form of the integer 
    #Pre:   The string method is called
    #Post:  The number is printed
    def __str__(self):
        return str(self.integer)
        
    #Method:This method will return whether or not two
    #       ArbitrarIntegers are equal
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
