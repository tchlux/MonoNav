import turtle
import math
import random
import variables
import maincharacter
import maps

class MainGame:

    #This method initializes everything needed for the game
    def __init__(self):
        self.variables = variables.Variables()
        self.init_turtle()
        self.init_attributes()
        self.build_map()

    #This method initializes all the turtle attributes of the game
    def init_turtle(self):
        turtle.addshape("PlayerRunLeft.gif")
        turtle.addshape("PlayerRunRight.gif")
        turtle.addshape("PlayerStandLeft.gif")
        turtle.addshape("PlayerStandRight.gif")
        turtle.addshape("ground.gif")
        turtle.addshape("red_oval.gif")
        turtle.addshape("red_rect.gif")
        turtle.addshape("wood.gif")
        turtle.addshape("sky.gif")
        turtle.addshape("post.gif")
        turtle.listen()
        turtle.tracer(0)
        turtle.onkeypress(self.handle_left_arrow, "Left")
        turtle.onkeyrelease(self.handle_turn_release, "Left")
        turtle.onkeypress(self.handle_right_arrow, "Right")
        turtle.onkeyrelease(self.handle_turn_release, "Right")
        turtle.onkeypress(self.handle_space_bar, "space")
        turtle.onkeypress(self.handle_p_key, "p")
        turtle.setup(width=self.variables.INIT_WINDOW_WIDTH, height=self.variables.INIT_WINDOW_HEIGHT)
        turtle.bgpic("sky.gif")
#noted out for removal of graphics

    #This method initializes the attributes for the maingame
    #Pre:    The method is called
    #Post:   The attributes are put in memory
    def init_attributes(self):
        self.main_character = maincharacter.MainCharacter(0,0,self.variables.MAIN_CHAR_SPEED, self.variables.MAIN_CHAR_JUMP, self.variables.GRAVITY, self.variables.TERMINAL_Y_VELOCITY)
        self.main_character.turtle.goto(-310,-150)
        self.pen = turtle.Turtle()
        self.pen.pu()
        self.pen.ht()
        self.pen.shape("red_oval.gif")
        self.map_builder = turtle.Turtle()
        self.map_builder.pu()
        self.map_builder.ht()
        self.map_builder.shape("ground.gif")
        self.score = 0
        self.wall_list = []
        self.goals = []
        self.pause = False
        self.game_over = False

    #This method calls the map builder class for map1
    #Pre:    The method is called
    #Post:   The wall_list for the game is created
    def build_map(self):
        m = maps.Map1(self.map_builder, self.variables.BRICK_WIDTH, self.goals)
        bricks = 0
        walls = 0
        for brick in m.brick_list:
            bricks +=1
            for wall in brick.wall_list:
                walls += 1
                self.wall_list.append(wall)
        print("bricks, walls ",bricks,walls)

    #This method prints the point clicked to the terminal
    def click(self, x, y):
        print("        locations_list.append(("+str(x)+","+str(y)+"))")

    #Calls move_forward in the MainCharacter class (sprite.py)
    def handle_space_bar(self):
        self.main_character.jump()

    #Calls turn_left in MainCharacter class (sprite.py)
    def handle_left_arrow(self):
        self.main_character.left()

    #Calls turn_right in MainCharacter class (sprite.py)
    def handle_right_arrow(self):
        self.main_character.right()

    #Stops the x movement of the MainCharacter
    def handle_turn_release(self):
        self.main_character.stop()

    #Pauses the game
    def handle_p_key(self):
        self.pause = not self.pause
        self.write_pause()

    #Writes pause to the screen
    def write_pause(self):
        self.pen.goto(0,0)
        font = ("Arial", self.variables.FONT_SIZE, "normal")
        self.pen.write("Pause", False, "center", font)
        if self.pause == False:
            self.pen.clear()

    def check_goals(self):
        (x,y) = self.main_character.turtle.pos()
        remove = []
        for goal in self.goals:
            (a,b) = goal
            dist = ((x-a)**2 + (y-b)**2)**(1/2)
            if dist < self.variables.GOAL_RADIUS:
                remove.append(goal)
        for goal in remove:
            self.goals.remove(goal)
        if len(self.goals) < 1:
            self.game_over = True
            self.pen.clear()
        else:
            self.pen.clear()
            for goal in self.goals:
                self.pen.goto(goal)
                self.pen.stamp()

    #This method updates all mobile objects on the screen
    def update(self):
        self.main_character.update(self.wall_list)
        self.check_goals()

    #This method updates the entire game
    def run(self):
        if not self.game_over:
            if not self.pause:
                self.update()
            turtle.update()
            turtle.ontimer(self.run, self.variables.FRAME_RATE)
        else:
            self.pen.goto(0,0)
            font = ("Arial", self.variables.FONT_SIZE, "normal")
            self.pen.write("You Win!", False, "center", font)


m = MainGame()
m.run()
turtle.mainloop()
