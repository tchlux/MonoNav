import turtle

class Shield:

    def __init__(self, radius, strength, image, x, y, powerout_timer, tipe='stationary'):
        self.turtle = turtle.Turtle()
        self.type = tipe
        self.radius = radius
        self.strength = strength
        self.health = strength
        self.damage = strength
        self.powerout_timer = 0
        self.powerout_reset_timer = powerout_timer
        self.turtle.shape(image)
        self.turtle.penup()
        self.turtle.goto(x,y)

    def update(self):
        self.health = self.strength
        self.damage = self.strength
        if self.strength > 0:
            self.powerout_timer += 1
        if (self.strength <= 0) or (self.powerout_timer == self.powerout_reset_timer):
            self.turtle.hideturtle()

    def is_overlapping(self, other_circle):
        distance = self.turtle.distance(other_circle.turtle)
        return (self.radius + other_circle.radius) > distance

class PortableShield:

    def __init__(self, radius, strength, image, x, y, tipe='portable'):
        self.turtle = turtle.Turtle()
        self.type = tipe
        self.radius = radius
        self.strength = strength
        self.health = strength
        self.damage = strength
        self.turtle.shape(image)
        self.turtle.penup()
        self.turtle.goto(x,y)

    def update(self):
        self.health = self.strength
        self.damage = self.strength
        if self.strength <= 0:
            self.turtle.hideturtle()

    def is_overlapping(self, other_circle):
        distance = self.turtle.distance(other_circle.turtle)
        return (self.radius + other_circle.radius) > distance
