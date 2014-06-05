import turtle
fresco = turtle.Turtle()

def star_side (length):
    fresco.forward(length)
    fresco.right(144)

length = 700

fresco.penup()
fresco.goto(-350,80)
fresco.pendown()

for i in range (5):
    star_side(length)


turtle.mainloop()
