import turtle
from wall import Wall
class Brick():

#this initializes a brick
    def __init__(self, var=None, topleft=(0,0), strength=1):
        self.turtle = turtle.Turtle()
        self.turtle.ht()
        self.turtle.penup()
        self.wall_list = []
        self.top_left = topleft
        self.strength = strength
        if self.strength==int(var.sstrength):
            self.width = var.swidth
            self.height = var.sheight
        else:
            self.width = var.wwidth
            self.height = var.wheight
        self.dead = False
        self.brick()

#brick builder, uses the bricks determined width and height to build a 6 wall brick
    def brick(self):
        (left_x, top_y) = self.top_left
        right_x = left_x + self.width
        bottom_y = top_y - self.height
        middle_x = (left_x + right_x)/2
        middle_y = top_y - (self.height/2)
        (p1,p2) = ((left_x, middle_y), (middle_x, top_y-10))
        (p3,p4) = ((right_x, middle_y), (right_x, bottom_y))
        (p5,p6) = ((middle_x, bottom_y-10), (left_x, bottom_y))
        self.turtle.begin_fill()
        self.wall_list.append(Wall(p1, p2))
        self.wall_list.append(Wall(p2, p3))
        self.wall_list.append(Wall(p3, p4))
        self.wall_list.append(Wall(p4, p5))
        self.wall_list.append(Wall(p5, p6))
        self.wall_list.append(Wall(p6, p1))
        self.turtle.end_fill()

#this runs the graphics for all the walls in the brick
    def graphics(self):
        for wall in self.wall_list:
            wall.graphics()

#this is called to kill the brick, erase walls and remove them from lists
    def die(self):
        for wall in self.wall_list:
            wall.turtle.clear()
        while len(self.wall_list) > 0:
            del(self.wall_list[0])

#used to update the bricks, health, if dead, call die
    def update(self):
        for wall in self.wall_list:
            if wall.hits_taken != 0:
                self.strength -= wall.hits_taken
                wall.hits_taken = 0
        if self.strength <= 0:
            self.die()
            self.dead = True
