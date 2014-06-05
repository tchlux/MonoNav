from window import Window
from ball import Ball
from brick import Brick
from wall import Wall
from paddle import Paddle
from variables import Variables
from levels import Level
import turtle
import pickle
import os
v = Variables()

#this is what runs the whole game
class Game:

#constructor
#pre: the level number
#post: everythin is initialized
    def __init__(self, level=v.level):
        self.lives = 20
        self.score = 0
        self.time = 10
        self.second = 0
        self.turtle = turtle.Turtle()
        self.canvas = turtle.getcanvas()
        self.canvas.bind("<Motion>", self.move)
        self.turtle.pu()
        self.turtle.ht()
        self.turtle.goto(-25,200)
        self.turtle.write("Level: "+str(int(v.level*10)/10)+" Score: "+str(self.score)+" Lives: "+str(self.lives))
        self.wall_builder = turtle.Turtle()
        self.wall_builder.ht()
        self.wall_builder.pu()
        self.wbs = 0
        turtle.screensize(v.worldw, v.worldh, v.worldbg)
        turtle.tracer(0)
        turtle.onkeypress(self.left, "Left")
        turtle.onkeyrelease(self.stop, "Left")
        turtle.onkeypress(self.right, "Right")
        turtle.onkeyrelease(self.stop, "Right")
        turtle.onkeypress(self.up, "Up")
        turtle.onkeyrelease(self.stop, "Up")
        turtle.onkeypress(self.down, "Down")
        turtle.onkeyrelease(self.stop, "Down")
        turtle.onkeypress(self.reset_ball, "b")
        turtle.onkeypress(self.help, "h")
        turtle.onkeypress(self.wb, "w")
        turtle.onkeypress(self.s, "s")
        turtle.onkeypress(self.e, "e")
        turtle.listen()
        self.ball_list = []
        self.brick_list = []
        self.paddle_list = []
        self.wall_list = []
        self.window = Window(var=v)
        self.ball_list.append(Ball(var=v))
        self.paddle_list.append(Paddle(var=v))
        Level(v, self.brick_list)
        self.run()


#this function prints the high scores on the screen
#pre: called
#post: turtle object created to write the scores on the screen
    def return_highscores(self):
        turt = turtle.Turtle()
        turt.ht()
        turt.pu()
        if os.path.exists('highscores.txt'):
            with open('highscores.txt', 'rb') as f:
                a_file = pickle.load(f)
                f.close()
        else:
            a_file = []
        turt.goto(-25,-50)
        self.turtle.write(str(self.score))
        turt.setheading(270)
        a = 0
        for fil in a_file:
            if a % 2 == 0:
                turt.forward(10)
                turt.write(str(fil))
                a += 1
            else:
                a += 1

#this function adds the current high score to the list
#pre: called
#post: the high score is saved
    def add_highscore(self):
        if os.path.exists('highscores.txt'):
            with open('highscores.txt', 'rb') as f:
                a_file = pickle.load(f)
                f.close()
        else:
            a_file = []
        a_file.append(self.score)
        with open('highscores.txt', 'wb') as f:
            pickle.dump(a_file, f)
            f.close()

#this method prints some information to check if methods are working properly
#pre: called
#post: the stuff is printed to the terminal
    def help(self):
        print('------------')
        print(self.ball_list)
        print(self.brick_list)
        print(self.paddle_list)
        print('------------')
        for paddle in self.paddle_list:
            for wall in paddle.wall_list:
                print(wall)

#this is the wall builder
#pre: w is pressed
#post: the wallbuilder takes over the button controls
    def wb(self):
        if self.wall_builder.isvisible():
            print('hidden')
            self.wall_builder.ht()
            self.wall_builder.clear()
            self.wall_builder.pu()
        else:
            print('un hidden')
            self.wall_builder.showturtle()
            self.wall_builder.pd()

#this mothod initiates the building of a wall
#pre: s is pressed
#post: the wall builder startes the building process
    def s(self):
        self.w1 = self.wall_builder.pos()

