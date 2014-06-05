import turtle
import math
import random

class TestTurtle:

    def __init__(self):
        self.init_turtle()

    def init_turtle(self):
        self.turtle = turtle.Turtle()
        self.ghost = turtle.Turtle()
        self.turtle.penup()
        self.ghost.penup()
        turtle.addshape('BlobHeroOpen0.gif')
        self.turtle.shape('BlobHeroOpen0.gif')
        # self.turtle.shape('square')
        # self.ghost.shape('square')
        try:
            bg = turtle.textinput("Hey you!", "what color should the bg be?")
            turtle.bgcolor(bg)
        except:
            print('invalid input for color:', bg)
            turtle.bgcolor('white')
        turtle.tracer(0)
        turtle.listen()
        self.x_speed = 0
        self.y_speed = 0
        turtle.onkeypress(self.handle_left_arrow, "Left")
        turtle.onkeyrelease(self.handle_left_release, "Left")
        turtle.onkeypress(self.handle_right_arrow, "Right")
        turtle.onkeyrelease(self.handle_right_release, "Right")
        turtle.onkeypress(self.handle_up_arrow, "Up")
        turtle.onkeyrelease(self.handle_up_release, "Up")
        turtle.onkeypress(self.handle_down_arrow, "Down")
        turtle.onkeyrelease(self.handle_down_release, "Down")
        turtle.onscreenclick(self.handle_click)

    def switch_bool(self, bol):
        if bol == True:
            bol = False
        else:
            bol = True
        return bol

    def handle_click(self, x, y):
        self.turtle.setheading(self.turtle.towards(x,y))
        self.ghost.setheading(self.ghost.towards(x,y))

    def handle_left_arrow(self):
        self.x_speed = -3

    def handle_left_release(self):
        self.x_speed = 0

    def handle_right_arrow(self):
        self.x_speed = 3

    def handle_right_release(self):
        self.x_speed = 0

    def handle_up_arrow(self):
        self.y_speed = 3

    def handle_up_release(self):
        self.y_speed = 0

    def handle_down_arrow(self):
        self.y_speed = -3

    def handle_down_release(self):
        self.y_speed = 0

    def run(self):
        (x,y) = self.turtle.pos()
        self.turtle.goto(x+self.x_speed, y+self.y_speed)
        turtle.update()
        turtle.ontimer(self.run, 30)

test = TestTurtle()
test.run()
turtle.mainloop()
