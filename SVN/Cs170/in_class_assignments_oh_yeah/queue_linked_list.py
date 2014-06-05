from queue import Queue
from linked_list import LinkedList

class LinkedQueue(Queue):

    def __init__(self):
        super().__init__()
        self.internal = LinkedList()

    #push - Adds the new_object to the back of the queue
    #Pre:   new_object can have any type representable within python.
    #       The internal data structure is able to operate as a queue
    #Post:  Puts new_object at the back of the internal data structure
    def enqueue(self, new_object):
        self.internal.add_last(new_object)

    #pop  - Removes the front element of the queue, and returns it
    #Pre:   The internal data structure is able to operate as a queue
    #Post:  Removes the front element of the internal data structure,
    #       and returns it.  Returns None if there is nothing in the
    #       queue. 
    def dequeue(self):
        return self.internal.remove_first()

    #peek - Returns a copy of the data at the front of the queue
    #Pre:   The internal data structure is able to operate as a queue
    #Post:  Returns a copy of the data stored as the front of the
    #       internal data structure.
    def peek(self):
        return self.internal.get_first()

    #is_empty - Does the queue contain anything?
    #Pre:       The internal data structure is able to operate as a
    #           queue.
    #Post:      Returns False if there are items within the queue,
    #           True otherwise.
    def is_empty(self):
        return self.internal.size <= 0
