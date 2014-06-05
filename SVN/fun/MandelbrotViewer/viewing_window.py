#!usr/bin/python
import ttk #for message boxes
import tkinter as tk #for viewing window
import messagebox #for message boxes
import colorchooser #for color chooser
import mandelbrot #to run mandelbrot
import os #to check if a path exists

NUMBER_OF_SEGMENTS = 20
CANVAS_WH = 300
DIM = 100
DEPTH = 255
A = -.5
B = 0
SIZE = 2
INIT_R = [0, 110, 255]
INIT_G = [5, 170, 15]
INIT_B = [30, 250, 50]

# INIT_VALUES_LIST = [100, 255, -.5, 0, 2, 0, 110, 255, 5, 170, 15, 30,
#                     250, 50]
#[dimensions, calc_depth, a, b, size, rl, rm, rh, gl, gm, gh, bl, bm, bh]
COMPENSATION = 15
IMAGE_FILENAME = "Mandelbrot0.ppm"


class ViewingWindow:
    #Method:Constructor for the coolest application ever
    #Pre:   The Viewing window is initialized if this is the __main__
    #Post:  The application runs
    def __init__(self):
        #configure necesities for mandelbrot
        self.dim = DIM
        self.depth = DEPTH
        self.a = A
        self.b = B
        self.size = SIZE
        self.red = INIT_R
        self.green = INIT_G
        self.blue = INIT_G

        self.man = mandelbrot.Mandelbrot(self)

        self.configure_root()
        self.configure_mainframe()
        self.configure_zoombuttonframe()
        self.configure_statbar()
        self.configure_colorpanel()
        self.configure_interactivepanel()
        self.configure_controlpanal()

        #begin the vicious cycle
        self.run_mandelbrot()
