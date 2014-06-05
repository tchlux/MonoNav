import math
import variables as v

class Wall:
    class Point:
        def __init__(self, x, y):
            self.x = x
            self.y = y
#constructor
    def __init__(self, p1=(0,0), p2=(10,10), hp=float("inf"), draw=True):
        self.hp = hp
        self.p1 = self.Point(p1[0], p1[1])
        self.p2 = self.Point(p2[0], p2[1])
        self.mid = ((p2[0]+p1[0])/2.0, (p2[1]+p1[1])/2.0)
        if draw:
            import turtle
            turtle.tracer(0)
            self.turt = turtle.Turtle()
            self.turt.ht()
            self.turt.pu()
            self.turt.goto((self.p1.x, self.p1.y))
            self.turt.pd()
            self.turt.goto((self.p2.x, self.p2.y))
            turtle.update()

    def live(self):
        if self.hp <= 0:
            v.REMOVE_WALL(self)

    def distance_to_wall(self, p3):
        x3, y3 = float(p3[0]), float(p3[1])
        if self.p2.y - self.p1.y == 0:
            x, y = (x3, self.p1.y)
        elif self.p2.x - self.p1.x == 0:
            x, y = (self.p1.x, y3)
        else:
            delta_x = self.p2.x - self.p1.x
            delta_y = self.p2.y - self.p1.y
            top = (x3 * delta_x) / delta_y + (self.p1.x * delta_y) / delta_x + y3 - self.p1.y
            bottom = delta_y / delta_x + delta_x / delta_y
            x = top / bottom
            y = x * (delta_y / delta_x) - self.p1.x * (delta_y / delta_x) + self.p1.y
        x, y = self.make_in_range(x,y)
        distance = ((x - x3) ** 2 + (y - y3) ** 2) ** 0.5
        return [distance, (x, y)]

    def make_in_range(self, x, y):
        max_x = max(self.p1.x, self.p2.x)
        max_y = max(self.p1.y, self.p2.y)
        min_x = min(self.p1.x, self.p2.x)
        min_y = min(self.p1.y, self.p2.y)
        if x < min_x:
            x = min_x
        elif x > max_x:
            x = max_x
        if y < min_y:
            y = min_y
        elif y > max_y:
            y = max_y
        return x, y

#tests if wall and path intersect based off endpoints
    def wall_path_intersect(self, path1, path2):
        a1 = self.Point(self.p1.x, self.p1.y)
        a2 = self.Point(self.p2.x, self.p2.y)
        b1 = self.Point(path1[0], path1[1])
        b2 = self.Point(path2[0], path2[1])
        return self.intersects(a1,a2,b1,b2)

#formula for testing sign of point comparison
    def _ccw(self, p1, p2, p3):
        return ((p2.x-p1.x)*(p3.y-p1.y) > (p2.y-p1.y)*(p3.x-p1.x))

#cross examines points to test sign equivalence, determines whether or
#not paths intersect
    def intersects(self, a1, a2, b1, b2):
        return self._ccw(a1,b1,b2) != self._ccw(a2,b1,b2) and self._ccw(a1,a2,b1) != self._ccw(a1,a2,b2)

