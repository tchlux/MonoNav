from stack_python_list import ListStack as Stack
from queue_linked_list import LinkedQueue as Queue

class BinaryTree:

    class _Node:
        def __init__(self):
            self.data = None
            self.left = None
            self.right = None

    def __init__(self):
        self.size = 0
        self.root = None

    #Method: this method inserts a new object in the tree based on if
    #        it is greater than or less than its parents.
    #Pre:    new_object is the data of the new_tree_node that is to be
    #        added to the tree
    #Att's:  self.root (type=Node)
    #Post:   the new object is made into a node for the tree, and the
    #        new node is added to the tree; added to right if it is
    #        greater than its parent and added to the left if it is
    #        less than its parent.
    def insert(self, new_object):
        new_tree_node = self._Node()
        new_tree_node.data = new_object
        if self.root == None:
            parent = self._Node()
            self.root = new_tree_node
        else:
            curr = self.root
            #special case: value == data; handled on left
            while curr != None:
                parent = curr
                if new_tree_node.data > curr.data:
                    curr = curr.right
                else:
                    curr = curr.left
            if new_tree_node.data > parent.data:
                parent.right = new_tree_node
            else:
                parent.left = new_tree_node

    #Method:This method calls self._search with the first node being
    #       self.root
    #Pre:   data is given as an Integer
    #Att's: self.root (type=_Node)
    #Post:  Returns Boolean for if data exists in the binary tree
    def search(self, data):
        return self._search(data, self.root)

    #Method:This method will return a Boolean for if a value exists in
    #       a binary tree
    #Pre:   data is given as an Integer, node as a _Node class
    #Att's: None required
    #Post:  True is returned if the value can be found in the binary
    #       tree, False for if it is not in the tree
    def _search(self, data, node):
        if node == None:
            return False
        if node.data < data:
            return self._search(data, node.right)
        if node.data > data:
            return self._search(data, node.left)
        if node.data == data:
            return True

    def print_depth_first(self):
        s = Stack()
        s.push(self.root)
        while not s.is_empty():
            curr = s.pop()
            print(curr.data)

            if curr.right != None:
                s.push(curr.right)


            if curr.left != None:
                s.push(curr.left)

    #Method:This method prints the binary tree by layers
    #Pre:   Method is called
    #Att's: self.root (type=_Node)
    #Post:  The binary tree is printed breadth first
    def print_breadth_first(self):
        q = Queue()
        q.enqueue(self.root)
        while not q.is_empty():
            node = (q.dequeue())
            print(node.data)
            if node.left != None:
                q.enqueue(node.left)
            if node.right != None:
                q.enqueue(node.right)

    #Method:This method prints subtrees first favoring the left
    #Pre:   A root is given
    #Att's: self.print_pre_order (type=Method)
    #Post:  If it is at the bottom of the tree it prints the data
    def print_pre_order(self, root):
        if root.left != None:
            self.print_pre_order(root.left)
        if root.right != None:
            self.print_pre_order(root.right)
        print(root.data)

    #Method:This method prints the binary tree depth first favoring
    #       left
    #Pre:   A root node is given to a binary tree
    #Att's: self.print_in_order (type=Method)
    #Post:  It prints the value and continues until it reaches the
    #       bottom 
    def print_in_order(self, root):
        print(root.data)
        if root.left != None:
            self.print_in_order(root.left)
        if root.right != None:
            self.print_in_order(root.right)

    #Method:This method prints subtrees first favoring the right
    #Pre:   A root node is given to a binary tree
    #Att's: self.print_pre_order (type=Method)            
    #Post:  The binary tree is printed from the bottom up favoring right
    def print_post_order(self, root):
        if root.right != None:
            self.print_pre_order(root.right)
        if root.left != None:
            self.print_pre_order(root.left)
        print(root.data)

    
