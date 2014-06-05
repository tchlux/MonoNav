import turtle
import math

class Wall:
    class Point:
        def __init__(self, x, y):
            self.x = x
            self.y = y

#constructor
    def __init__(self, p1=(0,0), p2=(10,10)):
        self.hits_taken = 0
        self.turtle = turtle.Turtle()
        self.turtle.ht()
        self.turtle.penup()
        self.turtle.goto(p1)
        self.p1 = p1
        self.p2 = p2
        self.turtle.setheading(self.turtle.towards(p2))
        self.p1top2 = self.turtle.heading()
        self.pos = self.get_ranged_angle(self.p1top2 + 90)
        self.neg = self.get_ranged_angle(self.p1top2 - 90)
        self.graphics()

#returns the location of the points
    def __str__(self):
        (x,y) = self.p1
        (a,b) = self.p2
        return "("+str(x)+","+str(y)+") ("+str(a)+","+str(b)+")"

#draws all the lines
    def graphics(self):
        self.turtle.clear()
        self.turtle.goto(self.p1)
        self.turtle.pendown()
        self.turtle.goto(self.p2)
        self.turtle.penup()

#used for movement of paddle
    def move(self, right=0, up=0):
        (x1, y1) = self.p1
        (x2, y2) = self.p2
        self.p1 = ((x1+right),(y1+up))
        self.p2 = ((x2+right),(y2+up))

#used to get an angle < 0, >360
    def get_ranged_angle(self, angle):
        while (angle > 360):
            angle -= 360
        while (angle < 0):
            angle += 360
        return angle

#this tests if two path points intercept the wall (this is where collision errors come from
    def wall_path_intersect(self, path1, path2):
        a1 = self.Point(self.p1[0], self.p1[1])
        a2 = self.Point(self.p2[0], self.p2[1])
        b1 = self.Point(path1[0], path1[1])
        b2 = self.Point(path2[0], path2[1])
        bounding_box1 = False
        bounding_box2 = False
        #Tests to see if the object's path is close to the wall, x then y
        bounding_box1 = (((a1.x-20) < b1.x < (a2.x+20)) or ((a1.x+20) > b1.x > (a2.x-20))) and (((a1.x-20) < b2.x < (a2.x+20)) or ((a1.x+20) > b2.x > (a2.x-20)))
        bounding_box2 = (((a1.y-20) < b1.y < (a2.y+20)) or ((a1.y+20) > b1.y > (a2.y-20))) and (((a1.y-20) < b2.y < (a2.y+20)) or ((a1.y+20) > b2.y > (a2.y-20)))
        #If the object is close enough
        if (bounding_box1) and (bounding_box2):
            cross = self.intersects(a1,a2,b1,b2)
            if cross:
                self.hits_taken += 1
            return cross
        return False

    def _ccw(self, p1, p2, p3):
        return ((p2.x-p1.x)*(p3.y-p1.y) > (p2.y-p1.y)*(p3.x-p1.x))

    def intersects(self, a1, a2, b1, b2):
        return self._ccw(a1,b1,b2) != self._ccw(a2,b1,b2) and self._ccw(a1,a2,b1) != self._ccw(a1,a2,b2)
