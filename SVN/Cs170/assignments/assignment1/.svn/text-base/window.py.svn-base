from variables import Variables
from wall import Wall
import turtle
v = Variables()

#this is what runs the window
class Window():

#constructor
#pre: called
#post: the wall's for the bounding box are built
    def __init__(self, var=None):
        self.turtle = turtle.Turtle()
        self.turtle.ht()
        self.turtle.penup()
        (self.w, self.h) = turtle.screensize()
        self.wall_list = []
        x1 = var.worldw/1.7
        y1 = var.worldh/1.7
        self.wall_list.append(Wall((-x1,-y1),(-x1,0)))
        self.wall_list.append(Wall((-x1, 0), (-x1, y1)))

        self.wall_list.append(Wall((-x1,y1),(0,y1+60)))
        self.wall_list.append(Wall((0,y1+60),(x1,y1)))

        self.wall_list.append(Wall((x1,y1),(x1,0)))
        self.wall_list.append(Wall((x1,y1),(x1,-y1)))

        self.wall_list.append(Wall((-x1,-y1),(0,-y1-60)))
        self.wall_list.append(Wall((0,-y1-60),(x1,-y1)))

#        self.wall_list.append(Wall((-20,-200),(20,-195)))


#########################################
#the next methods are not used
    def change_w(self, number):
        self.turtle.screensize(self.w-number, self.h)

    def change_h(self, number):
        self.turtle.screensize(self.w, self.h-number)

    def set_bg(self, background):
        self.screensize(bg=background)
