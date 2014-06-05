import random
import math
import turtle

EAST = 0
NORTH = 90
WEST = 180
SOUTH = 270
RADIUS = 25
SPEED = 10
DESCENT = 5

class Defender:
    
    def __init__(self, init_x, init_y):
        init_heading = EAST
        self.radius = RADIUS
        self.turtle = turtle.Turtle()
        self.turtle.penup()
        self.turtle.shape("defender.gif")
        self.turtle.goto(init_x, init_y)
        self.turtle.setheading(init_heading)
    
    def move_left(self):
        self.turtle.setheading(WEST)
        self.turtle.forward(SPEED)

    def move_right(self):
        self.turtle.setheading(EAST)
        self.turtle.forward(SPEED)

    def is_overlapping(self, other_circle):
        distance = self.turtle.distance(other_circle.turtle)
        return (self.radius + other_circle.radius) > distance
