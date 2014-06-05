import turtle

SPEED = 0
RADIUS = 0
IMAGE = 'Circle'
DAMAGE = 1
SLOW = None

class Bullet:

    def __init__(self, speed=SPEED, radius=RADIUS, image=IMAGE, damage=DAMAGE, x=0, y=0, heading=0, slow_effect=SLOW):
        self.turtle = turtle.Turtle()
        self.speed = speed
        self.radius = radius
        self.damage = damage
        self.turtle.shape(image)
        self.turtle.penup()
        self.turtle.goto(x,y)
        self.turtle.setheading(heading)
        self.slow = slow_effect

    def update(self):
        self.turtle.forward(self.speed)
