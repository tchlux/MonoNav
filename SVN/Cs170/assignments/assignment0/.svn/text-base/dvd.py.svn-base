import random
import tkinter as tk
import pickle
import os

#this class is for the individual dvds stored
class Dvd:

#constructor
#pre:  the title, release year, director, cost, who has the dvd
#post: the attributes are stored for the dvd
    def __init__(self, title=None, release_year=None, director=None, cost=None, who=None):
        self.title = title
        self.release_year = release_year
        self.director = director
        self.cost = cost
        self.who = who

#this returns the list that can be easily turned into a formatted gui screen
#pre: function is called
#post: a list of the attributes names and their values for the dvd
    def string(self):
        self.print_list = [["Title: ",self.title],["Release Year: ",self.release_year],["Director: ",self.director],["Cost: ",self.cost],["Who has it?: ",self.who],['','']]
        return self.print_list

#this class runs the Tkinter menu system set up
#pre: the class is called
#post: the Gui menu system with a few simple operations for dvds in a collection and some entries
class DvdCollection:

#constructor for dvd collection
#pre: none
#post: all needed attributes are set for the program to run (noted out things are beta code that's unfinished) and then the program is run
    def __init__(self):
        self.done = False
        self.done2 = False
        self.done3 = False
        self.done4 = False
        # while self.done == False:
        self.dvd_collection = self.return_a_file('collection')
        self.main_menu_list = [['Dvds',str(len(self.dvd_collection))]]
        self.button_list = [["Add Dvd",""],["Remove Dvd",""], ["Print Collection",""],["Count the monay",""],["Change who has a dvd", ""],["Find 'em all",'']]
        self.add_list = [["Title",""],["Release Year",""],["Director",""],["Cost",""],["Who has it?",""]]
        self.remove_list = [["Which Dvd would you like to remove?   ",""]]
        total_cost = 0
        for dvd in self.dvd_collection:
            try:
                total_cost += float(dvd.cost)
            except:
                pass
        self.cost_list = [["Total money in tha bank: ", total_cost]]
        self.who_list = [["Well what movie do you want to steal? ", ""],["And who are you gonna 'lend' it to now? ", ""]]
        self.where_list = [["Who is it that you want to find today master? ", ""]]


        self.first_screen = TkFrame(self.main_menu_list, "Main Menu  (what do ya want??)", True, quit_button=False)
        self.first_screen.mainloop()

        self.second_screen = TkFrame(self.button_list, "Editting (lets go!)", False, False, buttons=True)
        self.second_screen.mainloop()
        self.second_screen.done = self.done2

        if self.second_screen.switch == 'add':
            self.third_screen = TkFrame(button_lst=self.add_list, txt="Add Dvd", entry=True, dvds=self.dvd_collection)
        elif self.second_screen.switch == 'remove':
            self.third_screen = TkFrame(button_lst=self.remove_list, txt="Remove Dvd", entry=True, dvds=self.dvd_collection)
        elif self.second_screen.switch == "print":
            self.final_list = []
            for dvd in self.dvd_collection:
                temp_list = dvd.string()
                for item in temp_list:
                    self.final_list.append(item)
            self.third_screen = TkFrame(button_lst=self.final_list, txt="All Dvds", dvds=self.dvd_collection)
        elif self.second_screen.switch == 'cost':
            self.third_screen = TkFrame(button_lst=self.cost_list, txt="Make it rain in da club", dvds=self.dvd_collection)
        elif self.second_screen.switch == 'who':
            self.third_screen = TkFrame(button_lst=self.who_list, entry=True, txt="Give it back! So I can give it away..", dvds=self.dvd_collection)
        elif self.second_screen.switch == "where":
            self.third_screen = TkFrame(button_lst=self.where_list, txt="You can't hide from me >:D", entry=True, where=True, dvds=self.dvd_collection)
        try:
            self.done3 = self.third_screen.done
            self.third_screen.mainloop()
            self.save_a_collection(self.third_screen.collection, "collection")
        except:
            pass
        self.final_list = []
        try:
            for dvd in self.third_screen.where_where:
                temp_list = dvd.string()
                for item in temp_list:
                    self.final_list.append(item)
            self.fourth_screen = TkFrame(button_lst=self.final_list, txt="Gotta catch 'em all", dvds=self.dvd_collection)
            self.fourth_screen.mainloop()
            self.done4 = self.fourth_screen.done
        except:
            pass
        # if (self.done2 or self.done3 or self.done4):
        #     self.done = True


#this returns the saved file if it exists
#pre: function is called with a file name
#post: the file is unpickled and returned
    def return_a_file(self, a_file):
        if os.path.exists(a_file +'.txt'):
            with open(a_file +'.txt', 'rb') as f:
                a_file = pickle.load(f)
                f.close()
        else:
            a_file = []
        return a_file

#this method saves the collection passed to it with the name given + "txt" so names given should NOT already have 'txt'
#pre: a list/dictionary/string and a name for the file
#post: the list/dictionary/string is pickled and then saved to a file
    def save_a_collection(self, a_collection, a_file):
        with open(a_file+'.txt', 'wb') as f:
            pickle.dump(a_collection, f)
            f.close()


