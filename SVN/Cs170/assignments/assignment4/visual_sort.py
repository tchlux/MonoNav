import turtle
import random
import time

#This class creates a window full of random dots and sorts it on key presses
class VisualSort:
    #This initializes all of the variables and turtle attributes needed
    def __init__(self):
        self.list_length = 100
        self.lst = [i for i in range(-self.list_length//2,self.list_length//2+1)]
        self.randomize_lists()
        self.fast = False
        self.frame_rate = 2
        self.turtle = turtle.Turtle()
        self.turtle.pu()
        self.turtle.ht()
        self.turtle.speed(0)
        self.xratio = lambda x : (turtle.window_width()/self.list_length) * x
        self.yratio = lambda y : (turtle.window_height()/self.list_length) * y
        self.sortlst = Sort(self.lst)
        turtle.onkeypress(self.randomize_lists, "r")
        turtle.onkeypress(self.bubble_sort, "b")
        turtle.onkeypress(self.insertion_sort, "i")
        turtle.onkeypress(self.selection_sort, "s")
        turtle.onkeypress(self.fast_switch, "f")
        turtle.listen()
        turtle.tracer(0)
        pen = turtle.Turtle()
        pen.ht()
        pen.pu()
        pen.goto(-100,100)
        pen.write("S: Selection sort\nI: Insertion sort\nB: Bubble sort\nR: Randomize\nF: Switch speed modes")

    #This will turn on and off 'fast mode' so you can see the process at different speeds
    #Pre:    The method is called by a button press
    #Post:   The speed will be flipped to the opposite of its current value
    def fast_switch(self):
        self.fast = not self.fast

    #This method will re-randomize the list so the dots are scattered across the screen
    #Pre:    The "R" key is pressed
    #Post:   The list is randomized and the screen is scrambled again
    def randomize_lists(self):
        print("lists randomized")
        random.shuffle(self.lst)

    #This method will call bubble sort on the self.lst attribute
    #Pre:    The "B" key is pressed
    #Post:   The list is sorted step by step using the bubble method
    def bubble_sort(self):
        print("bubble sorting")
        self.sortlst.bubble_sort(self)

    #This method will call insertion sort on the self.lst attribute
    #Pre:    The "I" key is pressed
    #Post:   The list is sorted step by step using the insertion method
    def insertion_sort(self):
        print("insertion sorting")
        self.sortlst.insertion_sort(self)

    #This method will call selection sort on the self.lst attribute
    #Pre:    The "S" key is pressed
    #Post:   The list is sorted step by step using the selection method
    def selection_sort(self):
        print("selection sorting")
        self.sortlst.selection_sort(self)

    #This method will be called to clear and re-draw all of the dots on the screen
    #Pre:    This method is called by some other method or function
    #Post:   The screen is cleared and drawn again
    def draw_window(self):
        self.turtle.clear()
        for i in range(-self.list_length//2,self.list_length//2+1):
            self.turtle.goto(self.xratio(i), self.yratio(self.lst[i+self.list_length//2]))
            self.turtle.dot()
        turtle.update()
        if not self.fast:
            time.sleep(.1)

    #This method will keep the screen up to date based on a stored attribute
    #Pre:    This method will be called by the turtle.ontimer to keep things going
    #Post:   The program sits idle waiting for key presses
    def run(self):
        self.draw_window()
        turtle.ontimer(self.run, self.frame_rate)

#This is a class that sorts a given list
class Sort():
    #Pre:    a list is given
    #Post:   lst is saved to self
    def __init__(self, lst):
        self.lst = lst

    #This method sorts the self.lst using bubble method
    #Pre:    None
    #Post:   the self.lst is sorted
    def bubble_sort(self, parent):
        for end in range(len(self.lst)-1, 0, -1):
            parent.draw_window()
            for index in range(end):
                if self.lst[index] > self.lst[index+1]:
                    self.lst[index], self.lst[index+1] = self.lst[index+1], self.lst[index]


    #This method sorts the self.lst using selection method
    #Pre:    None
    #Post:   the self.lst is sorted
    def selection_sort(self, parent):
        for index in range(0, len(self.lst)):
            index_of_min = self._find_index_of_min(index, len(self.lst))
            self.lst[index], self.lst[index_of_min] = self.lst[index_of_min], self.lst[index]
            parent.draw_window()

    #This method finds the index of the min value
    #Pre:    The beginning and end indexes are given
    #Post:   The index of the min is returned
    def _find_index_of_min(self, begin, end):
        index_of_min = begin
        for index in range(begin + 1, end):
            if self.lst[index] < self.lst[index_of_min]:
                index_of_min = index
        return index_of_min

    #This function sorts a list using insertion
    #Pre:    A list is given
    #Post:   The list is returned sorted from smallest to largest
    def insertion_sort(self, parent):
        for start in range(1,len(self.lst)):
            self.insert_and_adjust(start)
            parent.draw_window()

    #This function puts a value at a start index into it's proper place
    # on the sorted side of the list
    #Pre:    A list is given, and a start index
    #Post:   The list is edited, with the given lst[start] being put
    #        on the sorted side of the list (assumption=sorted is left)
    def insert_and_adjust(self, start):
        new_index = self._find_where_to_put_min(start)
        minimum = self.lst[start]
        for i in range(start, new_index, -1):
            self.lst[i] = self.lst[i-1]
        self.lst[new_index] = minimum

    #This function finds the index to the left of the lowest number
    #in the sorted side of the list
    #Pre:    a list is given, and a start index is given
    #Post:   The index that is one location left of the first
    #        list[index] greater than list[start]
    def _find_where_to_put_min(self, start):
        min_index = start - 1
        if self.lst[min_index] > self.lst[start]:
            while (self.lst[min_index] > self.lst[start]) and (min_index >= 0):
                min_index -= 1
            return min_index + 1
        else:
            return start

final = VisualSort()
final.run()
turtle.mainloop()
