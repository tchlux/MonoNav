import math
import tkinter as tk
import tkinter.messagebox as popup

BUTTON_WIDTH = 8
BW = 4 #borderwidth
LABEL_WIDTH = 11
DIGITS = 5
RATIO = 50
CLICK_RANGE = 10
RADIUS = CLICK_RANGE / 2
ACTIVE = "red"
IDLE = "blue"
MILISECONDS = 30
SNAP_DIST = 10

VARIABLES = {"BUTTON_WIDTH":8, "BW":4, "LABEL_WIDTH":11, "DIGITS":5,
             "RATIO":50, "CLICK_RANGE":10, "RADIUS":5, "ACTIVE":"red",
             "IDLE":"blue", "MILISECONDS":30, "SNAP_DIST":20}

def write_to_file(vertices, name):
    pass

#This is a base frame for tkinter to be used as a root for other
#frames
class Builder(tk.Tk):
    #Constructor expanded from the normal tk.Tk
    def __init__(self):
        super().__init__()
        self.d = VARIABLES
        (w, h) = self.winfo_screenwidth(), self.winfo_screenheight()
        #The functions return the screen height and width
        self.w = w/2 - BUTTON_WIDTH*8
        self.h = h/2
        self.geometry('%dx%d+%d+%d' % (self.w, self.h, self.w, 0))
        #sets the window size and position
        #(width, height, x position, y postion)
        #Note that (0,0) is the top left of the screen
        self.focus_set() #used to make anything in this window interactive
        self.title("BaseFrame: Tkinter's best work")
        self.configure(bg="grey") #use configure to set any
                                  #options that would be given
                                  #on intialization 
        self.canvas = MapCavnas(self)
        self.canvas.pack(side="left",fill="both", expand=True)
        self.build_button_panel()
        self.panel.pack(side="right")
        self.panel.focus_set()

    def build_button_panel(self):
        self.buttons = []
        self.panel = tk.Frame(self, bg="black")
        self.buttons.append(tk.Button(self.panel, text="Snap in",
                                      command=self.snap_in,
                                      width=BUTTON_WIDTH-1,
                                      borderwidth=BW, bg="dark grey"))

        addB = lambda name, com: self.buttons.append(tk.Button(self.panel,
                                                               text=name,
                                                               command=com,
                                                               width=BUTTON_WIDTH))
        addE = lambda : self.buttons.append(tk.Entry(self.panel, width=LABEL_WIDTH))
        addL = lambda name: self.buttons.append(tk.Label(self.panel,
                                                         width=LABEL_WIDTH,
                                                         text=name))
        addB("Save", self.save)
        addB("Exit", self.exit)
        addB("Reset", self.reset)
        addB("Adjust", self.adjust)
        addB("New Shape", self.new_shape)
        addL("")
        addL("Idle color")
        addE()
        addL("Active color")
        addE()
        addL("Diameter")
        addE()
        addL("Snap distance")
        addE()

        self.buttons[-7].insert(0,IDLE)
        self.buttons[-5].insert(0,ACTIVE)
        self.buttons[-3].insert(0,CLICK_RANGE)
        self.buttons[-1].insert(0,SNAP_DIST)
        for button in self.buttons:
            button.pack()

    def new_shape(self):
        self.canvas.shapes.append([])
        self.canvas.shape_index = -1

    def adjust(self):
        self.d["IDLE"] = self.buttons[-7].get()
        self.d["ACTIVE"] = self.buttons[-5].get()
        self.d["CLICK_RANGE"] = int(self.buttons[-3].get())
        self.d["RADIUS"] = int(self.buttons[-3].get())/2
        self.d["SNAP_DIST"] = int(self.buttons[-1].get())

    def snap_in(self):
        if self.buttons[0]['bg'] == "light grey":
            self.buttons[0]['bg'] = "dark grey"
            self.canvas.snapin = True
        else:
            self.buttons[0]["bg"] = "light grey"
            self.canvas.snapin = False

    def save(self):
        name = self.buttons[-1].get()
        if name == "":
            popup.showwarning(message="The beautiful map needs a name!")
        elif " " in name:
            popup.showwarning(message="No spaces!")
        elif len(self.canvas.vertices) < 3:
            popup.showwarning(message="You need more vertices than that!")
        else:
            write_to_file(self.create_verts(), name)
            self.exit()

    def create_verts(self):
        verts = []
        for vert in self.canvas.vertices:
            (x,y) = (vert[0], vert[1])
            new = ((x-self.w/2)/RATIO,-(y-self.h/2)/RATIO)
            verts.append(new)
        return verts

    def reset(self):
        self.canvas.clear_canvas()
        self.d = VARIABLES
        self.buttons[-7].delete(0,10)
        self.buttons[-5].delete(0,10)
        self.buttons[-3].delete(0,10)
        self.buttons[-1].delete(0,10)

        self.buttons[-7].insert(0,IDLE)
        self.buttons[-5].insert(0,ACTIVE)
        self.buttons[-3].insert(0,CLICK_RANGE)
        self.buttons[-1].insert(0,SNAP_DIST)
        self.adjust()


    def exit(self):
        self.destroy()

