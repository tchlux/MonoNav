import random
import math
import turtle

class Wolf:
    
    def __init__(self, init_radius=1):
        half_width = turtle.window_width() // 2
        half_height = turtle.window_height() // 2
        init_x = random.randint(-half_width, half_width)
        init_y = random.randint(-half_height, half_height)
        self.radius = 25
        self.turtle = turtle.Turtle()
        self.turtle.penup()
        self.turtle.shape("wolf.gif")
        self.turtle.goto(init_x, init_y)

    def is_overlapping(self, other_circle):
        distance = self.turtle.distance(other_circle.turtle)
        return (self.radius + other_circle.radius) > distance

    def wander(self):
        heading = self.turtle.gh()
        random_degree = random.randint(heading-20, heading+20)
        heading += random_degree
        self.turtle.setheading(heading)
