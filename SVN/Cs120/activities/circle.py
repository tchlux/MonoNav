import turtle

#this is curcle
class Circle:

    def __init__(self, init_x=0, init_y=0, init_radius=1):
        self.radius = init_radius
        self.x = init_x
        self.y = init_y
        turtle.penup()
        turtle.goto(self.x, self.y)
        turtle.pendown()
        turtle.shape('circle')
        self.turtle_resize()

    def turtle_resize(self):
        factor = self.radius / 10
        turtle.shapesize(factor, factor)

    def ten_times(self):
        self.radius = 10*self.radius

    def move_horizontal(self, amount):
        self.x += amount

    def move_vertical(self, amount):
        self.y += amount

    def area(self):
        return 3.14159365259 * self.radius * self.radius

    def distance(self, circle2):
        x_distance = (self.x) - (circle2.x)
        y_distance = (self.y) - (circle2.y)
        distance = ((x_distance)**2 + (y_distance)**2)**(1/2)
        return distance

    def are_overlapping(self, circle2):
        distance = self.distance(circle2)
        return((self.radius + circle2.radius) > distance)
        

    def __str__(self):
        return "(x,y,radius):  (%f, %f, %f)" % (self.x, self.y, self.radius)
