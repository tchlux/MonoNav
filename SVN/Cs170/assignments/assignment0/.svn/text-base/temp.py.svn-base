import random
import tkinter as tk
import pickle
import os

class Dvd:

    def __init__(self, title=None, release_year=None, director=None, cost=None, who=None):
        self.title = title
        self.release_year = release_year
        self.director = director
        self.cost = cost
        self.who = who

class DvdCollection:

    def __init__(self):

        self.dvd_collection = self.return_a_file('dvd_collection')
        self.main_menu_list = [['Dvds',str(len(self.dvd_collection))]]
        self.button_list = [["Add Dvd",""],["Remove Dvd",""], ["Print Collection",""],["Count the monay",""],["Change who has a dvd", ""]]
        self.mainwindow = TkFrame(self.main_menu_list, "Main Menu  (what do ya want??)", True)
        self.mainwindow.mainloop()
        self.dvd = TkFrame(self.button_list, "Editting (lets go!)", buttons=True, self.dvd_collection)
        self.dvd.mainloop()
        self.save_a_collection(self.dvd.collection, "dvd_collection")

    def return_a_file(self, a_file):
        if os.path.exists(a_file +'.txt'):
            with open(a_file +'.txt', 'rb') as f:
                a_file = pickle.load(f)
                f.close()
        else:
            a_file = []
        return a_file

    def save_a_collection(self, a_collection, a_file):
        edit_state = ""
        yes_no = input('Do you want to save over the old collection in '+a_file+'.txt? ')
        while yes_no != "yes" and yes_no != "no":
            print('')
            yes_no = input('yes or no: ')
        if yes_no == "yes":
            with open(a_file+'.txt', 'wb') as f:
                pickle.dump(a_collection, f)
                f.close()
            edit_state = ("Collection successfully edited in " + a_file+".txt")
        else:
            edit_state = "Editing cancelled"
        print(edit_state)
        print('Done')





class TkFrame(tk.Frame):
    def __init__(self, lst, txt, edit=False, entry=False, buttons=False, dvds=[]):
        self.switch = False
        self.root = tk.Tk()
        self.collection = lst
        tk.LabelFrame.__init__(self, bg="black", fg="white", padx=100, pady=100, text=txt)
        col = len(lst[0])
        rows = len(lst)+1
        self.grid(column=col,row=rows)
        self.row = 1
        for item in lst:
            self.createWindow(item, rows, edit, entry, buttons)
            self.row += 1

    def createWindow(self, item, rows, edit, entry, buttons):
        if buttons == False:
            temp = tk.Label(self, fg="cyan", bg="black")
        else:
            temp = tk.Button(self, fg="cyan", bg="black")
            if self.row == 1:
                temp["command"] = self.add_dvd
            elif self.row == 2:
                temp["command"] = self.remove_dvd
            elif self.row == 3:
                temp["command"] = self.print_collection
            elif self.row == 4:
                temp["command"] = self.total_cost
            elif self.row == 5:
                temp["command"] = self.change_who
            else:
                temp["command"] = self.click

        temp["text"] = item[0]
        temp.grid(column=1, row=self.row)
        setattr(self, "item"+str(self.row)+"1", temp)
        if entry == False:
            temp = tk.Label(self, fg="cyan", bg="black")
            temp["text"] = item[1]
            if edit == True:
                Edit = tk.Button(self, text="Edit", fg="yellow", bg="black", command=self.edit)
                Edit.grid(column=2, row=rows)
        else:
            temp = tk.Entry(self)
            Enter = tk.Button(self, text="Enter", fg="yellow", bg="black", command=self.enter)
            Enter.grid(column=2, row=rows)
        temp.grid(column=2, row=self.row)
        setattr(self, "item"+str(self.row)+"2", temp)

        Quit = tk.Button(self, text="QUIT", fg="red", bg="black", command=self.root.destroy)
        Quit.grid(column=1,row=rows)

    def edit(self):
        print('edit')
        self.switch = True
        self.root.destroy()

    def click(self):
        print("WhAt'd YoU sAy")

    def enter(self):
        print('ennter')

    def add_dvd(self):

        print('add')
        pass

    def remove_dvd(self):
        print('remove')
        pass

    def print_collection(self):
        print('print')
        pass

    def total_cost(self):
        print('cost')
        pass

    def change_who(self):
        print('who')
        pass


app = DvdCollection()
