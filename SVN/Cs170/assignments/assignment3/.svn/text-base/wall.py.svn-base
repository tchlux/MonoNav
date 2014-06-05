import turtle
import math

class Wall:
#constructor
    def __init__(self, p1=(0,0), p2=(10,10)):
        self.turtle = turtle.Turtle()
        self.turtle.ht()
        self.turtle.pu()
        self.turtle.goto(p1)
##################################draw
        # self.turtle.pd()
        # self.turtle.goto(p2)
####################################
        self.p1 = p1
        self.p2 = p2

#this tests if two path points intercept the wall (this is where collision errors come from
    def wall_path_intersect(self, path1, path2):
        cross = False
        (p1x, p1y) = self.p1
        (p2x, p2y) = self.p2
        (path1x, path1y) = path1
        (path2x, path2y) = path2
        #Tests to see if the object's path is close to the wall, x then y, path1 -> 2
        var1 = (((p1x-10) < path1x < (p2x+10)) or ((p1x+10) > path1x > (p2x-10))) 
        var2 = (((p1y-10) < path1y < (p2y+10)) or ((p1y+10) > path1y > (p2y-10)))
        var3 = (((p1x-10) < path2x < (p2x+10)) or ((p1x+10) > path2x > (p2x-10)))
        var4 = (((p1y-10) < path2y < (p2y+10)) or ((p1y+10) > path2y > (p2y-10)))
        #If the object is close enough to the wall, then check collision
        if (var1 and var2) or (var3 and var4):
#########################################draw
            # self.turtle.clear()
            # self.turtle.pencolor("blue")
            # self.turtle.goto(self.p1)
            # self.turtle.goto(self.p2)
#########################################
            return self.collision(p1x, p1y, p2x, p2y, path1x, path1y, path2x, path2y)
        return False

#this method does the majority of the work, it calculates if the path points cross
#   the wall, it returns a False if they don't pass, a True if they do
    def collision(self, p1x, p1y, p2x, p2y, path1x, path1y, path2x, path2y):
        (p1p2xdiff,p1p2ydiff) = (p1x - p2x, p1y - p2y)
        (p1path1xdiff,p1path1ydiff) = (p1x-path1x, p1y-path1y)
        (p1path2xdiff,p1path2ydiff) = (p1x-path2x, p1y-path2y)
        spath1 = p1p2xdiff * p1path1ydiff - p1p2ydiff * p1path1xdiff
        spath2 = p1p2xdiff * p1path2ydiff - p1p2ydiff * p1path2xdiff
        try:
            comp = spath1 / spath2
        except:
            comp = 1
        #Tests to see if the object's path is through the wall, x then y, path1 -> 2
        var1 = (p1x) < path1x < (p2x)
        var2 = (p1y) < path1y < (p2y)
        var3 = (p1x) < path2x < (p2x)
        var4 = (p1y) < path2y < (p2y)
        #If the object is close enough to the wall, then check collision
        between = (var1 or var2 or var3 or var4)
######################################draw
        # if ((comp>0) and between):
        #     self.turtle.clear()
        #     self.turtle.pencolor("red")
        #     self.turtle.goto(self.p1)
        #     self.turtle.goto(self.p2)
##########################################
        return ((comp>0) and between)








#         if (comp>0) and between:
#             self.hits_taken += 1


#         self.hits_taken = 0
#         self.turtle.setheading(self.turtle.towards(p2))
#         self.p1top2 = self.turtle.heading()
#         self.graphics()
#         self.pos = self.get_ranged_angle(self.p1top2 + 90)
#         self.neg = self.get_ranged_angle(self.p1top2 - 90)

# #used for movement of paddle
#     def move(self, right=0, up=0):
#         (x1, y1) = self.p1
#         (x2, y2) = self.p2
#         self.p1 = ((x1+right),(y1+up))
#         self.p2 = ((x2+right),(y2+up))




# #returns the location of the points
#     def __str__(self):
#         (x,y) = self.p1
#         (a,b) = self.p2
#         return "("+str(x)+","+str(y)+") ("+str(a)+","+str(b)+")"

# #draws all the lines
#     def graphics(self):
#         self.turtle.clear()
#         self.turtle.goto(self.p1)
#         self.turtle.pendown()
#         self.turtle.goto(self.p2)
#         self.turtle.penup()





# #used to get an angle < 0, >360
#     def get_ranged_angle(self, angle):
#         while (angle > 360):
#             angle -= 360
#         while (angle < 0):
#             angle += 360
#         return angle




# this is what does the calculations, using angles from the points of the wall to the path points to see if they cross the wall

        # (a,b) = ((p1x - path1x),(p1y - path1y))
        # (c,d) = ((p1x - path2x),(p1y - path2y))
        # (e,f) = ((p2x - path1x),(p2y - path1y))
        # (g,h) = ((p2x - path2x),(p2y - path2y))
        # (i,j) = ((p1x - p2x),(p1y - p2y))
        # (k,l) = ((p2x - p1x),(p2y - p1y))
        # if a == 0:
        #     a = .001
        # if c == 0:
        #     c = .001
        # if e == 0:
        #     e = .001
        # if g == 0:
        #     g = .001
        # if i == 0:
        #     i = .001
        # if k == 0:
        #     k = .001
        # p1top2 = self.get_ranged_angle(math.degrees(math.atan(j/i)))
        # p2top1 = self.get_ranged_angle(math.degrees(math.atan(l/k)))
        # p1topath1 =  self.get_ranged_angle(math.degrees(math.atan(b/a)))
        # p1topath2 =  self.get_ranged_angle(math.degrees(math.atan(d/c)))
        # p2topath1 =  self.get_ranged_angle(math.degrees(math.atan(f/e)))
        # p2topath2 =  self.get_ranged_angle(math.degrees(math.atan(h/g)))
        # s1 = p1top2 - p1topath1
        # s2 = p1top2 - p1topath2
        # s3 = p2top1 - p2topath1
        # s4 = p2top1 - p2topath2
        # try:
        #     comp_value1 = s1 / s2
        #     comp_value2 = s3 / s4
        #     if (comp_value1 < 0) and (comp_value2 < 0):# or (a1 < .6):
        #         self.hits_taken += 1
        #         return True
        #     else:
        #         return False
        # except:
        #     self.hits_taken += 1
        #     return True
