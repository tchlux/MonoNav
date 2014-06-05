from brick import Brick
import turtle
import math

#this is what builds the level
class Level:

#this method creates the bricks
#pre: called
#post: the proper number of bricks are made
    def __init__(self, var, brick_list):
        self.number_of_rows = math.ceil(var.level)
        self.wbricks_per_row = int((var.worldw)//(var.wwidth*1.3))
        self.sbricks_per_row = int((var.worldw)//(var.swidth*1.3))
        tly = (var.worldh)/2
        for z in range (self.number_of_rows):
            tlx = -(var.worldw/2)
            tly -= 1.5*(var.wheight)
            if (z%2) == 1:
                for i in range(self.sbricks_per_row):
                    brick_list.append(Brick(var, (tlx,tly), var.sstrength))
                    tlx += 1.4*(var.swidth)
            else:
                for i in range(self.wbricks_per_row):
                    brick_list.append(Brick(var, (tlx,tly), var.wstrength))
                    tlx += 1.4*(var.wwidth)
