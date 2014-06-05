import brick

class Map1:

    #This method creates all the blocks needed for map1
    def __init__(self, turtle, brick_width, goal_list):
        for i in range(-3,6,2):
            goal_list.append((200*i*(.32),((i-5)*brick_width/2.05)+55))
        for i in range(-3,6,2):
            goal_list.append(((200*i*(.32)-130),((i-5)*brick_width/2.05)+205))


        self.brick_list = []

        #This creates all the wood blocks in the game
        turtle.shape("wood.gif")
        locations_list = []
        for i in range(-3,6):
            locations_list.append(((200*i*(.32)-130),((i-5)*brick_width/2.05)+150))
        for i in range(-3,6):
            locations_list.append((200*i*(.32),(i-5)*brick_width/2.05))
        for i in range(-10,10):
            locations_list.append((i*brick_width,290))
        locations_list.append((350,40))
        locations_list.append((240,100))
        for loc in locations_list:
            a = brick.StampBrick(loc, brick_width)
            a.stamp(turtle)
            self.brick_list.append(a)

        #This creates all of the posts on the side
        turtle.shape("post.gif")
        locations_list = []
        for i in range(-10,10):
            locations_list.append((385, i*brick_width*.9))
            locations_list.append((-385, i*brick_width*.9))
        for loc in locations_list:
            a = brick.StampBrick(loc, brick_width)
            a.stamp(turtle)
            self.brick_list.append(a)

        #This creates the ground
        turtle.shape("ground.gif")
        locations_list = []
        for i in range(-10,10):
            locations_list.append((i*brick_width*.95,-280))
        for loc in locations_list:
            a = brick.StampBrick(loc, brick_width)
            a.stamp(turtle)
            self.brick_list.append(a)

#2nd map
class Map2:
    #This method creates all the building blocks for map2
    def __init__(self, turtle, brick_width):
        self.brick_list = []
        locations_list = [(0,0),(10,0),(20,0),(0,10),(10,10),(20,10)]
        for loc in locations_list:
            self.brick_list.append(brick.StampBrick(loc, brick_width))
        for brick in self.brick_list:
            brick.stamp(turtle)
