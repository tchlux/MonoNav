import turtle
import math

dory = turtle.Turtle()

# this draws the left hand semi-circle (tail of fish)
# pre:  all must be positive integers
# post:  the screen looks CUURAAZY!

def draw_semicircle_at(w, h, k, turtle):
    r = w // 3
    turtle.penup()
    turtle.goto((h,(k+r)))
    turtle.pendown()
    for i in range ((k+r),(k-r-1),-1):
        y = i
        x = (((r ** 2) - (y - k) ** 2) ** (1/2)) + h
        turtle.goto(x,y)
    turtle.goto(h,(k+r))
    
# this draws pac man!
# pre:  all must be positive integers
# post:  the screen will eat you ghoul!

def draw_pac_man_at(w, h, k, turtle):
    turtle.penup()
    r = w // 3
    h = (2 * r) + h
    turtle.goto(h,k)
    dory.left(30)
    turtle.pendown()
    turtle.forward(r)
    (x,y) = turtle.pos()
    x = int(x)
    for i in range (x, (h-r-1), -1):
        x = i
        y = (((r ** 2) - (x - h) ** 2) ** (1/2)) + k
        turtle.goto(x,y)        
    turtle.penup()
    turtle.goto(h,k)
    dory.right(60)
    turtle.pendown()
    turtle.forward(r)
    (x,y) = turtle.pos()
    x = int(x)
    for i in range (x, (h-r-1), -1):
        x = i
        y = -(((r ** 2) - (x - h) ** 2) ** (1/2)) + k
        turtle.goto(x,y)

# this calls the definitions that draw the fish
# pre: all must be positive integers
# post: full life sized fish

def draw_fish_at(w,h,k,turtle):
    draw_semicircle_at(w,h,k,turtle)
    draw_pac_man_at(w,h,k,turtle)

draw_fish_at(200, 10, 10, dory)

turtle.mainloop()