#this method ends the wall builder process
#pre: e is pressed
#post: the wall is built and saved to the list
    def e(self):
        self.turtle.clear()
        self.w2 = self.wall_builder.pos()
        self.wall_list.append(Wall(self.w1, self.w2))
        print('w1, w2')
        print(self.w1, self.w2)

#the ball is reset to the starting position, status bar is updated too
#pre: b is pressed
#post: the ball that was in the list is cleared and a new ball is made
    def reset_ball(self):
        # for ball in self.ball_list:
        #     ball.die()
        # self.ball_list = []
        self.ball_list.append(Ball(var=v))
        self.lives -= 1
        self.turtle.clear()
        self.turtle.write("Level: "+str(int(v.level*10)/10)+" Score: "+str(self.score)+" Lives: "+str(self.lives))

#this is what moves the paddle with the mouse
#pre: the mouse is moved
#post: the paddle is moved to the mouse position
    def move(self,move):
        x = -(v.worldw/2) + move.x
        for paddle in self.paddle_list:
            wall = paddle.wall_list[3]
            (p1x, p1y) = wall.p1
            (movex) = x-p1x
            paddle.move(movex)

#this method stops the paddle when the arrow key is lifted
#pre: a key is released
#post: the paddle is stopped
    def stop(self):
        for paddle in self.paddle_list:
            paddle.stop()

#the paddle is given left speed
#pre: the left key is pressed
#post: the paddle is given left x velocity
    def left(self):
        if self.wall_builder.isvisible():
            self.wall_builder.left(10)
        else:
            for paddle in self.paddle_list:
                paddle.move_left()

#the paddle is given right speed
#pre: the left key is pressed
#post: the paddle is given right x velocity
    def right(self):
        if self.wall_builder.isvisible():
            self.wall_builder.right(10)
        else:
            for paddle in self.paddle_list:
                paddle.move_right()

    def up(self):
        pass
    def down(self):
        pass
    def up(self):
        if self.wall_builder.isvisible():
            self.wbs += 1
        else:
            for paddle in self.paddle_list:
                paddle.move_up()

    def down(self):
        if self.wall_builder.isvisible():
            self.wbs = 0
        else:
            for paddle in self.paddle_list:
                paddle.move_down()

#this is what runs the graphics for all objects
#pre: called
#post: all the walls are drawn
    def graphics(self):
        for wall in self.window.wall_list:
            wall.graphics()
        for shape in var.shapes:
            turtle.addshape(shape)
        for ball in self.ball_list:
            ball.graphics()
        for paddle in self.paddle_list:
            paddle.graphics()
        for brick in self.brick_list:
            brick.graphics()

#this method runs the program
#pre: called
#post: everything happens
    def run(self):
        if self.wall_builder.isvisible():
            self.turtle.write("building wall")
            self.wall_builder.forward(self.wbs)
            self.wall_builder.clear()
            self.wall_builder.stamp()
        for ball in self.ball_list:
            ball.update(self.brick_list, self.paddle_list, self.window, self.wall_list)
        for paddle in self.paddle_list:
            paddle.update()
        for brick in self.brick_list:
            if brick.dead:
                self.time += 5
                self.score += 100
                self.brick_list.remove(brick)
            else:
                brick.update()
        if len(self.brick_list) == 0:
            if self.score > 0:
                self.score += 17*self.time
            self.score += 1000
            v.level += .5
            Level(v, self.brick_list)
            self.lives += 2
            self.reset_ball()
            self.turtle.clear()
            self.turtle.write("Level: "+str(int(v.level*10)/10)+" Score: "+str(self.score)+" Lives: "+str(self.lives))
        if self.lives >= 0:
            if self.second == v.frame_rate:
                if self.time > 0:
                    self.time -= 1
            self.second += 1
            turtle.ontimer(self.run, v.frame_rate)
        else:
            self.turtle.clear()
            self.turtle.goto(-25,0)
            self.turtle.write("GAME OVER")
            self.turtle.goto(-25,-10)
            self.turtle.write("Your score: ", str(self.score))
            self.return_highscores()
            self.add_highscore()


g = Game()
g.run()
turtle.mainloop()
