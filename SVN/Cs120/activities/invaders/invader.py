import random
import math
import turtle

EAST = 0
NORTH = 90
WEST = 180
SOUTH = 270
RADIUS = 50
half_w_height = turtle.window_height() / 2
half_w_width = turtle.window_width() / 2

class Invader:
    
    def __init__(self, init_x=-half_w_width, init_y=half_w_height, speed=.2):
        init_heading = EAST
        self.radius = RADIUS
        self.diameter = 2 * self.radius
        self.turtle = turtle.Turtle()
        self.turtle.penup()
        self.turtle.shape("invader.gif")
        self.turtle.goto(init_x, init_y)
        self.turtle.setheading(init_heading)
        self.forward = speed
    
    def update(self):
        half_window_height = turtle.window_height() / 2
        half_window_width = turtle.window_width() / 2
        (x,y) = self.turtle.pos()
        if x > half_window_width:
            self.turtle.right(90)
            self.turtle.forward(self.diameter)
            self.turtle.right(90)
            self.turtle.forward(self.forward)
        elif x < -half_window_width:
            self.turtle.left(90)
            self.turtle.forward(self.diameter)
            self.turtle.left(90)
            self.turtle.forward(self.forward)
        elif y < -half_window_height:
            self.turtle.goto(-half_window_width,half_window_height)
        else:
            self.turtle.forward(self.forward)


    def is_overlapping(self, other_circle):
        distance = self.turtle.distance(other_circle.turtle)
        return (self.radius + other_circle.radius) > distance
