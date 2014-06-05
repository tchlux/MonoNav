import turtle

#The maincharacter
class MainCharacter:

    #This constructs all necessary attributes for the maincharacter
    def __init__(self, x, y, speed, jump_speed, gravity, terminalyvelocity):
        self.turtle = turtle.Turtle()
        self.turtle.shape("PlayerStandRight.gif")
        self.turtle.pu()
        self.xvel = 0
        self.yvel = 0
        self.last_x = 1
        self.speed = speed
        self.jump_speed = jump_speed
        self.gravity = gravity
        self.terminalyvel = terminalyvelocity
        self.turtle.goto(x,y)

    #This method gives the maincharacter left velocity (negative)
    def left(self):
        self.xvel = -self.speed
        self.last_x = -2

    #This method gives the maincharacter rigth velocity (positive)
    def right(self):
        self.xvel = self.speed
        self.last_x = 2

    #This method gives the maincharater upwards y velocity (positive)
    def jump(self):
        if self.yvel == 0:
            self.yvel = self.jump_speed

    #This method stops the movement of the character on the x axis
    def stop(self):
        self.xvel = 0

    #This method moves the player for each update that is run based on velocities
    def move(self, wall_list):
        #check if x move is valid, if valid then move, else, 0 xvel
        (x,y) = self.turtle.pos()
        (nex,ney) = (x+self.xvel, y+self.yvel)
        if self.valid_move(wall_list, nex, y):
            self.turtle.goto(nex, y)
        else:
            self.xvel = 0
            self.turtle.goto(x-self.last_x,y)
        #check if y move is valid, if valid then move, else, 0 yvel
        if self.valid_move(wall_list, x, ney):
            (x,y) = self.turtle.pos()
            self.turtle.goto(nex, ney)
        else:
            self.yvel = 0

    #This method determines if the current velocities can be maintained without
    # a collision, if they can, the variable clear is returned as True, if they
    # can't, clear is returned as false
    def valid_move(self, wall_list, nex, ney):
        clear = True
        (x,y) = self.turtle.pos()
        for wall in wall_list:
            if wall.wall_path_intersect((x,y),(nex,ney)):
                clear = False
        return clear

    #This method sets the picture for the character based on the current x velocity
    # or if there is none, an attribute stored of last x velocity
    def set_picture(self):
        if self.xvel > 0:
            self.turtle.shape("PlayerRunRight.gif")
        elif self.xvel < 0:
            self.turtle.shape("PlayerRunLeft.gif")
        elif self.last_x < 0:
            self.turtle.shape("PlayerStandLeft.gif")
        else:
            self.turtle.shape("PlayerStandRight.gif")

    #This method updates the maincharacter
    def update(self, wall_list):
        (x,y) = self.turtle.pos()
        if self.yvel > self.terminalyvel:
            self.yvel -= self.gravity
        self.move(wall_list)
        self.set_picture()
