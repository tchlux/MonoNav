import turtle
import random
from timeit import Timer
from timeit import timeit
lst = [33, 24, -17, 35, 46, 28, 49, 34, 30, 21, -16, 39, -10, -5, -1, -13, 16, -20, -7, -24, 48, 26, 8, 48, -14, -9, 31, 44, -21, 41, 40, 49, -10, 8, 8, -7, 18, 55, -15, 55, -6, -17, -5, 8, 43, -16, 47, -6, 57, 22, 32, 3, -24, 20, -28, 33, -17, -17, 11, -1, -6, 49, 33, 58, 6, -7, 15, -18, 10, 22, 6, 45, 41, -20, 41, 9, 8, 31, 45, -16, -4, 1, -2, 30, 41, 43, 6, -4, 53, 36, 45, -27, 30, 14, -15, 33, -7, 1, -26, 42]

#This is a class that sorts a given list
class Sort():
    #Pre:    a list is given
    #Post:   lst is saved to self
    def __init__(self, lst):
        self.lst = lst

    #This method finds the index of the min value
    #Pre:    The beginning and end indexes are given
    #Post:   The index of the min is returned
    def _find_index_of_min(self, begin, end):
        index_of_min = begin
        for index in range(begin + 1, end):
            if self.lst[index] < self.lst[index_of_min]:
                index_of_min = index
        return index_of_min

    #This method sorts the self.lst using selection method
    #Pre:    None
    #Post:   the self.lst is sorted
    def selection_sort(self):
        for index in range(0, len(self.lst)):
            index_of_min = self._find_index_of_min(index, len(self.lst))
        self.lst[index], self.lst[index_of_min] = self.lst[index_of_min], self.lst[index]


    #This function sorts a list using insertion
    #Pre:    A list is given
    #Post:   The list is returned sorted from smallest to largest
    def insertion_sort(self):
        for start in range(1,len(self.lst)):
            self.insert_and_adjust(start)
        return self.lst


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


    #This method times the selection sort for this class
    #Pre:    This class has a self.lst
    #Post:   The time it took to sort is returned
    def time_the_selection(self):
        timer1 = Timer(self.selection_sort)
        a = timer1.timeit(99)
        return a

    def time_the_insertion(self):
        timer2 = Timer(self.insertion_sort)
        b = timer2.timeit(99)
        return b

#This function prints the time it takes to sort different length
#  lists and then plots the data on turtle
#Pre:    None
#Post:   The times taken to sort are plotted
def print_all_timers():
    data = []
    for i in range(100,1001,50):
        print("List length", i)
        sel_trial = []
        ins_trial = []
        for trial in range(1):
            lst = [random.randint(-50,50) for q in range(i)]
            lst2 = [random.randint(-50,50) for q in range(i)]
            c = Sort(lst)
            b = Sort(lst2)
            sel = c.time_the_selection()
            ins = b.time_the_insertion()
            print("sel: ",sel,"  ins: ",ins)
            sel_trial.append(sel)
            ins_trial.append(ins)
        av_sel = sum(sel_trial)/len(sel_trial)
        av_ins = sum(ins_trial)/len(ins_trial)
        data.append([i, av_sel, av_ins])
    plot_data(data)

#This function plots given data in turtle
#Pre:    The data is given, [x, seltime, instime] format
#Post:   The data is plotted on turtle
def plot_data(data):
    turt = turtle.Turtle()
    turt.ht()
    turt.speed(0)
    turt.penup()
    turtle.setworldcoordinates(0,0,640,480)
    turt.goto(0,0)
    last_ins = (0,0)
    if data[-1][1] > data[-1][2]:
        max_value = data[-1][1]
    else:
        max_value = data[-1][2]
    for item in data:
        x = (640*item[0])/1100
        ysel = (480*item[1])/max_value
        yins = (480*item[2])/max_value
        turt.pd()
        turt.goto(x, ysel)
        turt.dot(10, "red")
        turt.pu()
        turt.goto(last_ins)
        turt.pd()
        turt.goto(x,yins)
        turt.dot(10, "blue")
        turt.pu()
        turt.goto(x,ysel)
        last_ins = (x, yins)
    turt.goto(20, 300)
    turt.write("Blue: Insertion   Red: Selection")
    turtle.mainloop()

print_all_timers()

# :) turtle running like a boss
def drunk_turtle():
    turt = turtle.Turtle()
    while 1>0:
        turt.forward(2)
        (x,y) = turt.pos()
        dist = ((x**2 + y**2)**(1/2))
        if dist >= turtle.window_width()/2:
            turt.left(turt.heading() - turt.towards(0,0))
        else:
            turt.left(random.randint(-4,2))
    turtle.mainloop()

a = input("")
drunk_turtle()
