import sys
from stack_and_queue import *

#Search term: todo
                #These are values set for the reading in of the sudoku
                #boards
ROWS_IN_BOX = 3 
COLS_IN_BOX = 3
BOXES_IN_ROW = 3
BOXES_IN_COL = 3
NUMBER_OF_BOXES = BOXES_IN_ROW * BOXES_IN_COL
NUMBER_OF_PLACES_ON_BOARD = (ROWS_IN_BOX * COLS_IN_BOX * BOXES_IN_ROW
                             * BOXES_IN_COL )
VALUE_RANGE = [1,10] #This is so the program knows what range to loop
                     #through when trying to find successful values.
MAX_NUMBER_OF_SOLUTIONS = 100  #This is to stop the program from
                               #running forever when there are lots of
                               #solutions
NUMBER_OF_SEEDS = 7  #This is for creating random boards.


#Scotty,
#    Sorry I didn't get to put as much work into this assignment as I
#    wanted to.  I did plan on creating random boards and having it be
#    an interactive game, but sadly as we are all too aware, there are
#    not enough hours in the week.  I can't really remember what I had
#    done/forgotten to do since last weekend when I finished the code,
#    so I hope I didn't miss anything important.  Just wanted to tell
#    you this in case there are some weird half-completed snippets!


#Class:   The sudoku game board confirmer!
#Runtime: ~2 second per 100 solutions
#Mainloop:No
class Sudoku:
    #Method:Constructor: this method initializes all necessary attributes
    #Pre:   The file name is given as a system arguemnt or upon
    #       initialization (an error is raised if not)
    #Att's: All are created here
    #Post:  The game board is ready to be checked, rows boxes and
    #       columns are created through other methods as well
    def __init__(self, test_file=None):
        self.boxes = []
        self.rows = []
        self.original_rows = []
        self.cols = []
        self.solutions = []
        self.incrementable = True
        self.done = False
        self.stack = Stack()
        self._build_rows(self._import_board(test_file))
        self._build_boxes()
        self._build_cols()

    #Method:This method takes a filename and turns the file into a
    #       Sudoku board
    #Pre:   The filename is given as a string
    #Att's: None
    #Post:  Returns the list of lines in the filename given, raises an
    #       exception of no board name is found
    def _import_board(self, filename):
        #This is a check to see if the filename was given on
        #initialization or as a system argument, if neither raises
        #exception
        try:
            print("I see you at the command line.")
            filename = sys.argv[1]
        except IndexError:
            if filename == None:
                raise Exception("There needs to be file name given either upon initialization or as a system argument.")
        #This is what opens the file
        with open(filename) as puzzle:
            line_list = puzzle.readlines()
            puzzle.close()
        return line_list

    #Method:This method builds the rows of the board
    #Pre:   A board is given as a list of strings for each row
    #Att's: self.rows (type=List)
    #       self.original_rows (type=List)
    #Post:  rows and original_rows are saved in self, the original
    #       rows will not be changed through the execution of the code
    def _build_rows(self, board):
        self.rows = [line.split() for line in board]
        self.rows = [[int(row[i]) for i in range(len(row))] for row in self.rows]
        self.original_rows = [[int(row[i]) for i in range(len(row))] for row in self.rows]

    #Method:This method builds the cols of the board
    #Pre:   The method is called AFTER the rows have been constructed
    #Att's: self.cols (type=List)
    #       self.rows (type=List)
    #Post:  cols are saved/updated based on the current value of
    #       self.rows
    def _build_cols(self):
        self.cols = []
        self.cols = [[row[i] for row in self.rows] for i in
                     range(len(self.rows[0]))]

    #Method:This method builds the boxes based on the self.rows
    #Pre:   The method is called by the constructor after rows have
    #       been built
    #Att's: self.rows (type=List)
    #       self.boxes (type=List)
    #Post:  self.boxes is made as a 2D list of boxes reading left to
    #       right then down
    def _build_boxes(self):
        self.boxes = []
        curr_box = []
        #Cycle through the number of boxes
        for box in range(NUMBER_OF_BOXES):
            #Get the first row and col based off the box number
            row_start = box//ROWS_IN_BOX * ROWS_IN_BOX
            col_start = (box%COLS_IN_BOX)*BOXES_IN_ROW
            #Cycle through rows in box
            for row in range(row_start,row_start+ROWS_IN_BOX):
                #Cycle through cols in box
                for col in range(col_start,col_start+COLS_IN_BOX):
                    #Add value to box
                    curr_box.append(self.rows[row][col])
            #Append the completed box to self.boxes, then repeat
            self.boxes.append(curr_box)
            curr_box = []

    #Method:This method checks if any values in the row conflict with
    #       the value given
    #Pre:   The row is given as a list and the value is given as an
    #       Integer
    #Att's: None
    #Post:  A boolean is returned for "is valid move"
    def _check_valid_row(self, row, val):
        return not val in row

    #Method:This method checks if any values in the col conflict with
    #       the value given
    #Pre:   The col is given as a list and value == Integer
    #Att's: None
    #Post:  A boolean is returned for "is valid move"
    def _check_valid_col(self, col, val):
        return not val in col

    #Method:This method checks if any values in the box conflict with
    #       the value given
    #Pre:   The box is given as a 2D list and value is given as an
    #       Integer
    #Att's: None
    #Post:  A boolean is returned for "is valid move"
    def _check_valid_box(self, box, val):
        return not val in box

    #Method:This method returns the current row and column of the
    #       stack based on the size of the stack and the size of the
    #       board 
    #Pre:   The method is called
    #Att's: self.stack (type=Stack)
    #Post:  The row and col are returned comma seperated as Integers
    def _return_row_col(self):
        place = self.stack.size - 1 #This -1 is to adjust for the way
                                    #indices work on python Lists
        row = place//(ROWS_IN_BOX*BOXES_IN_COL)
        col = (place)%(COLS_IN_BOX*BOXES_IN_ROW)
        return row, col

    #Method:This method sets the top value of the stack as a permanent
    #       addition to the attribute rows/cols/boxes lists 
    #Pre:   The method is called
    #Att's: self.rows (type=List)
    #       self.stack (type=Stack)
    #       self._return_row_col (type=Method)
    #       self._build_cols (type=Method)
    #       self._build_boxes (type=Method)
    #Post:  The lists for rows columns and boxes are updated and ready
    #       to be cross checked
    def _set_value(self):
        row,col = self._return_row_col()
        value = self.stack.peek()
        self.rows[row][col] = value
        self._build_cols()
        self._build_boxes()

    #Method:This method resets the location for the last stack value
    #       in all of the attributes for row/col/box to what it
    #       originally was upon importing of the board
    #Pre:   The method is called
    #Att's: self.stack (type=Stack)
    #       self.rows (type=List)
    #       self.original_rows (type=List)
    #       self._build_cols (type=Method)
    #       self._build_boxes (type=Method)
    #Post:  The lists for rows cols and boxes are reset to what they
    #       were when the board was imported for the CURRENT LOCATION
    #       ONLY (curr loc based on stack size)
    def _reset_current_value(self):
        place = self.stack.size - 1 #This -1 is to adjust for the way
                                    #indices work on python Lists
        row = place//(ROWS_IN_BOX*BOXES_IN_COL)
        col = (place)%(COLS_IN_BOX*BOXES_IN_ROW)
        self.rows[row][col] = self.original_rows[row][col]
        self._build_cols()
        self._build_boxes()

    #Method:This method checks if the most recent addition to the
    #       stack is a valid one, if it is it returns True, if the
    #       value already existed on the board upon importation it
    #       adds that value to the stack.  It also sets
    #       self.incrementable to True if the value was a seed, False
    #       if it was empty.
    #Pre:   The method is called
    #Att's: self.stack (type=Stack)
    #       self.original_rows (type=List)
    #       self.incrementable (type=Boolean)
    #       self._return_row_col (type=Method)
    #       self._check_valid_row (type=Method)
    #       self._check_valid_col (type=Method)
    #       self._check_valid_box (type=Method)
    #Post:  A boolean is returned for if the value was valid, if it
    #       was alread given when the board was imported (was a seed),
    #       True is returned and the stack value is set to what the
    #       import gave (to the seed value)
    def _is_valid(self):
        #I realize that the efficiency of this could be improved,
        #but that would have required more time. The repetitive calls
        #to self._return_row_col() made throughout the programe are
        #essentially wasteful.
        row, col = self._return_row_col()
        box = col//COLS_IN_BOX + (row//ROWS_IN_BOX)*(BOXES_IN_COL)
        curr_value = self.original_rows[row][col]
        #If the value was blank
        if curr_value == 0:
            self.incrementable = True
            value = self.stack.peek()
            case1 = self._check_valid_row(self.rows[row], value)
            case2 = self._check_valid_col(self.cols[col], value)
            case3 = self._check_valid_box(self.boxes[box], value)
            return case1 and case2 and case3
        #If the value was a seed
        else:
            self.incrementable = False
            self.stack.pop()
            self.stack.push(curr_value)
            return True

    #Method:This method resets values to what they were and backs up
    #       in the stack.  self._is_valid is run to recreate the
    #       self.incrementable attribute and the while loop continues
    #       to go back until the value in the stack can be incremented
    #       and was not given already (also checks to see if the stack
    #       is empty) the return is the next value to increment in the
    #       stack
    #Pre:   Method is called
    #Att's: self.stack (type=Stack)
    #       self.done (type=Boolean)
    #       self.incrementable (type=Boolean)
    #       self._reset_current_value (type=Method)
    #       self._is_valid (type=Method)
    #Post:  The new value to be tested in the stack is returned (this
    #       is why it is incremented by one, as to not repeat the same
    #       value and get stuck in a loop)
    def _reset_and_retreat(self):
        self._reset_current_value()
        self._is_valid()
        value = self.stack.pop()
        #Retrace steps until a cell that can be incremented is found
        while (value >= VALUE_RANGE[1] or not self.incrementable) and self.stack.size > 0:
            self._reset_current_value()
            self._is_valid()
            value = self.stack.pop()
        #If the program made it back to the beginning of the stack,
        #there are no solutions
        if self.stack.size == 0:
            self.done = True
        #This is to compensate for the 1-step-late break of the while loop
        return value + 1

    #Method:This method cycles through the 9 boxes and through their
    #       values 
    #Pre:   Method is called from self.run_check
    #Att's: self.done (type=Boolean)
    #       self.stack (type=Stack)
    #       self._is_valid (type=Method)
    #       self._set_value (type=Method)
    #Post:  All the boxes are checked for validity
    def _check_values(self):
        #These are the value ranges that can go into each box
        low = VALUE_RANGE[0]
        high = VALUE_RANGE[1]
        #This is to give you updates for the puzzles with a lot of solutions
        print("Number Solution Found: ",end="")
        #Loop until you find the last solution, or none (same case
        #either way)
        while self.stack.size < NUMBER_OF_PLACES_ON_BOARD and not self.done:
            #Used to check if the stack grows or not
            initial_size = self.stack.size
            #Cycles through the values
            for guess in range(low,high):
                self.stack.push(guess)
                if self._is_valid():
                    self._set_value()
                    break
                else:
                    self.stack.pop()
            low = VALUE_RANGE[0]
            if initial_size == self.stack.size:
                low = self._reset_and_retreat()
            if self.stack.size == NUMBER_OF_PLACES_ON_BOARD:
                print(len(self.solutions),end=",")
                sys.stdout.flush()
                self.solutions.append(str(self.stack))
                low = self._reset_and_retreat()
                if len(self.solutions) >= MAX_NUMBER_OF_SOLUTIONS:
                    break

    #Method:This method gives the final remarks to the program, it
    #       provides links to printing solutions or else it says none
    #       were found
    #Pre:   The method is called by self.run_check
    #Att's: self.solutions (type=List)
    #       self._print_board (type=Method)
    #Post:  The boards or lack thereof are printed to the command line
    def _final_remarks(self):
        num_solutions = len(self.solutions)
        if len(self.solutions) == 0:
            print("Sorry this puzzle had no solutions :(")
        else:
            while len(self.solutions) > 0:
                stack = self.solutions.pop()
                if stack in self.solutions:
                    print("Found a duplicate")
                else:
                    self._print_board(stack)
            print("All done! There were",num_solutions,"solution(s) in all!")

    #Method:This method prints the stack in a pretty format
    #Pre:   The stack is given, already in its string form!
    #Att's: None required
    #Post:  The board is printed to the command line
    def _print_board(self, stack):
        string = (str(stack)[-2:0:-1]).split(" ")
        print("\nHere's a solution:")
        print("--------------------------")
        for row in range(ROWS_IN_BOX * BOXES_IN_COL):
            for col in range(COLS_IN_BOX * BOXES_IN_ROW):
                location = row*COLS_IN_BOX*BOXES_IN_ROW + col
                print(string[location], end=" ")
                if (location+1) % COLS_IN_BOX == 0:
                    print(" | ",end="")
            print("")
            if (row+1)%(ROWS_IN_BOX) == 0:
                print("--------------------------")

    #Method:This method runs the whole program
    #Pre:   The method is called from outside this class
    #Att's: self._check_values (type=Method)
    #       self._final_remarks (type=Method)
    #Post:  The program executes and solution(s) are given
    def run_check(self):
        self._check_values()
        self._final_remarks()


    #Method:This method will use the random module to create a random
    #       board given a defined number of seed values
    #       
    #Pre:   
    #Att's: 
    #Post:  
    def random_board(self):

        pass
        
#Function: This runs the program if executed directly, and provides a
#filename to test on that can be un-noted if you don't want to provide
#it as a system argument
if __name__ == "__main__":
    board = Sudoku("puzzle1.txt")
    board.run_check()
