import math
import tkinter as tk
import messagebox
import imButtons

BG = "black"
BUTTON_W = 30
BUTTON_BW = 1
LABEL_WIDTH = 30

#This is a base frame for tkinter to be used as a root for other
#frames
class BaseFrame(tk.Tk):
    #Constructor expanded from the normal tk.Tk
    def __init__(self):
        super().__init__()
        (w, h) = self.winfo_screenwidth(), self.winfo_screenheight()
        #The functions return the screen height and width
        self.geometry('%dx%d+%d+%d' % (w/2, h, w/2, 0))
        #sets the window size and position
        #(width, height, x position, y postion)
        #Note that (0,0) is the top left of the screen
        self.focus_set() #used to make anything in this window interactive
        self.title("BaseFrame: Tkinter's best work")
        self.configure(bg=BG) #use configure to set any
                                  #options that would be given
                                  #on intialization 
        self.frames = []
        self.buttons = []
        self.labels = []
        self.entries = []

    # Post: A frame is added to the frame list
    def frame(self):
        self.frames.append(tk.Frame(self, bg=BG))
        self.buttons.append([])
        self.labels.append([])
        self.entries.append([])

    # Pre:  parent index, string, command
    # Post: appropriate button created
    def button(self, name, com, fi=-1):
        self.buttons[fi].append(tk.Button(self.frames[fi],
                                                   text=name,
                                                   command=com,
                                                   width=BUTTON_W))

    # Pre:  parent index, string
    # Post: appropriate label created
    def label(self, name, fi=-1):
        self.labels[fi].append(tk.Label(self.frames[fi],
                                        width=LABEL_WIDTH,
                                        text=name))

    # Pre:  parent index
    # Post: appropriate entry box created
    def entry(self, fi=-1):
        self.entries[fi].append(tk.Entry(self.frames[fi],
                                         width=LABEL_WIDTH))






    #     self.add_canvas()
    # def add_canvas(self):
    #     self.canvas = DrawingCavnas(self)
    #     self.canvas.pack(side="left",fill="both", expand=True)
MILISECONDS = 30
#This class will serve as a drawing plane for turtleesque simulations
class DrawingCavnas(tk.Canvas):
    def __init__(self, p):
        super().__init__(p)
        self.configure(cursor="pencil")
        self.setup_bindings()
        self.info = None
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
        pass

    def mainloop(self):
        self.processes()
        self.after(MILISECONDS, self.mainloop)

if __name__ == "__main__":
    a = BaseFrame()
    tk.mainloop()
