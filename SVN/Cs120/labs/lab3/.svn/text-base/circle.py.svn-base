import turtle

dory = turtle.Turtle()
# this draws the circle at a given point "h,k" w/ a radius of "r"
# pre:  all must be positive integers
# post: when i snap my fingers, you'll fall to the floor

def draw_circle_at(r, h, k, turtle):
    turtle.penup()
    turtle.goto((h+r),k)
    turtle.pendown()
    print('intial x', h, 'initial y', k)
    for i in range ((h+r),(h-r-1),-1):
        x = i
        y = (((r ** 2) - (x - h) ** 2) ** (1/2)) + k
        turtle.goto(x,y)
    for i in range ((h-r),(h+r+1),1):
        x = i
        y = -((((r ** 2) - (x - h) ** 2) ** (1/2))) + k
        turtle.goto(x,y)

print(" to the windooooow")
print("       to the wall!")
print(' watch that circle draw!')
print('')
print('')
print(' oooooohhh')

draw_circle_at(50,100,100,dory)
turtle.mainloop()


