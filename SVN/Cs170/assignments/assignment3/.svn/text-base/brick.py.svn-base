import wall

#this is the class for creating a brick out of wall objects
class StampBrick:
    #Sets the necessary attributes for the brick
    def __init__(self, location, width):
        (x,y) = location
        radius = width/2
        self.sides = radius
        self.location = location
        self.wall_list = []
        self.add_wall()

    #This method adds the four walls to the brick
    def add_wall(self):
        (x,y) = self.location
        p1 = (x-self.sides, y+self.sides)
        p2 = (x+self.sides, y+self.sides)
        p3 = (x+self.sides, y-self.sides)
        p4 = (x-self.sides, y-self.sides)
        self.wall_list.append(wall.Wall(p1,p2))
        self.wall_list.append(wall.Wall(p3,p2))
        self.wall_list.append(wall.Wall(p4,p3))
        self.wall_list.append(wall.Wall(p4,p1))

    def stamp(self, turtle):
        turtle.goto(self.location)
        turtle.stamp()
#noted out for removal of graphics
