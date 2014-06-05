from stack import Stack

class ListStack(Stack):
    def __init__(self):
        super().__init__()
        self.internal = []
        
    #push - Adds the new_object to the top of the stack
    #Pre:   new_object can have any type representable within python.
    #       The internal data structure is able to operate as a stack
    #Post:  Puts new_object on the top of the internal data structure
    def push(self, new_object):
        self.internal.append(new_object)

    #pop  - Removes the top element of the stack, and returns it
    #Pre:   The internal data structure is able to operate as a stack
    #Post:  Removes the top element of the internal data structure,
    #       and returns it.  Returns None if there is nothing in the
    #       stack. 
    def pop(self):
        ret_val = None

        if not self.is_empty():
            ret_val = self.internal.pop()

        return ret_val

    #peek - Returns a copy of the data on the top of the stack
    #Pre:   The internal data structure is able to operate as a stack
    #Post:  Returns a copy of the data stored as the top of the
    #       internal data structure.  Returns None if there is nothing
    #       in the stack.
    def peek(self):
        ret_val = None

        if not self.is_empty():
            ret_val = self.internal[-1]

        return ret_val
        
    
    #is_empty - Does the stack contain anything?
    #Pre:       The internal data structure is able to operate as a
    #           stack.
    #Post:      Returns False if there are items within the stack,
    #           True otherwise.
    def is_empty(self):
        return len(self.internal) <= 0
