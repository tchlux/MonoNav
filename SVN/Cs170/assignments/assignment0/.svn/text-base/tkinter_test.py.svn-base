import tkinter as tk

class Application(tk.Frame):
    def __init__(self):
        self.root = tk.Tk()
        tk.Frame.__init__(self)
        self.pack()
        self.createWidgets()

    def createWidgets(self):
        self.no = tk.Entry(self)
        self.no["width"] = 60

        self.hi_there = tk.Button(self)
        self.hi_there["text"] = "Hello World"
        self.hi_there["command"] = self.say_hi

        self.enter = tk.Button(self)
        self.enter["text"] = "Press me"
        self.enter["command"] = self.enter_pressed

        self.no.pack(side="right")
        self.hi_there.pack(side="top")
        self.enter.pack(side="top")

        self.QUIT = tk.Button(self, text="QUIT", fg="red", command=self.root.destroy)
        self.QUIT.pack(side="bottom")

    def say_hi(self):
        print("hi there, everyone!")

    def enter_pressed(self):
        print(self.no.get().strip())
        length = len(self.no.get())
        self.no.delete(0,length)

app = Application()
app.mainloop()
