import turtle
import random

BLACKHOLE_IMAGE = "Blackhole1.gif"
NUMBER_OF_FRAMES = 2

class Blackhole:

    def __init__(self, x, y, radius, damage, power_out_timer, number_of_frames=NUMBER_OF_FRAMES, image=BLACKHOLE_IMAGE):
        self.turtle = turtle.Turtle()
        self.turtle.penup()
        self.turtle.shape(image)
        self.turtle.goto(x,y)
        self.radius = radius
        self.damage = damage
        self.type = "blackhole"
        self.image_number = 1
        self.number_of_frames = number_of_frames
        self.power_out_timer = power_out_timer
        self.out_timer = 0
        self.frame_rate = 2
        self.frame_rate_counter = 0
        self.mover = 1

    def update(self):
        self.out_timer += 1
        if self.frame_rate_counter == self.frame_rate:
            self.frame_rate_counter = 0
            self.image_number += self.mover
            if self.image_number == self.number_of_frames:
                self.mover = -1
            elif self.image_number == 1:
                self.mover = 1
        else:
            self.frame_rate_counter += 1
        string = "Blackhole"+str(self.image_number)+".gif"
        self.turtle.shape(string)
        if self.out_timer == self.power_out_timer:
            self.turtle.hideturtle()
