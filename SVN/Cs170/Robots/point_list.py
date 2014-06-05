
class PointList:

    class _Node:
        #Method:Constructor, this will create a Node object
        #Pre:   The value for the object, and the next Node in the list
        #Post:  The node is created in memory
        def __init__(self, obj, nxt, degree):
            self.point = obj
            self.degree = degree
            self.next = nxt
            self.occurance = 0

        #Method:This method returns the string version of the stored
        #object comma separated
        #Pre:   None, the string method is called
        #Post:  The string version of the self.object is returned
        def __str__(self):
            if self.next == None:
                return str(self.point)
            else:
                return str(self.point)+","+str(self.next)

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
                return current
            else:
                raise(StopIteration)

##############################LINKED LIST BEGINS#####################

    #Method:Constructor, this method initializes the linked list size
    #       and first attributes
    #Pre:   The range of degree differences that will be considered
    #       the same
    #Post:  The attributes are initialized for later use
    def __init__(self, degree_threshold):
        self.degree_threshold = degree_threshold
        self.size = 0
        self.first = None

    #Method:This method checks to see if the difference between two
    #       degrees lies within the given threshold
    #Pre:   A node, and a degree are given to be compared
    #Att's: self.degree_threshold (type=Float)
    #Post:  Boolean response to within the threshold or not
    def check_threshold(self, node, new_degree):
        if abs(node.degree-new_degree) < self.degree_threshold:
            return True
        else:
            return False

    #Method:This method will insert a new point into the appropriate
    #       place in the current linked list of poitns
    #Pre:   The new object is given along with the degree associated
    #       with it, the degree should be in the range 1-360 the new
    #       object should be a tuple x,y location and the degree
    #       type=Float 
    #Att's: self._Node (type=PrivateClass)
    #       self.first (type=_Node)
    #       self.check_threshold (type=Method)
    #Post:  The new point is inserted into the appropriate place in
    #       the list
    def insert(self, new_object, new_degree):
        #Special case: Empty list
        if self.size == 0:
            self.first = self._Node(new_object, None, new_degree)
        else:
            previous = None
            node = self.first
            #Cycles the list until the correct place is found
            while (node.degree < new_degree) and not self.check_threshold(node, new_degree) and node.next != None:
                previous = node
                node = node.next
            #Special case: reached the end of the list
            if node.next == None:
                node.next = self._Node(new_object, None, new_degree)
            #Special case: The diff in degrees lies within threshold
            elif self.check_threshold(node, new_degree):
                node.occurance += 1
            #Special case: First object in list
            elif previous == None:
                self.first = self._Node(new_object, node, new_degree)
            #Normal case, just insert the point
            else:
                previous.next = self._Node(new_object, node, new_degree)
        self.size += 1

    #Method:This method removes the first item in the LinkedList and
    #       pops it back
    #Pre:   The method is called
    #Post:  IndexError for empty list, otherwise the self.first is
    #       removed and the size is incremented down by one, return
    #       first node
    def pop_first(self):
        first = self.first
        if self.first == None:
            raise(IndexError("The current list is empty"))
        elif self.first.next != None:
            self.first = self.first.next
            self.size -= 1
        else:
            self.first = None
            self.size -= 1
        return first

    #Method: This method removes an arbitrary element from the list.
    #Pre:    an element is given (which is of the same type as the
    #        objects in the linked list being searched.
    #Att.s:  self.first (type=Node)
    #Post:   The element specified is removed from the linked list,
    #        otherwise a ValueError is raised
    def remove(self, element):
        previous_node = None
        node = self.first
        while element != node.point:
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
