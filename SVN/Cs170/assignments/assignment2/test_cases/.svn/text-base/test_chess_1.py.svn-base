from chess_pieces import *
from chess_board import *

#chessboard is going to be a class that holds a 2-d list of board locations
#all of the chess_pieces, mentioned below are going to be inherited from an initial class with an empty move method and location attribute



bd = ChessBoard(two_player=False, ai=False)

#> the p1 Pawn piece will be made in the board initialization
p1 = Pawn(row=7, col=2, board)

#  all of this will be in the board initialization as well
# p0 = Pawn(row=7, col=1, board)
# p2 = Pawn(row=7, col=3, board)
# p3 = Pawn(row=7, col=4, board)
# p4 = Pawn(row=7, col=5, board)
# p5 = Pawn(row=7, col=6, board)
# p6 = Pawn(row=7, col=7, board)
# p7 = Pawn(row=7, col=8, board)
# r0 = Rook(row=8, col=1, board)
# r1 = Rook(row=8, col=8, board)
# k0 = Knight(row=8, col=2, board)
# k1 = Knight(row=8, col=7, board)
# b0 = Bishop(row=8, col=3, board)
# b1 = Bishop(row=8, col=6, board)
# qn = Queen(row=8, col=4, board)
# kg = King(row=8, col=5, board)
#more will be added if there is a second player

bd.draw_board()
#this will print the board to the command line
#the names on the board will be as listed p1,p2, etc
#the user will be prompted to enter the piece that they want to move
bd.move_piece("p1", "6", "2")
#the program will see if this is a valid move then
#this the move will be confirmed in that the recieving space is empty
#then the piece will be moved

#if the piece name does not exist, it will re-prompt

#grid layout is row(1-8) col(1-8)
#if the move is valid the piece will be moved to the new space and the board will be re-printed with the correct layout


before
0 1 2 3 4 5 6 7 8
1 - - - - - - - -
2 - - - - - - - -
3 - - - - - - - -
4 - - - - - - - -
5 - - - - - - - -
6 - - - - - - - -
7 - P - - - - - -
8 - - - - - - - -

after
0 1 2 3 4 5 6 7 8
1 - - - - - - - -
2 - - - - - - - -
3 - - - - - - - -
4 - - - - - - - -
5 - - - - - - - -
6 - P - - - - - -
7 - - - - - - - -
8 - - - - - - - -
