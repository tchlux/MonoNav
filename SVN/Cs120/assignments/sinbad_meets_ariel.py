import turtle
import math

sinbad = turtle.Turtle()
ariel = turtle.Turtle()

sinbad.left(90)
ariel.left(90)

def love_fest(length_of_side, radius):
    angle = math.asin(math.radians(( 2*radius ) / length_of_side))
    sinbad.left(angle)
    ariel.right(angle)
    sinbad.forward(length_of_side)
    ariel.forward(length_of_side)

love_fest(200, 1000)

turtle.mainloop()
