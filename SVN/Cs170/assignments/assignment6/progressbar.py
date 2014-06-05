
class Status:
    def __init__(self, parent=tk.Tk()):
        self.percent_complete = 0
        self.root = parent
        self.root.title("Status of your face!")
        self.root.configure(bg="black")
        self.root.geometry("%dx%d+0+0" % (250, 80))
        self.label = tk.Label(master=self.root, text="Working on it, just wait a minute.", bg="black", fg="white")
        self.label.grid(column=0,row=0, sticky="n")
        self.loadingbar = tk.Canvas(master=self.root)
        self.loadingbar.configure(height=20, width=200, bg="black")
        self.loadingbar.grid(column=0,row=1)

    def five_percent(self):
        self.percent_complete += .05
        self.create_box(self.loadingbar, int(self.percent_complete*200))

    def create_box(self, canvas, top_left):
        canvas.create_line(top_left, 0, top_left-10, 0, fill="white")
        canvas.create_line(top_left-10, 0, top_left-10, 20, fill="white")
        canvas.create_line(top_left, 0, top_left, 20, fill="white")
        canvas.create_line(top_left, 20, top_left-10, 20, fill="white")

    def terminate(self):
        self.root.destroy()
