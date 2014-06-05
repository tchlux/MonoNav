"""
File: bouncing_ball.py
Author: Scotty Smith

Class CreateWindow creates a window that you can draw upon.  
Class Ball represents a generic ball that can be drawn on the
    window CreateWindow represents.
"""
import random
import turtle
import math


PADDLE_HEIGHT = 20
PADDLE_WIDTH = 80
PADDLE_SPEED = 5
WINDOW_WIDTH = 640
WINDOW_HEIGHT = 480
REFRESH_RATE = 30
NUM_CIRCLES = 100
BACKGROUND_COLOR = "black"
RADIUS = 20
MAX_COLOR = 255
SPEED = 5

class UpdatingWindow:

    #__init__ - the constructor for updating window
    #Pre:  None
    #Post: Sets up the window the correct size and shape.  Creates a ball
    #      that can be referenced in the rest of the class.
    def __init__(self, width=WINDOW_WIDTH, height=WINDOW_HEIGHT, speed=SPEED):
        turtle_handle = turtle.getturtle()
        self.paddle = Paddle()
        self.ball = Ball(width, height, turtle_handle, speed, self.paddle)
        turtle.setup(width, height)
        turtle.colormode(255)
        turtle.onkeypress(self.paddle.left, "Left")
        turtle.onkeypress(self.paddle.right, "Right")
        turtle.onkeyrelease(self.paddle.stop_move, "Left")
        turtle.onkeyrelease(self.paddle.stop_move, "Right")
        turtle.listen()

    #update - responsible for making sure that all necessary objects are updated
    #Pre:  Instance variables for the ball have been created and initialized in
    #      UpdatingWindow constructor.
    #Post: Clears the screen of previous drawings.  Draws the ball in the 
    #      correct location
    def update(self):
        self.ball.update_ball()
        self.ball.draw()
        self.paddle.update()
        self.paddle.draw()
        if self.ball.game_over == True:
            self.game_over()
        else:
            turtle.ontimer(self.update, REFRESH_RATE)

#this is what draws game over on the screen
#pre: game over method is called
#post: new turtle created for drawing, font is set, game over is written
    def game_over(self):
        draw = turtle.Turtle()
        draw.ht()
        font = ("Arial", 40, "normal")
        draw.write("Game Over", False, "center", font)

    #run - causes the animation to begin.
    #Pre:  The constructor for this class has been called
    #Post: Starts the process of updating new positions of the ball, 
    #      through the update method.
    def run(self):
        turtle.tracer(0)
        self.update()
        turtle.mainloop()

