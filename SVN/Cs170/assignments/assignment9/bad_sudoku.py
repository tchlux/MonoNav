import sys
from stack_and_queue import *

#Search term: todo
ROWS_IN_BOX = 3
COLS_IN_BOX = 3
BOXES_IN_ROW = 3
BOXES_IN_COL = 3
NUMBER_OF_BOXES = BOXES_IN_ROW * BOXES_IN_COL
NUMBER_OF_PLACES_ON_BOARD = (ROWS_IN_BOX * COLS_IN_BOX * BOXES_IN_ROW
                             * BOXES_IN_COL )
VALUE_RANGE = [1,10]

#Class:   The sudoku game board confirmer!
#Runtime: todo
#Mainloop:todo
class Sudoku:
    #Method:Constructor: this method initializes all necessary attributes
    #Pre:   The file name is given as a system arguemnt
    #Att's: All are created here
    #Post:  The game board is ready to be checked
    def __init__(self, test_file=None):
        self.boxes = []
        self.rows = []
        self.original_rows = []
        self.cols = []
        self.solutions = []
        self.incrementable = True
        self.stack = Stack()
        self._import_board(test_file)
        self._build_boxes()

    #Method:This method takes a filename and turns the file into a
    #       Sudoku board
    #Pre:   The filename is given as a string
    #Att's: self.rows (type=List)
    #       self.cols (typw=List)
    #Post:  Saves self.rows and self.cols with 2D lists of values
    def _import_board(self, filename):
        #This is a check to see if the filename was given on
        #initialization or as a system argument, if neither raises
        #exception
        if filename == None:
            try:
                filename = sys.argv[1]
            except:
                raise Exception("There needs to be file name given either upon initialization or as a system argument.")

        #This is what opens the file
        with open(filename) as puzzle:
            line_list = puzzle.readlines()
            puzzle.close()
        self.rows = [line.split() for line in line_list]
        self.rows = [[int(row[i]) for i in range(len(row))] for row in self.rows]
        self.original_rows = [[int(row[i]) for i in range(len(row))] for row in self.rows]
        self.cols = [[row[i] for row in self.rows] for i in
                     range(len(self.rows[0]))]

    #Method:This method builds the boxes based on the self.rows
    #Pre:   The method is called by the constructor
    #Att's: self.rows (type=List)
    #       self.boxes (type=List)
    #Post:  self.boxes is made as a 2D list of boxes reading left to
    #       right then down
    def _build_boxes(self):
        curr_box = []
        for box in range(NUMBER_OF_BOXES):
            row_start = box//ROWS_IN_BOX * ROWS_IN_BOX
            col_start = (box%COLS_IN_BOX)*BOXES_IN_ROW
            for row in range(row_start,row_start+ROWS_IN_BOX):
                for col in range(col_start,col_start+COLS_IN_BOX):
                    curr_box.append(self.rows[row][col])
            self.boxes.append(curr_box)
            curr_box = []

    #Method:This method checks if any values in the row conflict with
    #       the value given
    #Pre:   The row and value are given as Integers
    #Att's: todo
    #Post:  A boolean is returned for "is valid move"
    def _check_valid_row(self, row, val):
        return not val in row

    #Method:This method checks if any values in the col conflict with
    #       the value given
    #Pre:   The col and value are given as Integers
    #Att's: todo
    #Post:  A boolean is returned for "is valid move"
    def _check_valid_col(self, col, val):
        return not val in col

    #Method:This method checks if any values in the box conflict with
    #       the value given
    #Pre:   The box is given as a 2D list and value is given as an
    #       Integer
    #Att's: todo
    #Post:  A boolean is returned for "is valid move"
    def _check_valid_box(self, box, val):
        return not val in box

    #Method:
    #Pre:   
    #Att's: 
    #Post:  
    def _return_row_col(self):
        place = self.stack.size - 1 #This -1 is to adjust for the way
                                    #indices work on python Lists
        row = place//(ROWS_IN_BOX*BOXES_IN_COL)
        col = (place)%(COLS_IN_BOX*BOXES_IN_ROW)
        return row, col

    #Method:
    #Pre:   
    #Att's: 
    #Post:  
    def _set_value(self):
        row,col = self._return_row_col()
        value = self.stack.peek()
        self.rows[row][col] = value

    #Method:
    #Pre:   
    #Att's: 
    #Post:  
    def _reset_current_value(self):
        place = self.stack.size - 1 #This -1 is to adjust for the way
                                    #indices work on python Lists
        row = place//(ROWS_IN_BOX*BOXES_IN_COL)
        col = (place)%(COLS_IN_BOX*BOXES_IN_ROW)
        self.rows[row][col] = self.original_rows[row][col]

    #Method:
    #Pre:   
    #Att's: 
    #Post:  
    def _is_valid(self):
        row, col = self._return_row_col()
        box = col//COLS_IN_BOX + (row//ROWS_IN_BOX)*(BOXES_IN_COL)
        curr_value = self.original_rows[row][col]
        if curr_value == 0:
            self.incrementable = True
            value = self.stack.peek()
            case1 = self._check_valid_row(self.rows[row], value)
            case2 = self._check_valid_col(self.cols[col], value)
            case3 = self._check_valid_box(self.boxes[box], value)
            return case1 and case2 and case3
        else:
            self.incrementable = False
            self.stack.pop()
            self.stack.push(curr_value)
            return True

    #Method:
    #Pre:   
    #Att's: 
    #Post:  
    def _reset_and_retreat(self):
        self._reset_current_value()
        self._is_valid()
        value = self.stack.pop()
        print("value:",value,"Increment:",self.incrementable)
        while (value >= VALUE_RANGE[1] or not self.incrementable) and self.stack.size > 0:
            print("while loop ran", value)
            self._reset_current_value()
            self._is_valid()
            value = self.stack.pop()
            self.no_solutions = True
        return value + 1

    #Method:This method cycles through the 9 boxes and through it's
    #       values 
    #Pre:   Method is called from self.run_check
    #Att's: todo
    #Post:  All the boxes are checked for validity
    def _check_values(self):
        low = VALUE_RANGE[0]
        high = VALUE_RANGE[1]
        while self.stack.size < NUMBER_OF_PLACES_ON_BOARD:
            initial_size = self.stack.size
            for guess in range(low,high):
                low = VALUE_RANGE[0]
                print("For loop ran", guess)
                self.stack.push(guess)
                if self._is_valid():
                    self._set_value()
                    break
                else:
                    self.stack.pop()
            final_size = self.stack.size
            print(self.stack)
            if initial_size == final_size:
                print("If executed")
                low = self._reset_and_retreat()
                print("New stack",self.stack)
                print("low", low)
        print(str(self.stack)[-2:0:-1])
        print("All done!")

    #Method:This method runs the whole program
    #Pre:   The method is called from outside this class
    #Att's: todo
    #Post:  The self.solutions list is populated or not
    def run_check(self):
        self._check_values()

if __name__ == "__main__":
    board = Sudoku("puzzle2.txt")
    board.run_check()
