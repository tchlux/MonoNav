from linked_list import LinkedList
#Class:   
#Runtime: 
#Mainloop:
class Stack(LinkedList):

    def __init__(self):
        super().__init__()

    #Method: this method adds a new object to the beginning of the
    #        linked list by calling self.add_first
    #Pre:    the data for a new object must be given
    #Att's:  self.first (type=node)
    #Post:   a new object node is created, self.first is set to the
    #        new node 
    def push(self, new_object):
        super().add_first(new_object)

    #Method: this method removes and returns the first element in the
    #        list by calling self.remove_first
    #Pre:    None
    #Att's:  self.size (type=integer), self.first (type=node),
    #        self.last (type=node)
    #Post:   the first object in the linked list is removed from the
    #        linked list and returned, self.first is set to
    #        self.first.next, and self.size is decremented by 1
    def pop(self):
        return (super().remove_first())

    #Method: this method just returns the first element in the list by
    #        calling self.get_first
    #Pre:    None
    #Att's:  self.first (type=node)
    #Post:   the first object in the linked list is just returned
    def peek(self):
        return (super().get_first())

    #Method: this is a method that prevents the user from calling
    #        add_last directly
    def add_last(self, new_object):
        raise(Exception("ERROR ERROR SHUTDOWN IMMINENT: this method doesn't make any sense for this class..."))

    #Method: this is a method that prevents the user from calling
    #        add_first directly
    def add_first(self, new_object):
        raise(Exception("ERROR ERROR SHUTDOWN IMMINENT: call push instead!"))

    #Method: this is a method that prevents the user from calling
    #        remove_first directly
    def remove_first(self):
        raise(Exception("ERROR ERROR SHUTDOWN IMMINENT: call pop instead!"))

    #Method: this is a method that prevents the user from calling
    #        get_first directly
    def get_first(self):
        raise(Exception("ERROR ERROR SHUTDOWN IMMINENT: call peek instead!"))


class Queue(LinkedList):

    def __init__(self):
        super().__init__()
    
    #Method: this method adds an object to the end of the linked list
    #        by calling self.add_last
    #Pre:    the data for a new object must be given
    #Att's:  self.size (type=integer), self.first (type=node)
    #Post:   a new object is created, and self.last is set to the new
    #        object 
    def enqueue(self, new_object):
        super().add_last(new_object)

    #Method: this method removes and returns the first element in the
    #        list by calling self.remove_first
    #Pre:    None
    #Att's:  self.size (type=integer), self.first (type=node),
    #        self.last (type=node)
    #Post:   the first object in the linked list is removed from the
    #        linked list and returned, self.first is set to
    #        self.first.next, and self.size is decremented by 1
    def dequeue(self):
        return (super().remove_first())

    #Method: this method just returns the first element in the list by
    #        calling self.get_first
    #Pre:    None
    #Att's:  self.first (type=node)
    #Post:   the first object in the linked list is just returned
    def peek(self):
        return (super().get_first())

    #Method: this is a method that prevents the user from calling
    #        add_last directly
    def add_last(self, new_object):
        raise(Exception("ERROR ERROR SHUTDOWN IMMINENT: call enqueue instead!"))

    #Method: this is a method that prevents the user from calling
    #        add_first directly
    def add_first(self, new_object):
        raise(Exception("ERROR ERROR SHUTDOWN IMMINENT: this method makes no sense for this class..."))

    #Method: this is a method that prevents the user from calling
    #        remove_first directly
    def remove_first(self):
        raise(Exception("ERROR ERROR SHUTDOWN IMMINENT: call dequeue instead!"))

    #Method: this is a method that prevents the user from calling
    #        get_first directly
    def get_first(self):
        raise(Exception("ERROR ERROR SHUTDOWN IMMINENT: call peek instead!"))


if __name__ == "__main__":
    # s = Stack()
    # for i in range(10):
    #     s.push(i)
    # for i in range(10):
    #     print(s.peek())
    # for i in range(10):
    #     print(s.pop())
    # for i in range(5):
    #     s.push(i)
    # print(s)
    q = Queue()
    for i in range(10):
        q.enqueue(i)
    print(q)
    for i in range(10):
        print(q.peek())
    for i in range(10):
        print(q.dequeue())
    for i in range(5):
        q.enqueue(i)
    print(q)

        
