import turtle
IMAGE = "Missile0.gif"

class Missile:

    def __init__(self, speed, radius, damage, x, y, heading, image=IMAGE):
        self.turtle = turtle.Turtle()
        self.speed = speed
        self.radius = radius
        self.damage = damage
        self.last_heading = 0
        self.slow = None
        self.turtle.shape(image)
        self.turtle.penup()
        self.turtle.goto(x,y)
        self.turtle.setheading(heading)

    def find_closest_to_angle(self, heading, pic_angles):
        whole = heading // pic_angles
        extra = heading % pic_angles
        if (extra > (pic_angles//2)) or (extra == (pic_angles//2)):
            whole = (whole+1)%(360/pic_angles)
        return whole*pic_angles

    def update(self):
        self.turtle.forward(self.speed)
        self.last_heading = self.turtle.heading()
        heading = self.turtle.heading()
        angle = str(int(self.find_closest_to_angle(heading, 22.5)))
        shape = "Missile"+angle+".gif"
        self.turtle.shape(shape)
