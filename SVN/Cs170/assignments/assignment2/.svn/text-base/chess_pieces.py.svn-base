#This is the base class for all pieces, given some ratios of direction and a max distance.
#    This can determine if a move is valid, and the initialized string is '--'
class ChessPiece():
    #Constructor
    #Pre:    The string name is given for the piece, preferrable 2 char long
    #Post:   The piece is initialized with some attributes for movement
    def __init__(self, string="--"):
        self.string = string
        self.rc_ratio = 0
        self.inverse_ratio = 0
        self.distance = 0

    #This method returns the name of the piece
    #Pre:    The method is called and a self.string exists
    #Post:   The string name is returned
    def __str__(self):
        return self.string

    #This method determines if two pieces are equal
    #Pre:    The other object has to have a self.string attribue that is a str type
    #Post:   The bool for equivalence is returned
    def __eq__(self, obj):
        if obj.string == self.string:
            return True
        else:
            return False

    #This method tests if a move is valid based off of ratios and max distance
    #Pre:    The current row and column are given along with the final row and column
    #Post:   A bool is given for whether or not a move is valid
    def valid_move(self, cr, cc, fr, fc):
        final = False
        r = (cr-fr)
        c = (cc-fc)
        distance = ((r**2 + c**2)**(1/2))
        try:
            rc_ratio = (abs(cr-fr)/abs(cc-fc))
        except:
            rc_ratio = (abs(cc-fc)/abs(cr-fr))
        a = rc_ratio == self.rc_ratio
        b = rc_ratio == self.inverse_ratio
        c = (distance < self.distance)
        if (a or b) and c:
            final = True
        return final

#This class is a Pawn piece in chess inheriting from the generic ChessPiece class
class Pawn(ChessPiece):
    #Constructor
    #Pre:    The number is given for the piece, set to 0 if not given
    #Post:   The piece is initialized as a ChessPiece would be
    def __init__(self, num=0):
        name = "P"+str(num)
        super().__init__(string=name)

    #This method is overwritten bc of the special nature of the pawn's movement
    #Pre:    The current row and column, along with the final row and column are given
    #Post:   The move is determined valid or not by the simplified pawn rules
    def valid_move(self, cr, cc, fr, fc):
        final = False
        if (cc-fc) == 0:
            if (cr-fr) == 1:
                final = True
        return final

#This class is a Rook piece in chess inheriting from the generic ChessPiece class
class Rook(ChessPiece):
    #Constructor
    #Pre:    The number is given for the piece, set to 0 if not given
    #Post:   The piece is initialized with the adequate movement ratios for
    #        a rook, and a max distance of 1 more than the length of the board
    def __init__(self, num=0):
        name = "R"+str(num)
        super().__init__(string=name)
        self.rc_ratio = 0
        self.inverse_ratio = 0
        self.distance = 8

#This class is a Knight piece in chess inheriting from the generic ChessPiece class
class Knight(ChessPiece):
    #Constructor
    #Pre:    The number is given for the piece, set to 0 if not given
    #Post:   The piece is initialized with the adequate movement ratios for
    #        a knight, and a max distance of .1 more than the standard distance
    #        traveled by a knight is set
    def __init__(self, num=0):
        name = "K"+str(num)
        super().__init__(string=name)
        self.rc_ratio = 2
        self.inverse_ratio = 1/2
        self.distance = (5)**(1/2) + .1

#This class is a Bishop piece in chess inheriting from the generic ChessPiece class
class Bishop(ChessPiece):
    #Constructor
    #Pre:    The number is given for the piece, set to 0 if not given
    #Post:   The piece is initialized with the adequate movement ratios for a Bishop
    #        and a max distance of 8, 1 more than the length of the board is set
    def __init__(self, num=0):
        name = "B"+str(num)
        super().__init__(string=name)
        self.rc_ratio = 1
        self.inverse_ratio = 1
        self.distance = 8

#This class is a King piece in chess inheriting from the generic ChessPiece class
class King(ChessPiece):
    #Constructor
    #Pre:    The number is given for the piece, set to 0 if not given
    #Post:   The piece is initialized with the adequate movement ratios for a King
    #        and a max distance of 2 is set to ensure all movements are at most 1 unit
    def __init__(self, num=" "):
        name = "K"+str(num)
        super().__init__(string=name)
        self.rc_ratio = 1
        self.inverse_ratio = 0
        self.distance = 2

#This class is a Queen piece in chess inheriting from the generic ChessPiece class
class Queen(ChessPiece):
    #Constructor
    #Pre:    The number is given for the piece, set to 0 if not given
    #Post:   The piece is initialized with the adequate movement ratios for a Queen
    #        and a max distance of 8 is set, 1 more than the length of the board
    def __init__(self, num=" "):
        name = "Q"+str(num)
        super().__init__(string=name)
        self.rc_ratio = 1
        self.inverse_ratio = 0
        self.distance = 8
