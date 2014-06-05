import turtle
import math
import random

sinbad = turtle.Turtle()
ariel = turtle.Turtle()
pi = 3.14159265359

sinbad.left(90)
ariel.left(90)

def love_fest(angle, radius):
    angle = math.radians(angle)
    length_of_side = 2*radius // (math.sin(angle))
    length_of_side = math.ceil(length_of_side)
    angle = math.degrees(angle)
    print(length_of_side)
    print(radius)
    print(angle)
    sinbad.left(angle)
    ariel.right(angle)
    sinbad.forward(length_of_side)
    ariel.forward(length_of_side)
    (x,y) = sinbad.position()
    h = ((x+radius)-x)/2
    (w,v) = ariel.position()
    radius = math.ceil(radius)
    x = math.ceil(x)
    s = (w-(w+radius))/2
    print(x,y)
    for i in range (x, x+radius):
        y = (radius ** 2 - (i-h) ** 2)
        print(x,y)
        sinbad.goto(x,y)
    for i in range (x, x-radius, -1):
        y = (radius ** 2 - (i-h) ** 2)
        print(x,y)
        ariel.goto(x,y)





    # distance_turtles_travel = pi * radius
    # distance_turtles_travel = distance_turtles_travel / 90
    # print(distance_turtles_travel)
    # distance_turtles_travel = math.ceil(distance_turtles_travel)
    # print(distance_turtles_travel)


    # for i in range (0,91,1):
    #     sinbad.forward(distance_turtles_travel)
    #     sinbad.right(2)
    # for i in range (0,91,1):
    #     ariel.forward(distance_turtles_travel)
    #     ariel.left(2)

    # for i in range (              ):
    #     sinbad.forward(distance_turtles_travel)
    #     sinbad.right(angle_turn_turtles)
    # for i in range (              ):
    #     ariel.forward(distance_turtles_travel)
    #     ariel.left(angle_turn_turtles)
    

rand = random.randrange(20,100,1)

love_fest(35, rand)

turtle.mainloop()

# rand = random.random(20,100,1)

# love_fest(40, rand)

# turtle.mainloop()

# rand = random.random(20,100,1)

# love_fest(40, rand)

# turtle.mainloop()

# rand = random.random(20,100,1)

# love_fest(40, rand)

# turtle.mainloop()
