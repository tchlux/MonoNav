import turtle
import shapes

#This initializes the turtle, along with the shapes/objects that we are drawing with, the state of each shape, along with a list that holds all shape locations and types.
#input: None
class Window():
    def __init__(self):
        self.turtle = turtle.Turtle()
        self.turtle.ht()
        self.turtle.pu()
        self.square = shapes.Square()
        self.triangle = shapes.Triangle()
        self.circle = shapes.Circle()
        self.square_altered = shapes.SquareAltered()
        self.triangle_altered = shapes.TriangleAltered()
        self.circle_altered = shapes.CircleAltered()
        self.state = self.square.name
        self.big_list = []

        width = turtle.window_width()
        height = turtle.window_height()
        self.scribe_turtle = turtle.Turtle()
        self.scribe_turtle.ht()
        self.scribe_turtle.pu()
        (x,y) = turtle.screensize()
        self.scribe_turtle.goto(-(width/2)+10,-(height/2)+10)

        turtle.tracer(0)
        turtle.onscreenclick(self.draw_shape)
        turtle.onkeypress(self.q_key, "q")
        turtle.onkeypress(self.w_key, "w")
        turtle.onkeypress(self.e_key, "e")
        turtle.onkeypress(self.a_key, "a")
        turtle.onkeypress(self.s_key, "s")
        turtle.onkeypress(self.d_key, "d")
        turtle.onkeypress(self.clear_screen, "Escape")
        turtle.listen()

#q_key, w_key, e_key, a_key, s_key, and d_key takes those specific keys on the keyboard and initializes them to a shape object. Q for Square, W for Triangle, E for Circle, A for alterable Square, S for alterable Triangle, and D for alterable Circle.

    def clear_screen(self):
        self.big_list = []

    def q_key(self):
        self.state = self.square.name

    def w_key(self):
        self.state = self.triangle.name

    def e_key(self):
        self.state = self.circle.name

    def a_key(self):

        self.state = self.square_altered.name

    def s_key(self):
        self.state = self.triangle_altered.name

    def d_key(self):
        self.state = self.circle_altered.name


#This takes the x and y coordinates of where you click on the mouse and draws the corresponding shape
#pre: the x,y coordinate that the shape will be added to or edited
#post: the corresponding shape is added to the list or altered if possible
    def draw_shape(self, x, y):
        if self.state == self.square.name:
            if self.square.in_range(x,y, self.big_list):
                self.big_list.append([(x,y),False, self.square.name])
        if self.state == self.triangle.name:
            if self.triangle.in_range(x,y, self.big_list):
                self.big_list.append([(x,y),False, self.triangle.name])
        if self.state == self.circle.name:
            if self.circle.in_range(x,y, self.big_list):
                self.big_list.append([(x,y),False, self.circle.name])
        if self.state == self.square_altered.name:
            if self.square_altered.in_range(x,y, self.big_list):
                self.big_list.append([(x,y),True, self.square_altered.name])
        if self.state == self.triangle_altered.name:
            if self.triangle_altered.in_range(x,y, self.big_list):
                self.big_list.append([(x,y),True, self.triangle_altered.name])
        if self.state == self.circle_altered.name:
            if self.circle_altered.in_range(x,y, self.big_list):
                self.big_list.append([(x,y),True, self.circle_altered.name])

#this is what draws the current shape type
#pre: none
#post: the information is written to the bottom left side of the screen
    def scribe(self):
        self.scribe_turtle.clear()
        self.scribe_turtle.write("Click to draw a "+self.state+"!")

#this is the method that continually updates the window
#pre: method called
#post: all of the shapes are updated along with the scribe
    def updatewindow(self):
        self.scribe()
        self.square.update(self.big_list)
        self.triangle.update(self.big_list)
        self.circle.update(self.big_list)
        self.square_altered.update(self.big_list)
        self.triangle_altered.update(self.big_list)
        self.circle_altered.update(self.big_list)
        turtle.ontimer(self.updatewindow, 30)

w = Window()
w.updatewindow()
turtle.mainloop()
