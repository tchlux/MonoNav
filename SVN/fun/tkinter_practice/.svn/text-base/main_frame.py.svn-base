import math
import tkinter as tk
from util import messagebox

#This is a base frame for tkinter to be used as a root for other
#frames
class BaseFrame(tk.Tk):
    #Constructor expanded from the normal tk.Tk
    def __init__(self):
        super().__init__()
        (w, h) = self.winfo_screenwidth(), self.winfo_screenheight()
        #The functions return the screen height and width
        self.geometry('%dx%d+%d+%d' % (w/2, h/2, w/2, 0))
        #sets the window size and position
        #(width, height, x position, y postion)
        #Note that (0,0) is the top left of the screen
        self.focus_set() #used to make anything in this window interactive
        self.title("BaseFrame: Tkinter's best work")
        self.configure(bg="grey") #use configure to set any
                                  #options that would be given
                                  #on intialization 
        self.add_canvas()

    def add_canvas(self):
        self.canvas = DrawingCavnas(self)
        self.canvas.pack(side="left",fill="both", expand=True)

MILISECONDS = 30
#This class will serve as a drawing plane for turtleesque simulations
class DrawingCavnas(tk.Canvas):
    def __init__(self, p):
        super().__init__(p)
        self.configure(cursor="pencil")
        self.setup_bindings()
        self.info = None
        self.turtle = Turtle(self)
        self.mainloop()

    def left_click(self, event):
        print("Left click")
        print("     at (%d, %d)"%(event.x,event.y))

    def right_click(self, event):
        print("Right click")
        print("     at (%d, %d)"%(event.x,event.y))

    def mouse_move(self, event):
        pass

    def clear_canvas(self, event):
        self.delete('all')

    def setup_bindings(self):
        self.bind("<Key-c>", self.clear_canvas)
        self.bind("<Button-1>", self.left_click)
        self.bind("<Button-3>", self.right_click)
        self.bind("<Motion>", self.mouse_move)
        self.focus_set()

    def processes(self):
        self.turtle.update()

    def mainloop(self):
        self.processes()
        self.after(MILISECONDS, self.mainloop)

MOVE = 4.0
TURN = 4.0
PIC_DIST = 12.0
PIC_ANGLE = 155.0
class Turtle:
    def __init__(self, canvas):
        self.canvas = canvas
        self.heading = 0.0
        self.location = (100.0, 100.0)
        self.picture = None
        self.move_amount = 0
        self.turn_amount = 0
        self.setup_bindings()

    def setup_bindings(self):
        self.canvas.bind("<KeyPress-a>", self.set_left_turn)
        self.canvas.bind("<KeyPress-d>", self.set_right_turn)
        self.canvas.bind("<KeyPress-w>", self.set_forward)
        self.canvas.bind("<KeyPress-s>", self.set_backward)
        self.canvas.bind("<KeyRelease-a>", self.stop_turn)
        self.canvas.bind("<KeyRelease-d>", self.stop_turn)
        self.canvas.bind("<KeyRelease-w>", self.stop_move)
        self.canvas.bind("<KeyRelease-s>", self.stop_move)

    def set_right_turn(self,event):
        self.turn_amount = TURN
    def set_left_turn(self,event):
        self.turn_amount = -TURN
    def set_forward(self,event):
        self.move_amount = MOVE
    def set_backward(self,event):
        self.move_amount = -MOVE
    def stop_turn(self,event):
        self.turn_amount = 0
    def stop_move(self,event):
        self.move_amount = 0
    def left(self, degrees):
        self.heading += degrees
    def right(self, degrees):
        self.heading -= degrees
    def backward(self, distance):
        self.forward(-distance)
    def forward(self, distance):
        (x,y) = self.pos(distance, self.heading)
        self.goto(self.location[0]+x, self.location[1]+y)
    def goto(self, x, y):
        self.location = (x,y)
    def pos(self, dist, heading):
        y = dist * (math.sin(math.radians(heading)))
        x = dist * (math.cos(math.radians(heading)))
        return (x, y)

    def draw_self(self):
        (x,y) = self.location
        p = [self.location,
             self.pos(PIC_DIST,self.heading+PIC_ANGLE),self.pos(PIC_DIST,self.heading-PIC_ANGLE)]
        self.picture = self.canvas.create_polygon(x,y,x+p[1][0],y+p[1][1],x+p[2][0],y+p[2][1],fill="black")

    def move(self):
        self.forward(self.move_amount)
        self.left(self.turn_amount)

    def update(self):
        self.canvas.delete(self.picture)
        self.move()
        self.draw_self()


BUTTON_ROWS = 30
#This is a class that makes example of how to create a scrollable
#canvas with buttons on it
class ScrollCanvas(tk.Canvas):
    #Constructor, sets scrolling ability
    def __init__(self, root):
        super().__init__(root)
        self.yscrollbar = tk.Scrollbar(root, orient="vertical", command=self.yview)
        self.configure(yscrollcommand=self.yscrollbar.set)
        #configuring necessary bindings for scrolling
        self.configure(scrollregion=(0,0,0,0))
        #scrollable area (w, n, e, s)
        self.yscrollbar.pack(side="right",fill="y")
        self.xscrollbar = tk.Scrollbar(root, orient="horizontal", command=self.xview)
        self.configure(xscrollcommand=self.xscrollbar.set)
        #configuring necessarx bindings for scrolling
        self.configure(scrollregion=(0,0,0,0))
        #scrollable area (w, n, e, s)
        self.xscrollbar.pack(side="bottom",fill="x")
        self.pack(side="left",fill="both",expand=True)
        self.prepare_buttons()

    #Prepares the buttons to be added to the canvas
    def prepare_buttons(self):
        self.frame = tk.Frame(self)
        self.frame.grid(sticky="nsew")
        self.create_window((0,0),window=self.frame, anchor="nw")
        #This step is vital for making the screen scrollable
        #(location, what is visible through it, and anchor)
        self.counter = 0

    #Arbitrary function to be called on a button press
    def button_command(self, special=""):
        print("Oh no! A button was pressed!")

    #This adds a button to the window giving each one an unique name
    def add_button(self):
        txt = "Button " + str(self.counter)
        r = self.counter % BUTTON_ROWS
        c = self.counter // BUTTON_ROWS
        b = tk.Button(self.frame,text=txt,command=self.button_command).grid(row=r,column=c)
        self.counter += 1

    #This uses an average sized button to adjust the scrollable frame,
    #still looking for a better way to do this.  Preferrable one where
    #you can simply query the length in pixels of the contents
    def refresh_scroll_area(self):
        (x,y) = self.frame.grid_size()
        width_factor = 100
        height_factor = 30
        self.configure(scrollregion=(0,0,x*width_factor,y*height_factor))

if __name__ == "__main__":
    a = BaseFrame()
    tk.mainloop()

#Code from the drawing canvas
    # def start_line(self, event):
    #     self.info = (event.x, event.y)

    # def stop_line(self, event):
    #     self.info = None

    # def draw_line(self, event):
    #     if type(self.info) == tuple:
    #         self.create_line(self.info[0],self.info[1],event.x,event.y)
    #         self.info = (event.x, event.y)
