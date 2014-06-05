import turtle

NUMBER_OF_POINTS = 100

class DrawingTurtle:
    def __init__(self):
        self.pt_list = []
        self.turtle = turtle.Turtle()
        self.turtle.ht()
        self.vturt = self.turtle.clone()
        self.vturt.pu()
        self.bez = BeziereCurve()
        turtle.tracer(0)
        turtle.onclick(self.click)
        turtle.listen()

    def click(self, x, y):
        print("Click")
        self.pt_list.append(Vertex(x,y))

    def draw_vertices(self):
        self.vturt.clear()
        for vertex in self.pt_list:
            self.vturt.goto((vertex[0],vertex[1]))
            if vertex.state == "active":
                self.vturt.pencolor("red")
            else:
                self.vturt.pencolor("blue")
            self.vturt.dot()

    def draw_lines(self):
        draw_list = []
        for i in range(0, NUMBER_OF_POINTS):
            ratio = i / NUMBER_OF_POINTS #changed to 100
            draw_list.append(self.bez.formula(self.pt_list, ratio))
        self.turtle.clear()
        self.turtle.pu()
        self.turtle.goto(draw_list[0])
        self.turtle.pd()
        for spot in draw_list:
            self.turtle.goto(spot)

    def run(self):
        if len(self.pt_list) > 0:
            self.draw_vertices()
            self.draw_lines()
        turtle.ontimer(self.run, 30)

class Vertex:
    def __init__(self, x, y):
        self.pt = (x,y)
        self.state = "idle"

    def __getitem__(self, index):
        return self.pt[index]

class BeziereCurve:
    def __init__(self):
        pass

    def formula(self, pt_list, ratio):
        if len(pt_list) > 1:
            lst = []
            for i in range(len(pt_list)-1):
                lst.append(self.midpoint(pt_list[i], pt_list[i+1], ratio))
            return self.formula(lst, ratio)
        else:
            return pt_list[0]

    def midpoint(self, p1, p2, ratio):
        return ( ((1-ratio)*p2[0] + ratio*p1[0]),((1-ratio)*p2[1] + ratio*p1[1]) )


if __name__ == "__main__":
    a = DrawingTurtle()
    a.run()
    turtle.mainloop()
