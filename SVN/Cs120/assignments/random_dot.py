import random
import turtle

turt = turtle.Turtle()

def make_dat(turt):

    height = turtle.window_height()
    width = turtle.window_width()
    half_height = height // 2
    half_width = width // 2
    rando_y = (int(random.random() * height - half_height))
    rando_x = (int(random.random() * width - half_width))
    turt.penup()
    turt.goto(rando_x,rando_y)
    turt.pendown()
    diameter = int(random.random()*10)
    turt.dot(diameter, "#ff1493")

for i in range(10):
    make_dat(turt)

turtle.mainloop()
print('all on the floor')
print(' gimme some more')
print("'till you get sore")
print(' ohh ahh ohh ouah')
