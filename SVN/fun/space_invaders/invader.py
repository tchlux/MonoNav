import random
import math
import turtle

EAST = 0
NORTH = 90
WEST = 180
SOUTH = 270
RADIUS = 50
DESCENT = 10
INIT_SPEED = 4
ACCELERATION = 1
MOVING_EAST_STATE = 0
MOVING_SOUTH_STATE = 1
MOVING_WEST_STATE = 2
MOVING_NORTH_STATE = 3


class Invader:
    
    def __init__(self, init_x, init_y):
        self.speed = INIT_SPEED
        self.radius = RADIUS
        self.state = MOVING_EAST_STATE
        self.turtle = turtle.Turtle()
        self.turtle.penup()
        self.turtle.shape("invader.gif")
        self.turtle.goto(init_x, init_y)
        self.turtle.setheading(EAST)
    
    def update(self):
        half_window_width = turtle.window_width() // 2
        (x, y) = self.turtle.position()
        if self.state == MOVING_EAST_STATE and x > half_window_width:
            self.turtle.setheading(SOUTH)
            self.state = MOVING_SOUTH_STATE
            self.goal_y = y - self.radius
            self.speed += ACCELERATION
        if self.state == MOVING_SOUTH_STATE and y < self.goal_y:
            self.turtle.setheading(WEST)
            self.state = MOVING_WEST_STATE
        if self.state == MOVING_WEST_STATE and x < -half_window_width:
            self.turtle.setheading(SOUTH)
            self.state = MOVING_NORTH_STATE
            self.goal_y = y - self.radius
            self.speed += ACCELERATION
        if self.state == MOVING_NORTH_STATE and y < self.goal_y:
            self.turtle.setheading(EAST)
            self.state = MOVING_EAST_STATE
        self.turtle.forward(self.speed)

    def is_overlapping(self, other_circle):
        distance = self.turtle.distance(other_circle.turtle)
        return (self.radius + other_circle.radius) > distance
