from chess_pieces import *

#this is the class that holds the list of pieces on the chess board
class ChessBoard():

    #constructor
    #Pre:    The chess board is called, p2 and ai can be given a bool value of true if
    #        desired
    #Post:   The chess board is put into the run loop
    def __init__(self, p2=False, ai=False):
        self.lst = [[ChessPiece() for i in range(8)] for i in range(8)]
        self.player()
        if p2:
            self.player(0)
        self.run()

    #This method creates the pieces for a player
    #Pre:    The row number of the main pieces is given
    #Post:   The normal set of chess pieces is set on the board
    def player(self, row=7):
        for i in range (8):
            if row == 7:
                self.lst[row-1][i] = Pawn(i)
            else:
                self.lst[row+1][i] = Pawn(i)
        self.lst[row][0] = Rook()
        self.lst[row][7] = Rook(1)
        self.lst[row][1] = Knight()
        self.lst[row][6] = Knight(1)
        self.lst[row][2] = Bishop()
        self.lst[row][5] = Bishop(1)
        if row == 7:
            self.lst[row][3] = Queen()
            self.lst[row][4] = King()
        else:
            self.lst[row][4] = Queen()
            self.lst[row][3] = King()

    #This method is what prints the chess board to the command line
    #Pre:    The method must be called
    #Post:   The board row and column numbers are printed along with the string
    #        values for each piece
    def __str__(self):
        string = ""
        i = 0
        for row in self.lst:
            string = string + str(i) + "   "
            for col in row:
                string = string + str(col) + "  "
            string = string+"\n"
            i += 1
        string = string + "     0   1   2   3   4   5   6   7\n"
        return string

    #This method attempts to move a piece
    #Pre:    The current row and column are given, and the desired row and column 
    #        are given
    #Post:   The piece is sent to coordinates, to test if it is a valid move,
    #        if it is then the piece is moved and a space is left behind
    def move(self, r1, c1, r2, c2):
        if self.lst[r1][c1] == ChessPiece():
            print("There is no piece in that board location")
        else:
            piece = self.lst[r1][c1]
            if piece.valid_move(r1, c1, r2, c2) and (self.lst[r2][c2] == ChessPiece()):
                self.lst[r1][c1] = ChessPiece()
                self.lst[r2][c2] = piece
            else:
                print("That is not a valid move for that piece")

    #This method is what asks for the users input on a move
    #Pre:    The method is called
    #Post:   The move method is sent the current piece (row,col) and the desired
    #        (row,col) destination
    def prompt_move(self):
        print("")
        try:
            (row, col) = input("Current RowCol: ")
            (frow, fcol) = input("Final RowCol: ")
            row = int(row.strip())
            col = int(col.strip())
            frow = int(frow.strip())
            fcol = int(fcol.strip())
        except ValueError:
            print("Blank spaces don't help!  But that's ok, just try again.")
            (row, col, frow, col) = (0,0,0,0)
        try:
            self.move(row, col, frow, fcol)
        except:
            print("")
            print("One of those spaces wasn't on the board")
            self.prompt_move()

    #This method runs the loop to play chess
    #Pre:    The Chess board is initialized
    #Post:   The board is printed, and the game begins
    def run(self):
        self.c = 'y'
        print('')
        while (self.c == 'y'):
            print('')
            print(self)
            print('Example RowCol: 42')
            print('Row = 4 Col = 2')
            self.c = input("Continue?(y,n) ")
            if self.c =="y":
                self.prompt_move()
            print('')

m = ChessBoard()
