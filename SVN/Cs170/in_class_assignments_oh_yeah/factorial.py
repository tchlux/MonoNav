def factorial(num):
    if num == 0:
        return 1
    else:
        return factorial(num-1) * num

print(factorial(5))

            
# :) turtle running like a boss
import turtle
import random
class DrunkTurtle:
    def __init__(self):
        self.lst = []
        self.number_of_turtles = 3
        self.frame_rate = 30
        self.walking_pace = 2
        self.rs_left = -4
        self.rs_right = 2
        self.leash = turtle.window_width()/2
        self.make_the_turtles_drink()
        self.run()

    def make_the_turtles_drink(self):
        for i in range(self.number_of_turtles):
            self.lst.append(turtle.Turtle())


    def stammering_turtle(self):
        for turt in self.lst:
            turt.forward(self.walking_pace)
            (x,y) = turt.pos()
            dist = ((x**2 + y**2)**(1/2))
            if dist >= self.leash:
                turt.left(turt.heading() - turt.towards(0,0))
            else:
                turt.left(random.randint(self.rs_left, self.rs_right))

    def stammering_turtle(self):
        for turt in self.lst:
            turt.forward(2)
            (x,y) = turt.pos()
            dist = ((x**2 + y**2)**(1/2))
            if dist >= turtle.window_width()/2:
                turt.left(turt.heading()-turt.towards(0,0))
            else:
                turt.left(random.randint(-4,2))

    
    def run(self):
        self.stammering_turtle()
        turtle.update()
        turtle.ontimer(self.run, self.frame_rate)

harry = DrunkTurtle()
turtle.mainloop()