class Ball:
    #__init__ - Ball constructor
    #Pre:  width and height are the width and height of the window in which
    #      the ball is being drawn.
    #      turtle_handle is a turtle object which can be used to draw the ball.
    #Post: Creates an initialized the instance variables necessary to draw
    #      a circle to represent a ball.
    def __init__(self, width, height, turtle_handle, speed, paddle_object):
        self.paddle = paddle_object
        self.radius = RADIUS
        self.diameter = 2 * self.radius
        self.speed = speed
        self.game_over = False
        
        #such that a ball draw at these x and y locations were to be drawn
        #with the generated radius, it is fully contained within the drawable
        #area.
        self.x_coord = random.randint(-1* width // 2 + self.radius, 
                                       width // 2 - self.radius)
        self.y_coord = random.randint((-1 * height // 2) + self.radius,
                                      (height // 2) - self.radius)
        self.color = (random.randint(0, MAX_COLOR),
                      random.randint(0, MAX_COLOR),
                      random.randint(0, MAX_COLOR))
        self.turtle = turtle_handle
        self.turtle.setheading(random.randint(0,360))
        self.turtle.ht()

# this method returns true for in paddle and false if not
#pre: a paddle object is saved in self
#post: a true if paddle is overlapping ball, otherwise false
    def in_paddle(self):
        (self.paddle_x, self.paddle_y) = self.paddle.turtle.pos()
        if ((self.y < (self.paddle_y+self.paddle.height/2+RADIUS)) and ((self.paddle_x-self.paddle.width/2) < self.x < (self.paddle_x+self.paddle.width/2))):
            return True
        else:
            return False

    #keep_on_screen - this keeps the ball on the screen by deflecting
        #off the sides
    #pre: the ball has a turtle
    #post: the turn is provided (0 if not near wall)
    def keep_on_screen(self):
        turn = 0
        (self.x, self.y) = self.turtle.pos()
        if self.in_paddle():
            self.turtle.goto(self.x, (self.paddle_y + self.paddle.height/2 + 18))
            new_heading = 360 - self.turtle.heading()
            turn = (new_heading - self.turtle.heading())
        elif ((math.fabs(self.x)+RADIUS/8) > WINDOW_WIDTH//2):
            new_heading = 180 - self.turtle.heading()
            turn = (new_heading - self.turtle.heading())
        elif (((self.y)+RADIUS/8) > WINDOW_HEIGHT//2):
            new_heading = 360 - self.turtle.heading()
            turn = (new_heading - self.turtle.heading())
        elif ((self.y)+RADIUS/8) < -WINDOW_WIDTH/2:
            self.game_over = True
        else:
            turn = 0
        return turn

    #update_ball - updates the ball as time elapses.  Does nothing for this ball
    #Pre:  the ball was initialized, there is a method for keep on screen
    #Post: ball is moved accordingly
    def update_ball(self):
        turn = self.keep_on_screen()
        self.turtle.left(turn)
        self.turtle.forward(self.speed)

    #draw - draws the ball to the appropriate turtle canvas
    #Pre:  self.x_coord and self.y_coord are integers which represent the center
    #      point of the circle we wish to draw. Tuple
    #      self.radius is the radius of that circle.
    #      self.color is a valid color that the turtle class accepts
    #Post: Draws the ball centered at (self.x_coord, self.y_coord), with radius
    #      self.radius.
    def draw(self):
        self.turtle.clear()
        self.turtle.dot(self.radius, self.color)

class Paddle:

# paddle constructor: this initializes the paddle and all of its variables
#pre: the height width and speed are already given or given when initialized
#post: the variables for the paddle are initialized
    def __init__(self, height=PADDLE_HEIGHT, width=PADDLE_WIDTH, paddle_speed=PADDLE_SPEED):
        self.height = height
        self.width = width
        self.turtle = turtle.Turtle()
        self.turtle.ht()
        self.turtle.penup()
        initial_y_position = (-(WINDOW_HEIGHT/2) + height/2)
        self.turtle.goto(0, initial_y_position)
        self.paddle_speed = paddle_speed
        self.speed = 0

#this function initiates left movement of the paddle
#pre: self.paddle_speed has been initialized
#post: the current speed is set to the paddle speed
    def left(self):
        self.speed = -(self.paddle_speed)

#this function initiates right movement of the paddle
#pre: self.paddle_speed has been initialized
#post: the current speed is set to the paddle speed
    def right(self):
        self.speed = self.paddle_speed

#this function stops the paddle from moving
#pre: either the left or right arrow keys have been released
#post: paddle speed is set to 0
    def stop_move(self):
        self.speed = 0

#this function handles drawing the paddle every fram
#pre: turtle object exists
#post: the paddle is drawn in its new position
    def draw(self):
        (x,y) = self.turtle.pos()
        top_left = ((x-self.width/2),(y+self.height/2))
        bottom_left = ((x-self.width/2),(y-self.height/2))
        bottom_right = ((x+self.width/2),(y-self.height/2))
        top_right = ((x+self.width/2),(y+self.height/2))
        self.turtle.clear()
        self.turtle.begin_fill()
        self.turtle.goto(top_left)
        self.turtle.goto(bottom_left)
        self.turtle.goto(bottom_right)
        self.turtle.goto(top_right)
        self.turtle.goto(top_left)
        self.turtle.end_fill()
        self.turtle.goto(x,y)

#this function moves the paddle
#pre: none
#post: the paddle moves the according speed
    def update(self):
        self.turtle.forward(self.speed)

game = UpdatingWindow()
game.run()
