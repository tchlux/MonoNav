import turtle
import math

EAST = 0
NORTH = 90
WEST = 180
SOUTH = 270
RADIUS = 9
TURN_SPEED = 5
BLOBHERO_INIT_X = -300
BLOBHERO_INIT_Y = 200
INIT_SPEED = 1
MAX_SPEED = 3

class BlobHero:

    def __init__(self, speed=INIT_SPEED):
        self.turtle = turtle.Turtle()
        self.turtle.penup()
        self.radius = RADIUS
        self.speed = speed
        self.turn = 0
        self.turtle.shape("BlobHeroOpen0.gif")
#        self.turtle.shape("fairy.gif")
        self.turtle.goto(BLOBHERO_INIT_X, BLOBHERO_INIT_Y)
        self.turtle.setheading(EAST)
    
    def turn_left(self):
        self.turn = TURN_SPEED

    def turn_right(self):
        self.turn = -TURN_SPEED

    def stop_turn(self):
        self.turn = 0

    def move_forward(self):
        if self.speed < MAX_SPEED:
            self.turtle.shapesize(2,2)
            self.speed += .5

    def move_backward(self):
        if self.speed >= .5:
            self.speed -= .5

    def find_closest_to_angle(self, heading, pic_angles):
        whole = heading // pic_angles
        extra = heading % pic_angles
        if (extra > (pic_angles//2)) or (extra == (pic_angles//2)):
            whole = (whole+1)%(360/pic_angles)
        return whole*pic_angles

    def update(self):
        self.turtle.left(self.turn)
        self.turtle.fd(self.speed)
        heading = self.turtle.heading()
        angle = str(int(self.find_closest_to_angle(heading, 15)))
        shape = "BlobHeroOpen"+angle+".gif"
        self.turtle.shape(shape)


    def is_overlapping(self, other_circle):
        distance = self.turtle.distance(other_circle.turtle)
        return (self.radius + other_circle.radius) > distance
