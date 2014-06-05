import turtle
import random

class BlobBomber:

    def __init__(self, health, radius, speed, x, y, fire_rate):
        self.health = health
        self.radius = radius
        self.speed = speed
        self.timer = 0
        self.last_heading = 0
        self.fire_rate = fire_rate
        self.ammo_type = "missile"
        self.turtle = turtle.Turtle()
        self.turtle.penup()
        self.turtle.shape("BlobBomber0.gif")
        self.turtle.goto(x,y)
        self.turtle.setheading(0)

    def is_overlapping(self, other_circle):
        distance = self.turtle.distance(other_circle.turtle)
        return (self.radius + other_circle.radius) > distance

    def find_closest_to_angle(self, heading, pic_angles):
        whole = heading // pic_angles
        extra = heading % pic_angles
        if (extra > (pic_angles//2)) or (extra == (pic_angles//2)):
            whole = (whole+1)%(360/pic_angles)
        return whole*pic_angles

    def update(self):
        self.turtle.fd(self.speed)
        # heading = self.turtle.heading()
        # angle = str(int(self.find_closest_to_angle(heading, 30)))
        # shape = "BlobBomber"+angle+".gif"
        # self.turtle.shape(shape)
