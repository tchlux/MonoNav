import turtle
import math
import random

import enemy1

INIT_X = 0
INIT_Y = 0
SPEED = 1
one_spawn_per_second = ((1800)/(60))
SPAWN_RATE = one_spawn_per_second * 5
HEALTH = 10
RADIUS = 8
EAST = 0
IMAGE = 'EnemySpawn.gif'
CHILD = "enemy1"

class EnemySpawn:

    def __init__(self, health=HEALTH, radius=RADIUS, speed=SPEED, image=IMAGE, x=INIT_X, y=INIT_Y, spawn_rate=SPAWN_RATE, child=CHILD):
        self.turtle = turtle.Turtle()
        self.turtle.shape(image)
        self.turtle.penup()
        self.health = health
        self.radius = radius
        self.speed = speed
        self.child = child
        self.i = 0
        self.turtle.goto(x,y)
        self.spawn_rate = spawn_rate
        self.turtle.setheading(random.randint(0,359))

    def get_closest_turn(self, turn):
        if turn > 180:
            turn = turn - 360
        if turn < -180:
            turn = turn + 360
        return turn

    def keep_on_screen(self):
        (half_window_width) = turtle.window_width() / 2
        (half_window_height) = turtle.window_height() / 2
        if (math.fabs(self.x) > half_window_width):
            new_heading = 180 - self.turtle.heading()
            turn = (new_heading - self.turtle.heading())
            if turn < 10:
                turn = (self.turtle.towards(0,0) - self.turtle.heading())
        elif (math.fabs(self.y) > half_window_height):
            new_heading = 360 - self.turtle.heading()
            turn = (new_heading - self.turtle.heading())
            if turn < 10:
                turn = (self.turtle.towards(0,0) - self.turtle.heading())
        else:
            turn = random.randint(-2,2)
        return turn

    def update(self, enemies_list, spawners_list, hero, blobs, bullets):
        if self.i > self.spawn_rate:
            self.i = 0
        (self.x, self.y) = self.turtle.pos()
        self.last_heading = self.turtle.heading()
        self.heading = self.turtle.heading()
        turn = self.get_closest_turn(self.keep_on_screen())
        self.turtle.left(turn)
        self.turtle.forward(self.speed)
        self.i += 1

    def is_overlapping(self, other_circle):
        distance = self.turtle.distance(other_circle.turtle)
        return (self.radius + other_circle.radius) > distance
