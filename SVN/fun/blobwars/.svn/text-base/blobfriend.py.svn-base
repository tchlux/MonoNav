import turtle
import math

EAST = 0
RADIUS = 9
X = 0
Y = 0
HEALTH = 2
RADIUS = 10
SPEED = 0
SHOT = "bullet"
FIRE_RATE = 20

class BlobFriend:

    def __init__(self, health=HEALTH, radius=RADIUS, speed=SPEED, x=X, y=Y, shot=SHOT, fire_rate=FIRE_RATE):
        self.health = health
        self.radius = radius
        self.speed = speed
        self.timer = 0
        self.last_heading = 0
        self.ammo_type = shot
        self.fire_rate = fire_rate
        self.turtle = turtle.Turtle()
        self.turtle.penup()
        self.turtle.shape("BlobFriend0.gif")
        self.turtle.goto(x,y)
        self.turtle.setheading(EAST)

    def find_closest_to_angle(self, heading, pic_angles):
        whole = heading // pic_angles
        extra = heading % pic_angles
        if (extra > (pic_angles//2)) or (extra == (pic_angles//2)):
            whole = (whole+1)%(360/pic_angles)
        return whole*pic_angles

    def update(self):
        self.turtle.fd(self.speed)
        heading = self.turtle.heading()
        angle = str(int(self.find_closest_to_angle(heading, 45)))
        shape = "BlobFriend"+angle+".gif"
        self.turtle.shape(shape)

    def is_overlapping(self, other_circle):
        distance = self.turtle.distance(other_circle.turtle)
        return (self.radius + other_circle.radius) > distance