#this class makes a versatile Tkinter frame type
class TkFrame(tk.Frame):

#constructor
#pre: the list of button names, label frame text, edit button, entry spaces, click buttons, dvd_collection, quit button, "looking for a person?" true or false)
#post: the root and all the attributes are initialized and the grid is allocated, finally a for loop is run that turns the provided list into a Tkinter display
    def __init__(self, button_lst=None, txt="Tkinter", edit=False, entry=False, buttons=False, dvds=[], quit_button=True, where=False):
        self.done = False
        self.quit = quit_button
        self.buttons = button_lst
        self.where = where
        self.switch = False
        self.root = tk.Tk()
        self.collection = dvds
        tk.LabelFrame.__init__(self, bg="black", fg="white", padx=100, pady=100, text=txt)
        col = len(button_lst[0])
        rows = len(button_lst)+1
        self.grid(column=col,row=rows)
        self.row = 1
        for item in button_lst:
            self.createDisplay(item, rows, edit, entry, buttons)
            self.row += 1

#this method fills the tkinter window with dynamic buttons/entry boxes/labels (commands are set specific if certain numbers of buttons exist)
#pre: the current item (row) from the list, the number of rows, edit button(true/false), entry(t/f), buttons(t/f)
#post: one row of the display is created per loop
    def createDisplay(self, item, rows, edit, entry, buttons):
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
            elif self.row == 6:
                temp["command"] = self.find_em
            else:
                temp["command"] = self.click

        temp["text"] = item[0]
        temp.grid(column=1, row=self.row)
        setattr(self, "item"+str(self.row)+"1", temp)
        if entry == False:
            temp = tk.Label(self, fg="cyan", bg="black")
            temp["text"] = item[1]
            if edit == True:
                Edit = tk.Button(self, text="Continue", fg="yellow", bg="black", command=self.edit)
                Edit.grid(column=2, row=rows)
        else:
            setattr(self, "grid"+str(self.row), tk.Entry(self))
            temp = getattr(self, "grid"+str(self.row))

            Enter = tk.Button(self, text="Enter", fg="yellow", bg="black", command=self.enter)
            Enter.grid(column=2, row=rows)
        temp.grid(column=2, row=self.row)
        setattr(self, "item"+str(self.row)+"2", temp)

        if self.quit == True:
            Quit = tk.Button(self, text="Quit", fg="red", bg="black", command=self.click)
            Quit.grid(column=1,row=rows)

#this method handles the "Continue" button (names were changed, that's why it says 'edit'
#pre: the button is clicked
#post: the current menu is taken down and the switch is set to true
    def edit(self):
        self.switch = True
        self.root.destroy()

#this method was created to test and end the menus at specific times but was never fully implemented
#pre: the button was clicked
#post: the menu is taken down and done is set to True
    def click(self):
        self.done = True
        self.root.destroy()

#this method handles the enter button in three different circumstances (5 buttons(second menu), 1 button(first menu, search menu), 2 buttons(switch dvd holder))
#pre: the enter button is clicked
#post: the corresponding action is preformed specific to the current menu (circumstances listed above)
    def enter(self):
        if len(self.buttons) == 5:
            title = self.grid1.get().strip()
            release = self.grid2.get().strip()
            direct = self.grid3.get().strip()
            cost = self.grid4.get().strip()
            who = self.grid5.get().strip()
            self.collection.append(Dvd(title, release, direct, cost, who))
            self.root.destroy()

        elif len(self.buttons) == 1:
            if self.where == False:
                try:
                    dvd_title = self.grid1.get().strip()
                    for dvd in self.collection:
                        if dvd.title == dvd_title:
                            self.collection.remove(dvd)
                    self.root.destroy()
                except:
                    print("I'm sorry, there was an error processing your request.\n  Feel free to try again in 17 hours!")
            else:
                self.where_where = []
                who = self.grid1.get().strip()
                try:
                    for dvd in self.collection:
                        if dvd.who ==  who:
                            self.where_where.append(dvd)
                    self.root.destroy()
                except:
                    print("I'm sorry, there was an error processing your request.\n  Feel free to try again in 17 hours!")
        elif len(self.buttons) == 2:
            try:
                dvd_title = self.grid1.get().strip()
                new_holder = self.grid2.get().strip()
                for dvd in self.collection:
                    if dvd.title == dvd_title:
                        dvd.who = new_holder
                self.root.destroy()
            except:
                print("I'm sorry, there was an error processing your request.\n  Feel free to try again in 17 hours!")


#this whole set of methods sets a switch to a corresponding value and then closes the tkinter window
#pre: the corresponding button is clicked
#post: the switch is changed to the correct process for each button so the next window will the correct
################################################
    def add_dvd(self):
        self.switch = 'add'
        self.root.destroy()

    def remove_dvd(self):
        self.switch = 'remove'
        self.root.destroy()

    def print_collection(self):
        self.switch = 'print'
        self.root.destroy()

    def total_cost(self):
        self.switch = 'cost'
        self.root.destroy()

    def change_who(self):
        self.switch = 'who'
        self.root.destroy()

    def find_em(self):
        self.switch = 'where'
        self.root.destroy()
###############################################


app = DvdCollection()
