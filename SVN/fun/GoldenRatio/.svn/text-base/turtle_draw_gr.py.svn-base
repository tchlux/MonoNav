import math
import turtle

PHI = (1+5**.5)/2
INITIAL_LENGTH = 600
DEPTH = 14
PEN_COLOR = "blue"
TURN = 90
START = (-INITIAL_LENGTH/2.0,INITIAL_LENGTH/(PHI*2))

class GoldenRatio:
    def __init__(self):
        self.turtle = turtle.Turtle()
        self.turtle.speed(0)
        self.turtle.ht()
        self.turtle.pu()
        self.turtle.pencolor(PEN_COLOR)
        self.turtle.goto(START)
        self.turtle.pd()
        self.length = INITIAL_LENGTH

    def draw_rectangle(self):
        a = self.length/PHI
        b = self.length - a
        self.turtle.pd()
        for i in range(2):
            self.turtle.fd(a+b)
            self.turtle.right(TURN)
            self.turtle.fd(a)
            self.turtle.right(TURN)
        self.turtle.fd(a)
        self.turtle.right(TURN)
        self.turtle.fd(a)
        self.turtle.right(TURN*2)

    def run(self):
        for i in range(DEPTH):
            self.draw_rectangle()
            self.length = self.length/PHI


if __name__ == "__main__":
    picture = GoldenRatio()
    picture.run()
    turtle.mainloop()
