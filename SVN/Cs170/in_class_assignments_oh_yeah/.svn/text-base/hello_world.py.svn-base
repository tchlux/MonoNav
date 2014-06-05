import turtle
import random
import math
TEXT = "Hello World!"
DIST = 5
FRAME_RATE = 30

#Class:   
#Runtime: 
#Mainloop:
class Hello_world:
    #Method:
    #Pre:   
    #Att's: 
    #Post:  
    def __init__(self, text):
        self.turtle = turtle.Turtle()
        self.turtle.hideturtle()
        self.text = text
        turtle.tracer(0)

    #Method:
    #Pre:   
    #Att's: 
    #Post:  
    def forward(self):
        turn = random.randint(-2,2)
        distance = DIST
        self.turtle.left(turn)
        self.turtle.forward(DIST)
        self.turtle.clear()
        self.turtle.write(self.text)

    #Method:
    #Pre:   
    #Att's: 
    #Post:  
    def keep_on_screen(self):
        half_window_width = turtle.window_width()/2
        half_window_height = turtle.window_height()/2
        (x,y) = self.turtle.pos()
        if (math.fabs(x) > half_window_width) or (math.fabs(y) > half_window_height):
            self.turtle.left(180)

    #Method:
    #Pre:   
    #Att's: 
    #Post:  
    def run(self):
        self.forward()
        self.keep_on_screen()
        turtle.update()
        turtle.ontimer(self.run, FRAME_RATE)

var_list = []
num_list = []

#Function:
#Pre:     
#Post:    
def prime_check(integer):
    boolean = True
    for i in range(2,integer):
        if (integer % i == 0):
            boolean = False
    return boolean

#Function:
#Pre:     
#Post:    
def hello_world():
    for i in range(2,100):
        if prime_check(i):
            var_list.append("var"+str(i))
            num_list.append(i)

hello_world()
for var in var_list:
    index = var_list.index(var)
    var = Hello_world(num_list[index])
    var.run()
turtle.mainloop()
