import turtle

#the ball
class Ball:

#constructor
#pre: called
#post: everything is initialized
    def __init__(self, var=None):
        self.turtle = turtle.Turtle()
        self.turtle.ht()
        self.turtle.penup()
        self.turtle.setheading(94)
        self.speed = var.bspeed
        self.radius = var.bradius
        self.turtle.goto(0, -150)
        self.pos = self.turtle.pos()
        self.last_pos = (0,0)

#the graphics are run
#pre: called
#post: the graphics are drawn
    def graphics(self):
        turtle.addshape(var.bimage)
        self.turtle.shape(var.bimage)

#this updates the ball location
#pre: all objects that could be intercepted with
#post: the bounce is called if there is an intersection
    def update(self, bricks, paddles, window, walls):
        self.turtle.clear()
        self.turtle.dot(10)
        self.collision(bricks, paddles, window, walls)
        self.turtle.forward(self.speed)
        self.last_pos = self.pos
        self.pos = self.turtle.pos()

#this method tests collision
#pre: all interceptable objects
#post: the collision is determined
    def collision(self, bricks, paddles, window, walls):
        for brick in bricks:
            for wall in brick.wall_list:
                if wall.wall_path_intersect(self.pos, self.last_pos):
                    self.bounce(wall.pos, wall.neg)
        for paddle in paddles:
            for wall in paddle.wall_list:
                if wall.wall_path_intersect(self.pos, self.last_pos):
                    self.bounce(wall.pos, wall.neg)
        for wall in window.wall_list:
            if wall.wall_path_intersect(self.pos, self.last_pos):
                self.bounce(wall.pos, wall.neg)
        for wall in walls:
            if wall.wall_path_intersect(self.pos, self.last_pos):
                self.bounce(wall.pos, wall.neg)

#bounce
#per: wall perpindicular angles are determined
#post: the bounce is given based off the collision angle
    def bounce(self, wall_pos, wall_neg):
        if abs(self.turtle.heading()-wall_pos) > abs(self.turtle.heading()-wall_neg):
            perp = wall_pos
        else:
            perp = wall_neg
        bounce = self.get_ranged_angle((2*perp - (self.turtle.heading() + 180)))
        self.turtle.setheading(bounce)
        self.turtle.forward(self.speed)
        (self.speed)
        self.pos = self.turtle.pos()
        self.last_pos = self.pos

#the angle is made less than 360 or more than 0
#pre: called
#post: bounce
    def get_ranged_angle(self, angle):
        while (angle > 360):
            angle -= 360
        while (angle < 0):
            angle += 360
        return angle

#the ball is cleared
#pre: called
#post: ball cleared
    def die(self):
        self.turtle.clear()