#This class will serve as a drawing plane for simulations
class MapCavnas(tk.Canvas):
    def __init__(self, p):
        super().__init__(p)
        self.configure(cursor="pencil")
        self.setup_bindings()
        self.shapes = [[]]
        self.shape_index = 0
        self.lines = []
        self.snapin = True
        self.mainloop()

    def left_click(self, event):
        for vertex in self.shapes[self.shape_index]:
            if vertex.click_check((event.x,event.y)):
                return None
        self.shapes[self.shape_index].append(Vertex((event.x,event.y),self))

    def right_click(self, event):
        for shape in self.shapes:
            for vertex in shape:
                if vertex.click_check((event.x,event.y)):
                    vertex.kill()
                    shape.remove(vertex)


    def clear_canvas(self, event=None):
        self.delete('all')
        self.shapes = [[]]
        self.shape_index = 0

    def setup_bindings(self):
        self.bind("<Key-c>", self.clear_canvas)
        self.bind("<Button-1>", self.left_click)
        self.bind("<Button-3>", self.right_click)
        self.focus_set()

    def null(self, event):
        pass

    def draw(self):
        for line in self.lines: self.delete(line)
        for shape in self.shapes:
            for i in range(len(shape)):
                p1 = shape[i-1]
                p2 = shape[i]
                self.lines.append(self.create_line(p1[0],p1[1],p2[0],p2[1]))

    def processes(self):
        for shape in self.shapes:
            for vertex in shape:
                vertex.update()
        self.draw()

    def mainloop(self):
        self.processes()
        self.after(MILISECONDS, self.mainloop)

    def snap_in(self, given):
        (x,y) = (given[0], given[1])
        for shape in self.shapes:
            for vert in shape:
                if vert != given:
                    if abs(vert[0]-given[0]) < self.master.d["SNAP_DIST"]:
                        x = vert[0]
                    if abs(vert[1]-given[1]) < self.master.d["SNAP_DIST"]:
                        y = vert[1]
        return (x,y)

class Vertex:
    def __init__(self,loc, parent):
        self.loc = loc
        self.canvas = parent
        self.picture = None
        self.active = False
        if self.canvas.snapin:
            self.loc = self.canvas.snap_in(self)

    def click_check(self, loc):
        if distance(self.loc, loc) < self.canvas.master.d['CLICK_RANGE']:
            self.active = True
            self.canvas.bind("<Motion>", self.move)
            self.canvas.bind("<ButtonRelease-1>", self.place)
            return True
        return False

    def place(self, event):
        self.loc = (event.x, event.y)
        if self.canvas.snapin:
            self.loc = self.canvas.snap_in(self)
        self.active = False
        self.canvas.bind("<Motion>", self.canvas.null)
        self.canvas.bind("<ButtonRelease-1>", self.canvas.null)

    def move(self, event):
        self.loc = (event.x, event.y)

    def __getitem__(self,index):
        return self.loc[index]

    def draw(self):
        (x,y) = self.loc
        radius = self.canvas.master.d['RADIUS']
        active = self.canvas.master.d['ACTIVE']
        idle = self.canvas.master.d['IDLE']
        if self.active:
            self.picture = self.canvas.create_oval(x-radius,y-radius,x+radius,y+radius,fill=active)
        else:
            self.picture = self.canvas.create_oval(x-radius,y-radius,x+radius,y+radius,fill=idle)

    def update(self):
        self.canvas.delete(self.picture)
        self.draw()

    def kill(self):
        self.canvas.delete(self.picture)

def distance(p1, p2):
    return ((p1[0]-p2[0])**2+(p1[1]-p2[1])**2)**.5


if __name__ == "__main__":
    a = Builder()
    tk.mainloop()
