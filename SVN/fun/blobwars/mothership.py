import turtle
import math
import random

import enemy1

INIT_X = 100
INIT_Y = 100
SPEED = 1
one_spawn_per_second = ((1800)/(60))
SPAWN_RATE = one_spawn_per_second * 5
HEALTH = 10
RADIUS = 10
EAST = 0
IMAGE = 'Circle'

class EnemySpawn:

    def __init__(self, x=INIT_X, y=INIT_Y, spawn_rate=SPAWN_RATE, health=HEALTH, radius=RADIUS, speed=SPEED, image=IMAGE):
        self.turtle = turtle.Turtle()
        self.turtle.shape("EnemySpawn.gif")
        self.turtle.penup()
        self.health = health
        self.radius = radius
        self.speed = speed
        self.i = 0
        self.turtle.goto(x,y)
        self.spawn_rate = spawn_rate
        self.turtle.setheading(EAST)

    def keep_on_screen(self):
        (half_window_width) = turtle.window_width() / 2
        (half_window_height) = turtle.window_height() / 2
        if ((math.fabs(self.x) > half_window_width) or (math.fabs(self.y) > half_window_height)):
            turn = 180
        else:
            turn = random.randint(-2,2)
        return turn

    def update(self):
        if self.i > self.spawn_rate:
            self.i = 0
        (self.x, self.y) = self.turtle.pos()
        self.heading = self.turtle.heading()
        turn = self.keep_on_screen()
        self.turtle.left(turn)
        self.turtle.forward(self.speed)
        self.i += 1

    def is_overlapping(self, other_circle):
        distance = self.turtle.distance(other_circle.turtle)
        return (self.radius + other_circle.radius) > distance
