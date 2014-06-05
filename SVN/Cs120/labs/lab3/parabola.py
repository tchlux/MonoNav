import turtle

dory = turtle.Turtle()

# this draws a function specified as y = inside the definition with a 
#   window that has been resized to (-320,-370,320,370)
# pre: real number, real formula
# post:  porabola mudda fhada

def draw_parabola(x):
    h = turtle.window_height()
    print(h)
    w = turtle.window_width()
    print(w)
    turtle.setworldcoordinates((-w/2), (-h/2), (w/2), (h/2))
    turtle.penup()
    turtle.goto((-w / 2),(h / 2))
    print('look at me!')
    for i in range ((-w // 2), (w // 2)):
        x = i
        y = (x ** 2) / 100
        print('weeeeeeeeee!')
        turtle.pendown()
        turtle.goto(i, y)
    turtle.mainloop()
    

draw_parabola(0)

turtle.mainloop()
