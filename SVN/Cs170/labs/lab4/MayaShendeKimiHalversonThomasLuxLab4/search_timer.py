import list_search
from timeit import Timer
from timeit import timeit
import random
from student import Student

#This class compares the time for a linear or binary search of a
#    given term.
class SearchTimer:
    #Constructor
    #Pre:    a search term must be provided
    #Post:   multiple class attributes are defined
    def __init__(self, lst, search_term):
        self.lst = lst
        self.search_term = search_term
        self.bin_timer = 0
        self.lin_timer = 0
        self.itr = 1000
        self.bin()
        self.lin()
        # (null, self.bin_itr) = list_search.binary_search(self.lst, self.search_term)
        # (null, self.lin_itr) = list_search.linear_search(self.lst, self.search_term)

    #This method calls the list_search.binary_search with the appropriate variables
    #Pre:    The method is called
    #Post:   The list_search is run
    def bin_search(self):
        list_search.binary_search(self.lst, self.search_term)

    #This method calls the list_search.linear_search with the appropriate variables
    #Pre:    The method is called
    #Post:   The list_search is run
    def lin_search(self):
        list_search.linear_search(self.lst, self.search_term)

    #This method times the binary search
    #Pre:    The method is called.
    #Post:   The self.bin_timer attribute is given a value
    def bin(self):
        timer = Timer(self.bin_search)
        self.bin_timer = timer.timeit(self.itr)

    #This method times the linear search
    #Pre:    The method is called.
    #Post:   The self.lin_timer attribute is given a value
    def lin(self):
        timer = Timer(self.lin_search)
        self.lin_timer = timer.timeit(self.itr)

    #This method prints the two timers (binary : linear)
    #Pre:    The string method is called on the class
    #Post:   The 'string'ed version of the timer attributes are
    #        returned
    def __str__(self):
        string = ("%.4f   :   %.4f") % (self.bin_timer, self.lin_timer)
        return string


#this runs the Search timer class on numbers 0 to 99 on a list
#    containing the values 0 to 99
#lst = list(range(1000000))
print("Binary   :   Linear")
student_list = []
for i in range(10):
    name = input("student name")
    student_list.append(Student(name, 1, 2, 3))

s = Student("Maya", 1, 2, 3)
print(list_search.binary_search(student_list, s))
