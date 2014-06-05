import turtle
from wall import Wall
class Paddle():

#constructor
    def __init__(self, var=None):
        self.turtle = turtle.Turtle()
        self.turtle.ht()
        self.turtle.penup()
        self.wall_list = []
        self.top_left = var.ptopleft
        self.width = var.pwidth
        self.height = var.pheight
        self.speed = var.pspeed
        self.hspeed = 0
        self.vspeed = 0
        self.paddle()

#the paddle is built of walls
    def paddle(self):
        (left_x, top_y) = self.top_left
        right_x = left_x + self.width
        bottom_y = top_y - self.height
        middle_x = (left_x + right_x)/2
        middle_y = top_y + (self.height/2)
        p1 = ((left_x+5),(top_y))
        p2 = ((middle_x),(middle_y))
        p3 = ((right_x-5),(top_y))
        p4 = ((right_x+15),(bottom_y))
        p5 = ((middle_x),(middle_y-self.height))
        p6 = ((left_x-15),(bottom_y))

        self.wall_list.append(Wall(p1,p2))
        self.wall_list.append(Wall(p2,p3))
        self.wall_list.append(Wall(p3,p4))
        self.wall_list.append(Wall(p4,p5))
        self.wall_list.append(Wall(p5,p6))
        self.wall_list.append(Wall(p6,p1))

#Alternate paddle design
        # self.wall_list.append(Wall((left_x, bottom_y),(middle_x,middle_y)))
        # self.wall_list.append(Wall((middle_x, middle_y),(right_x, bottom_y)))
        # self.wall_list.append(Wall((right_x, bottom_y),(middle_x, bottom_y+5)))
        # self.wall_list.append(Wall((middle_x, bottom_y+5),(left_x, bottom_y)))

#graphics run
    def graphics(self):
        for wall in self.wall_list:
            wall.graphics()
        # self.turtle.addshape(var.pimage)
        # self.turtle.shape = var.pimage

#used for mouse movement
    def move(self, movex):
        for wall in self.wall_list:
            wall.move(right=movex)

#right arrow key
    def move_right(self, move=0):
        self.hspeed = self.speed

#left arrow key
    def move_left(self, move=0):
        self.hspeed = -self.speed

#cancelled out
    def move_up(self):
        self.vspeed = self.speed

#cancelled out
    def move_down(self):
        self.vspeed = -self.speed

#movement stopped
    def stop(self):
        self.hspeed = 0
        self.vspeed = 0

#all walls graphics are updated
    def update(self):
        for wall in self.wall_list:
            wall.move(right=self.hspeed, up=self.vspeed)
        self.graphics()