#        self.configure_saved_points_list()
        self.root.mainloop()


        # ========================================
        #          Configuration methods
        # ========================================

    # Pre:  
    # Post: self.root is configured appropriately
    def configure_root(self):
        self.root = tk.Tk()
        self.root.title("Mandelbrot Image Viewer")
        self.root.configure(bg="black")
        w, h = self.root.winfo_screenwidth(), self.root.winfo_screenheight()
        self.root.geometry("%dx%d+%d+%d" % (w//2, h//2, w//4, h//4))
        self.root.bind("<Return>", self.update_picture)
        self.root.bind("<Up>", self.up)
        self.root.bind("<Down>", self.down)
        self.root.bind("<Left>", self.left)
        self.root.bind("<Right>", self.right)
        self.root.bind("<o>", self.zoomout)
        self.root.bind("<i>", self.zoomin)
        self.inform = ""#"Press enter to update the picture"
        self.root.informme = tk.Label(text=self.inform, bg="black", fg="white")
        self.root.informme.grid(column=0, row=2)
        self.root.informme["text"] = ""

    # Pre:  
    # Post: The status bar is initialized and configured
    def configure_statbar(self):
        self.statbar = ttk.Progressbar(self.root, orient="horizontal", length=200, mode="determinate")
        self.statbar["value"] = 0
        self.statbar["maximum"] = self.dim
        self.statbar.grid(row=1,column=0)

    #Method:This is what builds the picture and the navigation buttons
    #Pre:   called
    #Post:  mainframe is put on the screen
    def configure_mainframe(self):
        self.mainframe = SubFrame(master=self.root, bg="black")
        self.mainframe.columnconfigure(0, weight=1)
        self.mainframe.columnconfigure(1, weight=2)
        self.mainframe.columnconfigure(2, weight=1)
#        self.mainframe.add_button("L", 0, 1, self.lileft, 5, stick="e")
        self.mainframe.add_button("Left", 0, 1, self.left, 5)
#        self.mainframe.add_button("R", 2, 1, self.liright, 5)
        self.mainframe.add_button("Right", 2, 1, self.right, 5)
        self.mainframe.add_button("Up", 1, 0, self.up, 40, 7)
        self.mainframe.add_button("Down", 1, 2, self.down, 40, 7)
        self.mainframe.grid(column=0, row=0)

        self.picture = tk.Canvas(master=self.mainframe, width=CANVAS_WH,
                                 height=CANVAS_WH, bg="black")
        self.picture.grid(row=1, column=1)
        self.photoImage = None

    #Method:This is the subframe that controls zooming
    #Pre:   The method is called
    #Post:  The zoom buttons (in/out) are grid()ed
    def configure_zoombuttonframe(self):
        self.zoombuttonframe = SubFrame(master=self.root, bg="black")
        self.zoombuttonframe.add_button("Zoom in  ", 0, 0, self.zoomin, 20, 8)
        self.zoombuttonframe.add_button("Zoom out", 0, 1, self.zoomout, 20, 8)
        self.zoombuttonframe.grid(column=1, row=0, sticky="nw")

    #Method:This creates the control panel for changing the colors
    #Pre:   called
    #Post:  The from/to buttons are .grid()ed
    def configure_colorpanel(self):
        self.colorframe = SubFrame(master=self.root, bg="black")
        self.colorframe.add_label("\nCOLOR CONTROL!", 0, 0, cspan=2)
        self.colorframe.add_button("f", 0, 1, self.adjust_color_from, 5, 5, 1)
        self.colorframe.add_button("b", 0, 2, self.adjust_color_between, 5, 5, 2)
        self.colorframe.add_button("t", 1, 1, self.adjust_color_to, 5, 5, 1)
        self.colorframe.buttonf.configure(text="From", bg="#00051e")
        self.colorframe.buttonb.configure(text="Between", bg="#6eaafa")
        self.colorframe.buttont.configure(text="  To  ", bg="#ff0f32")
        self.colorframe.grid(column=1, row=0, sticky="ne")

    #Method:This is called frequently to offer direct movement
    #Pre:   called
    #Post:  the interactivepanelframe is removed and then recreated (inefficient but effective)
    def configure_interactivepanel(self):
        self.interactivepanelframe = SubFrame(master=self.root, bg="black")
        self.interactivepanelframe.add_label("Pixel Count: ", 0, 0)
        self.interactivepanelframe.add_label("Max depth  : ", 0, 1)
        self.interactivepanelframe.add_label("Move to a  : ", 0, 2)
        self.interactivepanelframe.add_label("Move to b  : ", 0, 3)
        self.interactivepanelframe.add_label("Curr. Size : ", 0, 4)
        self.isize = tk.StringVar(value=str(self.dim))
        self.depthtk = tk.StringVar(value=str(self.depth))
        self.complexa = tk.StringVar(value=str(self.a))
        self.complexb = tk.StringVar(value=str(self.b))
        self.size_e = tk.StringVar(value=str(self.size))
        self.isize_entry = tk.Entry(master=self.interactivepanelframe, textvariable=self.isize, fg="white", bg="black")
        self.depthtk_entry = tk.Entry(master=self.interactivepanelframe, textvariable=self.depthtk, fg="white", bg="black")
        self.complexa_entry = tk.Entry(master=self.interactivepanelframe, textvariable=self.complexa, fg="white", bg="black")
        self.complexb_entry = tk.Entry(master=self.interactivepanelframe, textvariable=self.complexb, fg="white", bg="black")
        self.size_e_entry = tk.Entry(master=self.interactivepanelframe, textvariable=self.size_e, fg="white", bg="black")

        self.isize_entry.grid(row=0, column=1)
        self.depthtk_entry.grid(row=1, column=1)
        self.complexa_entry.grid(row=2, column=1)
        self.complexb_entry.grid(row=3, column=1)
        self.size_e_entry.grid(row=4, column=1)
        self.interactivepanelframe.add_button("Adjust picture", 0, 5, self.adjust_image, 5, 5, 2)
        self.interactivepanelframe.grid(column=1, row=0, sticky="e")

    # Pre:  
    # Post: controlpanel is created, currently only containts one button
    def configure_controlpanal(self):
        self.controlpanelframe = SubFrame(master=self.root, bg="black")
        # self.controlpanelframe.add_label("Complex a: "+str(self.a), 0, 0)
        # self.controlpanelframe.add_label("Complex b: "+str(self.b), 0, 1)
        # self.controlpanelframe.add_label("Size: "+str(self.size), 0, 2)
        self.controlpanelframe.add_button("Save These\n Coordiantes.", 0, 0, self.print_coord, 3, 1)
        self.controlpanelframe.grid(column=1, row=0, sticky="s")


        # ========================================
        #          Color chooser methods
        # ========================================

    #Method:This method changes the self attributes for color lows in the mandelbrot
    #Pre:   from button is pressed and ok is pressed on colorchooser
    #Post:  the button changes colors correspondingly with the image
    def adjust_color_from(self):
        try:
            ((self.red[0], self.green[0], self.blue[0]),string) = colorchooser.askcolor((self.red[0], self.green[0], self.blue[0]))
            self.colorframe.buttonf.configure(bg=string)
            self.run_mandelbrot()
        except TypeError:
            print("You're adopted.")


    #Method:This method changes the self attributes for color mids in the mandelbrot
    #Pre:   to button is pressed and ok is pressed on colorchooser
    #Post:  the button changes colors correspondingly with the image
    def adjust_color_between(self):
        try:
            ((self.red[1], self.green[1], self.blue[1]),string) = colorchooser.askcolor((self.red[1], self.green[1], self.blue[1]))
            self.colorframe.buttonb.configure(bg=string)
            self.run_mandelbrot()
        except TypeError:
            print("Yeah, that was kinda gross...")

    #Method:This method changes the self attributes for color highs in the mandelbrot
    #Pre:   to button is pressed and ok is pressed on colorchooser
    #Post:  the button changes colors correspondingly with the image
    def adjust_color_to(self):
        try:
            ((self.red[2], self.green[2], self.blue[2]),string) = colorchooser.askcolor((self.red[2], self.green[2], self.blue[2]))
            self.colorframe.buttont.configure(bg=string)
            self.run_mandelbrot()
        except TypeError:
            print("What?? I liked that color!")

        # ========================================
        #          Runtime update methods
        # ========================================

    # Pre:  
    # Post: The interactive panel is updated with the newest
    #       information regarding the mandelbrot set
    def update_interactivepanel(self):
        self.isize_entry.delete(0, tk.END)
        self.depthtk_entry.delete(0, tk.END)
        self.complexa_entry.delete(0, tk.END)
        self.complexb_entry.delete(0, tk.END)
        self.size_e_entry.delete(0, tk.END)

        self.isize_entry.insert(0,self.dim)
        self.depthtk_entry.insert(0,self.depth)
        self.complexa_entry.insert(0,self.a)
        self.complexb_entry.insert(0,self.b)
        self.size_e_entry.insert(0,self.size)

    #Method:This method draws the picture to the canvas provided
    #Pre:   called
    #Post:  the mandelbrot image is loaded on the canvas
    def update_picture(self, null):
        del(self.photoImage)
        self.photoImage = tk.PhotoImage(file=IMAGE_FILENAME)
        loc = (CANVAS_WH/2)#+ (self.dim/2)
        self.picture.create_image(loc, loc, image=self.photoImage)

        # ========================================
        #           Mandelbrot update
        # ========================================

    #Method:This methd is used to call mandelbrot and make images
    #Pre:   called
    #Post:  mandelbrot is made based on self attributes stored earlier on and all frames are updated
    def run_mandelbrot(self):
        self.man.set(self.a, self.b, self.size, self.dim,
                     self.red, self.green, self.blue, self.depth)
        # self.pthread = threading.Thread(target=self.man.run)
        # self.pthread.start()
        self.statbar.grid()
        self.statbar["maximum"] = self.dim
        self.update_interactivepanel()
        self.man.run()
        self.update_picture(None)

        # ========================================
        #         Button-binded functions
        # ========================================

    #Method:This method is used when the adjust image button is pressed
    #Pre:   Adjust image button pressed
    #Post:  The mandelbrot is remade accordingly
    def adjust_image(self):
        self.dim = int(self.isize.get())
        self.depth = int(self.depthtk.get())
        self.a = float(self.complexa.get())
        self.b = float(self.complexb.get())
        self.size = float(self.size_e.get())
        self.isize.set(value=self.dim)
        self.depthtk.set(value=self.depth)
        self.complexa.set(value=self.a)
        self.complexb.set(value=self.b)
        self.size_e.set(value=self.size)
        self.run_mandelbrot()

    #Method:Zooms in by factor of 3
    #Pre:   called
    #Post:  new mandelbrot, updated window
    def zoomin(self, event=None):
        self.size /= 3
        self.run_mandelbrot()

    #Method:Zooms out by factor of 3
    #Pre:   called
    #Post:  new mandelbrot, updated window
    def zoomout(self, event=None):
        self.size *= 3
        self.run_mandelbrot()

    #Method:moves image left
    #Pre:   called
    #Post:  new mandelbrot, updated window
    def left(self, event=None):
        move = self.size / 5
        self.a -= move
        self.run_mandelbrot()

    #Method:moves image right
    #Pre:   called
    #Post:  new mandelbrot, updated window
    def right(self, event=None):
        move = self.size / 5
        self.a += move
        self.run_mandelbrot()

    #Method:moves image up
    #Pre:   called
    #Post:  new mandelbrot, updated window
    def up(self, event=None):
        move = self.size / 5
        self.b -= move
        self.run_mandelbrot()

    #Method:moves image down
    #Pre:   called
    #Post:  new mandelbrot, updated window
    def down(self, event=None):
        move = self.size / 5
        self.b += move
        self.run_mandelbrot()

    #Method:Prints the current coordinates to a datafile
    #Pre:   called
    #Post:  messagebox saying operation complete
    def print_coord(self):
        current_file = ''
        if os.path.exists('data.txt'):
            with open('data.txt', 'r') as f:
                current_file = f.read()
                f.close
        with open('data.txt', 'w') as f:
            current_file += "\n________DATA_________\n#A = "+str(self.a)+"\n#B = "+str(self.b)+"\n#SIZE = "+str(self.size)+"\n"
            f.write(current_file)
            f.close
        messagebox.showwarning(title="All done :)", message="Your current location was saved to data.txt!")



        # ========================================
        #             Usage class
        # ========================================


#This class is used to create each viewing window for the users
class SubFrame(tk.Frame):
    #This method adds a child button to the self
    #Pre:    The name of the button, grid x,y, and the associated command are given
    #Post:   The button is drawn to the frame
    def add_button(self, name="Button", gridx=0, gridy=0, com=None, px=50, py=40, cspan=1):
        a = tk.Button(master=self, text=name, command=com, padx=px, pady=py, bg="black", fg="white", activebackground="dark grey")
        a.grid(column=gridx, row=gridy, columnspan=cspan)
        setattr(self, "button"+name, a)

    #This method adds a child label object to the self
    #Pre:    The name of the label, and the grid x,y are given
    #Post:   The label is drawn to the frame
    def add_label(self, name, gridx, gridy, cspan=1, px=1, py=3):
        a = tk.Label(master=self, text=name, padx=px, pady=py, fg="white", bg="black")
        a.grid(column=gridx, row=gridy, columnspan=cspan)
        setattr(self, "label", a)


if __name__ == "__main__":
    v = ViewingWindow()



#     def command(self):
#         print("command")

#     def configure_saved_points_list(self):

#         self.saved_points_frame = SubFrame(master=self.root)

#         current_file = []
#         if os.path.exists('data.txt'):
#             with open('data.txt', 'r') as f:
#                 current_file = f.readlines()
#                 f.close
#         number_of_points = len(current_file) // 5

#         for i in range(number_of_points):
#             start_ind = i*5 
#             value = (current_file[start_ind+2], current_file[start_ind+3], current_file[start_ind+4])
#             att_name = "Point "+str(i)
#             setattr(self.saved_points_frame, att_name, value)
#             self.saved_points_frame.add_button(att_name, 0, i, self.command, 5, 5)
            
#         #Create a scrollable subframe (canvas) for the questions
#         self.canv = tk.Canvas(self.saved_points_frame, width=200, height=300, scrollregion=(0,0,200,50*number_of_points), bg="black")
#         self.scrollY = tk.Scrollbar(self.saved_points_frame, orient=tk.VERTICAL, command=self.canv.yview)
#         self.canv.configure(yscrollcommand=self.scrollY.set)
#         self.canv.pack(side=tk.LEFT)
#         self.scrollY.pack(side=tk.RIGHT, fill=tk.Y)
# #        canv.create_window(window=self.saved_points_frame)
#         self.saved_points_frame.grid(row=0, column=3)

        # self.picture.photo = []
        # for i in range(NUMBER_OF_SEGMENTS):
        #     string = "Mandelbrot"+str(i)+".ppm"
        #     self.picture.photo.append(tk.PhotoImage(file=string))
        #     y = (CANVAS_WH/2)+ (self.dim/2)*((i-NUMBER_OF_SEGMENTS/2)/NUMBER_OF_SEGMENTS/2)*4
        #     self.picture.create_image(CANVAS_WH//2, y, image=self.picture.photo[i])
