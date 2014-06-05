import turtle
import math
import random
loofa = turtle.Turtle()

def draw_circle_at(turtle):
    r = 300
    turtle.penup()
    turtle.goto(r,0)
    turtle.pendown()
    for i in range ((r),(-r-1),-2):
        x = i
        y = (((r ** 2) - (x) ** 2) ** (1/2))
        turtle.goto(x,y)
    for i in range ((-r),(r+1),2):
        x = i
        y = -((((r ** 2) - (x) ** 2) ** (1/2)))
        turtle.goto(x,y)

def make_dat(loofa):
    height = turtle.window_height()
    width = turtle.window_width()
    half_height = height // 2
    half_width = width // 2
    rando_y = (int(random.random() * height - half_height))
    rando_x = (int(random.random() * width - half_width))
    loofa.penup()
    loofa.goto(rando_x,rando_y)
    loofa.pendown()
    diameter = int(random.random()*10)
    loofa.dot(diameter, "#ff1493")
    x,y = loofa.position()
    distance = (((x)**(2)) + ((y)**(2))) ** (1/2)
    if distance > 300:
        loofa.write("outside")
    else:
        loofa.write("inside")

draw_circle_at(loofa)
for i in range (10):
    make_dat(loofa)

turtle.mainloop()

