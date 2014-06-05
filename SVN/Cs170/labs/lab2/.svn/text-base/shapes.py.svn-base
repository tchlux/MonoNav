import turtle

#this is the generic shape class
class Shape:

#constructor: this initializes the shape
#pre: option parameters (x,y,pencolor,fillcolor)
#post: 
    def __init__(self, x=0, y=0, pencolor="black", fillcolor="black"):
        self.turtle = turtle.Turtle()
        self.turtle.ht()
        self.turtle.penup()
        self.turtle.goto(x,y)
        self.pencolor = pencolor
        self.fillcolor = fillcolor
        self.turtle.color(pencolor, fillcolor)
        self.click_range = 30

    def in_range(self, x,y, big_list):
        in_range = True
        for lst in big_list:
            (shapex, shapey) = lst[0]
            x_diff = abs(shapex-x)
            y_diff = abs(shapey-y)
            dist = (x_diff**2 + y_diff**2)**(1/2)
            if dist < self.click_range:
                in_range = False
                lst[1] = not lst[1]
        return in_range

    def update(self, big_list):
        self.turtle.clear()
        for lst in big_list:
            self.turtle.goto(lst[0])
            (x, y) = lst[0]
            if lst[2] == self.name:
                if self.alter(lst[1], x,y):
                    self.draw_shape(x,y)

    def alter(self, alter, x, y):
        return True


class Square(Shape):
    def __init__(self, fill='black', side_length=30):
        super().__init__(fillcolor=fill)
        self.side_length = side_length
        self.name = "Square"

    def draw_shape(self, x, y):
        self.turtle.goto(x,y)
        self.turtle.begin_fill()
        self.turtle.pd()
        for i in range (4):
            self.turtle.forward(self.side_length)
            self.turtle.left(90)
        self.turtle.end_fill()
        self.turtle.pu()



class Triangle(Shape):
    def __init__(self, fill="black", side_length=30):
        super().__init__(fillcolor=fill)
        self.side_length = side_length
        self.name = "Triangle"

    def draw_shape(self, x, y):
        self.turtle.goto(x,y)
        self.turtle.begin_fill()
        self.turtle.pd()
        for i in range (3):
            self.turtle.forward(self.side_length)
            self.turtle.left(120)
        self.turtle.end_fill()
        self.turtle.pu()

class Circle(Shape):
    def __init__(self, fill="black", radius=10):
        super().__init__(fillcolor=fill)
        self.radius = radius
        self.name = "Circle"

    def draw_shape(self, x, y):
        self.turtle.goto(x,y)
        self.turtle.begin_fill()
        self.turtle.pd()
        self.turtle.circle(self.radius)
        self.turtle.end_fill()
        self.turtle.pu()


class SquareAltered(Square):
    def __init__(self, fillcolor="red", side_length=50):
        super().__init__(fillcolor, side_length)
        self.name = "different Square"

    def alter(self, alter, x, y):
        if alter:
            try:
                self.side_length *= 2
            except:
                self.radius *= 2
            self.turtle.color(self.pencolor, self.fillcolor)
            self.draw_shape(x,y)
            try:
                self.side_length /= 2
            except:
                self.radius /= 2
            return False
        else:
            return True


class TriangleAltered(Triangle):
    def __init__(self, fillcolor="green", side_length=50):
        super().__init__(fillcolor, side_length)
        self.name = "different Triangle"

    def alter(self, alter, x, y):
        if alter:
            try:
                self.side_length *= 2
            except:
                self.radius *= 2
            self.turtle.color(self.pencolor, self.fillcolor)
            self.draw_shape(x,y)
            try:
                self.side_length /= 2
            except:
                self.radius /= 2
            return False
        else:
            return True


class CircleAltered(Circle):
    def __init__(self, fillcolor="blue", radius=20):
        super().__init__(fillcolor, radius)
        self.name = "different Circle"

    def alter(self, alter, x, y):
        if alter:
            try:
                self.side_length *= 2
            except:
                self.radius *= 2
            self.turtle.color(self.pencolor, self.fillcolor)
            self.draw_shape(x,y)
            try:
                self.side_length /= 2
            except:
                self.radius /= 2
            return False
        else:
            return True
