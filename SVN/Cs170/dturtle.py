import turtle
import random

FRAME_RATE = 30
NUMBER_OF_TURTLES = 3
STAMMER_RANGE = [1,3]
TURN_RANGE = [-2,2]
RED = [0,255]
GREEN = [0,255]
BLUE = [0,255]
SCREEN_CLEAR_FREQ = 600

DOT_RANGE = [3,6]
DOTS = []
DOT_OCCURANCE = [1,6]

PHRASES = ["weher aer my keys???", "HHHEY YOU", "mhhmmmmh", "Sost it syou slpamling fsac", "I sware if you alsk", "   L", "boodaba"]
PHRASE_OCCURANCE = [1,70]

for i in range(DOT_OCCURANCE[0]):
    DOTS.append(True)
for i in range(DOT_OCCURANCE[1]*len(DOTS) - DOT_OCCURANCE[0]*len(DOTS)):
    DOTS.append(False)
for i in range(PHRASE_OCCURANCE[1]*len(PHRASES) - PHRASE_OCCURANCE[0]*len(PHRASES)):
    PHRASES.append('')

# :) turtle running like a boss
class Fun:
    class _DrunkTurtle:
        def __init__(self, wp, turn, leash, job):
            turtle.tracer(0)
            self.turtle = turtle.Turtle()
            self.turtle.pu()
            self.turtle.setheading(random.randint(0,360))
            self.walking_pace = wp
            self.turn = turn
            self.leash = leash
            self.job = job


        def calculate_turn(self):
            (x,y) = self.turtle.pos()
            # if abs(x) > turtle.window_width()/2:
            #     self.turtle.pu()
            #     self.turtle.goto(-x,y)
            # if abs(y) > turtle.window_height()/2:
            #     self.turtle.pu()
            #     self.turtle.goto(x,-y)
            dist = ((x**2 + y**2)**(1/2))+1
            total = (dist/self.leash) + (self.leash/dist)
            norm_factor = (self.leash/dist)/total
            leash_factor = (dist/self.leash)/total
            turn = -(leash_factor)*self.turtle.towards(0,0) + (norm_factor)*self.turn
            return turn
#            return self.turn

        def stammer_along(self):
            self.turtle.right(self.calculate_turn())
            self.turtle.forward(self.walking_pace)
            self.job(self.turtle)


    def __init__(self):
        turtle.tracer(0)
        turtle.clearscreen()
        turtle.bgcolor("light blue")
        turtle.colormode(255)
        self.run_loop = 0
        self.turtle_list = []
        self.leash = turtle.window_width()/2
        self.dot_size = random.randint(DOT_RANGE[0], DOT_RANGE[1])
        self.make_the_turtles_drink()
        self.run()

    def make_the_turtles_drink(self):
        jobs = [self.give_them_a_bingo_marker, self.give_them_a_pen, self.give_them_a_keyboard]
        for i in range(NUMBER_OF_TURTLES):
            walking_pace = random.randint(STAMMER_RANGE[0], STAMMER_RANGE[1])
            turn = random.randint(TURN_RANGE[0],TURN_RANGE[1])
            self.turtle_list.append(self._DrunkTurtle(walking_pace, turn, self.leash, random.choice(jobs)))

    def give_them_a_pen(self, t):
        t.pd()
        t.pencolor(self.color)

    def give_them_a_bingo_marker(self, t):
        t.pencolor(self.color)
        if random.choice(DOTS):
            t.dot(self.dot_size)

    def give_them_a_keyboard(self, t):
        t.pencolor(self.color)
        t.write(random.choice(PHRASES))
    
    def new_color(self):
        red = random.randint(RED[0],RED[1])
        green = random.randint(GREEN[0],GREEN[1])
        blue = random.randint(BLUE[0],BLUE[1])
        self.color = (red, green, blue)

    def run(self):
        self.new_color()
        for lil_guy in self.turtle_list:
            lil_guy.stammer_along()
        turtle.update()
        self.run_loop += 1
        if self.run_loop < SCREEN_CLEAR_FREQ:
            turtle.ontimer(self.run, FRAME_RATE)
        else:
            self.__init__()

Fun()
turtle.mainloop()
