import random
import turtle

akon = turtle.Turtle()
last_x_position = 0
last_y_position = 0

def make_dat(akon):

    height = turtle.window_height()
    width = turtle.window_width()
    half_height = height // 2
    half_width = width // 2
    rando_y = (int(random.random() * height - half_height))
    rando_x = (int(random.random() * width - half_width))
    akon.goto(rando_x,rando_y)
    diameter = int(random.random()*10)
    akon.dot(diameter, "#ff1493")

def write_distance(akon):
    x,y = akon.position()
    x = ((last_x_position) - x)
    distance = (((x)**(2)) + ((y)**(2))) ** (1/2)
    akon.write(int(distance))


for i in range (10):
    make_dat(akon)
    write_distance(akon)
turtle.mainloop()
