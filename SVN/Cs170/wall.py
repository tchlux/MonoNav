import math
import turtle

BOUNDING_BOX = 10

class Wall:
    class Point:
        def __init__(self, x, y):
            self.x = x
            self.y = y
#constructor
    def __init__(self, p1=(0,0), p2=(10,10)):
        self.p1 = p1
        self.p2 = p2
        turtle.tracer(0)
        turt = turtle.Turtle()
        turt.ht()
        turt.pu()
        turt.goto(p1)
        turt.pd()
        turt.goto(p2)
        turt.pu()

#this tests if two path points intercept the wall (this is where collision errors come from
    def wall_path_intersect(self, path1, path2):
        a1 = self.Point(self.p1[0], self.p1[1])
        a2 = self.Point(self.p2[0], self.p2[1])
        b1 = self.Point(path1[0], path1[1])
        b2 = self.Point(path2[0], path2[1])
        return self.intersects(a1,a2,b1,b2)

    def _ccw(self, p1, p2, p3):
        return ((p2.x-p1.x)*(p3.y-p1.y) > (p2.y-p1.y)*(p3.x-p1.x))

    def intersects(self, a1, a2, b1, b2):
        return self._ccw(a1,b1,b2) != self._ccw(a2,b1,b2) and self._ccw(a1,a2,b1) != self._ccw(a1,a2,b2)
