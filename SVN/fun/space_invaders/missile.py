import random
import math
import turtle

EAST = 0
NORTH = 90
WEST = 180
SOUTH = 270
RADIUS = 10
SPEED = 10
DESCENT = 5

class Missile:
    
    def __init__(self, init_x, init_y):
        self.radius = RADIUS
        self.turtle = turtle.Turtle()
        self.turtle.penup()
        self.turtle.shape("missile.gif")
        self.turtle.goto(init_x, init_y)
        self.turtle.setheading(NORTH)
    
    def update(self):
        self.turtle.forward(SPEED)

    def is_overlapping(self, other_circle):
        distance = self.turtle.distance(other_circle.turtle)
        return (self.radius + other_circle.radius) > distance
