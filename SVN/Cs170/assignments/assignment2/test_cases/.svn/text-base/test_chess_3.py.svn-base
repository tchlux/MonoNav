from chess_pieces import *
from chess_board import *

#chessboard is going to be a class that holds a 2-d list of board locations
#all of the chess_pieces, mentioned below are going to be inherited from an initial class with an empty move method and location attribute



bd = ChessBoard(two_player=False, ai=False)
b0 = Bishop(row=8, col=3, board)
bd.draw_board()
#this will print the board to the command line
#the names on the board will all spaces with the exception of the knight r8 c7
#the user will be prompted to enter the piece that they want to move
bd.move_piece("b0", "7", "4")
#the program will see if this is a valid move then
#this the move will be confirmed in that the recieving space is empty
#then the piece will be moved

#if the piece name does not exist, it will re-prompt
#if the move is invalid it will re-prompt
#if the move-to location is not empty it will re-prompt

#grid layout is row(1-8) col(1-8)

before
0 1 2 3 4 5 6 7 8
1 - - - - - - - -
2 - - - - - - - -
3 - - - - - - - -
4 - - - - - - - -
5 - - - - - - - -
6 - - - - - - - -
7 - - - - - - - -
8 - - B - - - - -

after
0 1 2 3 4 5 6 7 8
1 - - - - - - - -
2 - - - - - - - -
3 - - - - - - - -
4 - - - - - - - -
5 - - - - - - - -
6 - - - - - - - -
7 - - - B - - - -
8 - - - - - - - -
