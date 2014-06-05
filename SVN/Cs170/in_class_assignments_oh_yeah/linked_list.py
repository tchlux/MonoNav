class LinkedList:

    class _Node:
        def __init__(self):
            self.object = None
            self.next = None

    def __init__(self):
        self.size = 0
        self.first = None
        self.last = None

    def add_last(self, new_object):
        new_node = self._Node()
        new_node.object = new_object
        new_node.next = None
        if self.size == 0:
            self.first = new_node
        else:
            self.last.next = new_node
        self.last = new_node
        self.size += 1

    def add_first(self, new_object):
        new_node = self._Node()
        new_node.object = new_object
        new_node.next = self.first
        if self.size == 0:
            self.last = new_node
        self.first = new_node
        self.size += 1

    def get_first(self):
        if self.size == 0:
            raise IndexError("Can not get from an empty list.")
        return self.first.object

    def remove_first(self):
        if self.size == 0:
            raise IndexError("Can not remove from an empty list.")
        removed_object = self.first.object
        self.first = self.first.next
        if self.size == 1:
            self.last = None
        self.size -= 1
        return removed_object

    def __str__(self):
        string = "["
        current_node = self.first
        while current_node is not None and current_node.next is not None:
            string += str(current_node.object) + ", "
            current_node = current_node.next
        if current_node is not None:
            string += str(current_node.object)
        string += "]"
        return string

