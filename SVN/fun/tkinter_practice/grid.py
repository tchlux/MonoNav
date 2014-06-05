import math

BOX_SIZE = 2 #This is the box size in pixels
GRID_SIZE = 10*BOX_SIZE  #The initial grid size in pixels, this number squared is the
#number of cells
INITIAL_LOCATION = (4,4) #This is the initial index location of in the grid
SCALE_FACTOR = 3 #The frequency of points checked between two grid cells
OCCUPIED_THRESHOLD = 2 #The number of occurances a cell must contain
#to be considered occupied
DISTANCE_THRESHOLD = .8 #This controls when the while loop of
#self.in_line_of_sight breaks
NUMBER_OF_READINGS = 360 #The number of readings on the rebuild
EXCESS_EXPANSION = 5 #How much extra is added to the grid when expanding
SUBTRACT_AMOUNT = 2

#Class:   This class will create the grid for navigation
#Runtime: 
#Mainloop:
class Grid(object):
    #Method:Constructor, this method initializes all necessary
    #       attributes
    #Pre:   The size of each individual box and the entire grid is
    #       given as integers.
    #Att's: todo
    #Post:  todo
    def __init__(self, box_size=BOX_SIZE, grid_size=GRID_SIZE):
        self.grid = []
        self.outliers = 0
        self.location = INITIAL_LOCATION
        self.box_size = box_size
        self._initialize_grid(grid_size)

    #Method:This method adds a point to the appropriate place in the
    #       grid assuming the current location is the center cell
    #Pre:   A (heading, distance) tuple is given of the location of the points
    #Att's: todo 
    #Post:  The point is either added to the grid or the grid is
    #       expanded if it lies outside of the grid then it is added
    def add_point(self, point):

        gridcell = self._return_grid_cell(point)
        (x,y) = self._get_expand_amount(gridcell)
        if max(abs(x),abs(y)) > 0:
            self._expand(x,y)
            return self.add_point(point)
        if not self._check_line_of_sight(gridcell):
            self.outliers += 1
        self._increment_grid_cell(gridcell)
        print("Point added:", point)
        print("Gridcell:", gridcell)
        print("Current value of that gridcell:", self.grid[gridcell[1]][gridcell[0]])

    #Method:This method returns a list of length 360 that is the
    #       distance to the points surrounding self.location, 0 for
    #       unknown
    #Pre:   Called
    #Att's: self._find_cell (type=Method
    #Post:  A list of distances is returned
    def return_dist_list(self):
        degree_dist_list = []
        for i in range(NUMBER_OF_READINGS):
            degree_dist_list.append(round(self._find_cell(i*(360/NUMBER_OF_READINGS)),2))
        return degree_dist_list

    #Method:Moves self.location to the new position provided
    #Pre:   A heading (Float) and distance (Float) are given
    #Att's: self.location (type=Tuple)
    #       self._return_grid_cell (type=Method)
    #Post:  self.location is moved accordingly
    def move_location(self, heading, distance):
        print("(Heading dist)", "(" + str(heading) + ", " + str(distance) + ")")
        print("Old location", self.location)
        self.location = self._return_grid_cell((heading,distance))
        print("New location:", self.location)

    #Method:This method will initialize all of the cells for the grid
    #Pre:   The grid size is given
    #Att's: todo
    #Post:  The grid is ready to be edited when data points are found
    def _initialize_grid(self, grid_size):
        size = int(math.ceil(grid_size/self.box_size))
        self.grid = [[None for col in range(size)] for row in range(size)]

    #Method:This method continues to go in a straight line until it
    #       hits an occupied cell
    #Pre:   degree (type=Float)
    #Att's: self.grid (type=Grid Class)
    #       self.distance_between_cells (type=Method)
    #       self._return_grid_cell (type=Method)
    #       self.location (type=Tuple/List)
    #Post:  The distance to the nearest point in that direction is
    #       returned
    def _find_cell(self, degree):
        x_change = math.cos(math.radians(degree))/10
        y_change = math.sin(math.radians(degree))/10
        point = self.location
        cell = [int(point[0]), int(point[1])]
        while 0 <= cell[1] < len(self.grid) and 0 <= cell[0] < len(self.grid[0]):
            cell_value = self.grid[cell[1]][cell[0]]
            if cell_value != None and cell_value > OCCUPIED_THRESHOLD:
                #deleted round() in front of the return
                return self.distance_between_cells(cell, self.location)*BOX_SIZE
            point = (point[0]+x_change, point[1]+y_change)
            #Added a round() to the point
            cell = [int(round(point[0])), int(round(point[1]))]
        return 0

    #Method:This method returns whether or not any of the neighbors of
    #       a cell and itself are occupied
    #Pre:   
    #Att's: 
    #Post:  
    def _check_neighbors(self, cell):
        x,y = cell[0],cell[1]
        for col in range(-1,2):
            for row in range(-1,2):
                if x+col < len(self.grid[0]) and x+col >= 0:
                    if y+row < len(self.grid) and y+row >= 0:
                        if (self.grid[y+row][x+col] != None and
                            self.grid[y+row][x+col] >
                            OCCUPIED_THRESHOLD):
                            return True

    #Method:This method will return the amount that the grid needs to
    #       be expanded to accomodate a given data value
    #Pre:   The gridcell that needs to fit in the grid
    #Att's: self.grid (type=Grid class)
    #       self.location (type=List/Tuple)
    #Post:  The amount of cells the grid needs to be expanded
    def _get_expand_amount(self, gridcell):
        x_expand_amount = 0
        y_expand_amount = 0
        if round(gridcell[0]) <= 0:
            x_expand_amount = gridcell[0] - EXCESS_EXPANSION
        elif round(gridcell[0]) >= len(self.grid[0]):
            x_expand_amount = gridcell[0] - len(self.grid[0]) + EXCESS_EXPANSION
        if round(gridcell[1]) <= 0:
            y_expand_amount = gridcell[1] - EXCESS_EXPANSION
        elif round(gridcell[1]) >= len(self.grid):
            y_expand_amount = gridcell[1] - len(self.grid) + EXCESS_EXPANSION
        return (x_expand_amount, y_expand_amount)

    #Method:This method will return the index location of the grid
    #       cell of the point
    #Pre:   A (heading, distance) tuple is given
    #Att's: todo
    #Post:  The index of the grid cell that represents that point is
    #       returned as a tuple (col,row)
    def _return_grid_cell(self,point):
        #removed int(round()) from the x_dist and y_dist
        x_dist = ((point[1]*math.cos(math.radians(point[0]))) /
                     self.box_size)
        y_dist = ((point[1]*math.sin(math.radians(point[0]))) /
                     self.box_size)
        return (self.location[0]+x_dist,self.location[1]+y_dist)

    #Method:The grid cell is given as a tuple index location
    #Pre:   A grid cell is given as a tuple
    #Att's: self.grid (type=2D List)
    #Post:  The grid cell is incremented by 1 if it has already been
    #       found, otherwise it is set to 1
    def _increment_grid_cell(self,cell):
        #Had to int the cell or else it was out of range, looking into it
        cell = (int(round(cell[0])),int(round(cell[1])))
        if self.grid[cell[1]][cell[0]] != None:
            self.grid[cell[1]][cell[0]] += 1
        else:
            self.grid[cell[1]][cell[0]] = 1

    #Method:This method expands the grid by a number of boxes given
    #Pre:   The number of boxes to be added on all sides as an Int
    #Att's: todo
    #Post:  self.grid is expanded accordingly
    def _expand(self, x_amount, y_amount):
        if x_amount >= 0:
            x_expand_size = int(math.ceil(x_amount))
        else:
            x_expand_size = int(math.floor(x_amount))
        if y_amount >= 0:
            y_expand_size = int(math.ceil(y_amount))
        else:
            y_expand_size = int(math.floor(y_amount))
        x,y = 0,0
#expand on the x direction
        for row in self.grid:
            if x_expand_size < 0:
                x = abs(x_expand_size)
                for box in range(0,x_expand_size,-1):
                    row.insert(0,None)
            else:
                for box in range(x_expand_size): row.append(None)
#expand on the y direction
        empty_row = [None for col in range(len(self.grid[0]))]
        if y_expand_size < 0:
            y = abs(y_expand_size)
            for row in range(0,y_expand_size,-1):
                self.grid.insert(0,empty_row[:])
        else:
            for row in range(y_expand_size): self.grid.append(empty_row[:])
#adjust the stored location
        self.location = (self.location[0]+x, self.location[1]+y)

    #Method:This method returns the euclidean distance between two cells
    #Pre:   Two cells are given as Tuples
    #Att's: None
    #Post:  The Euclydean distance is returned
    def distance_between_cells(self, cell1, cell2):
        return ((cell1[0]-cell2[0])**2 + (cell1[1]-cell2[1])**2)**.5

    #Method:This method will return a Boolean for if a cell is in
    #       clear line of sight of the current location
    #Pre:   The gridcell index location in self.grid
    #Att's: todo
    #Post:  A boolean of whether or not there is a clear line of sight
    #       is returned
    def _check_line_of_sight(self, gridcell):
        clear = True
        diff = [gridcell[0]-self.location[0],gridcell[1]-self.location[1]]
        scale = self.distance_between_cells(self.location, gridcell) *SCALE_FACTOR
        if scale == 0:
            # print("scale equaled 0 for this gridcell",gridcell)
            # print("the current location is:", self.location)
            return True
        x_change,y_change = diff[0]/scale, diff[1]/scale
        point = self.location
        while self.distance_between_cells(point,gridcell) > DISTANCE_THRESHOLD:
            point = (point[0]+x_change, point[1]+y_change)
            if self.grid[int(point[1])][int(point[0])] == None:
                self.grid[int(point[1])][int(point[0])] = 0
            elif self.grid[int(point[1])][int(point[0])] > OCCUPIED_THRESHOLD:
#                self.grid[int(point[1])][int(point[0])] = 0
                self.grid[int(point[1])][int(point[0])] -= SUBTRACT_AMOUNT
                clear = False
        return clear
        
    #Pre: factor should be a positive integer, the number of normal
    #size cells that will fit in a single shrunken cell.
    #self.grid must have at least one element. 
    #Post: Returns a grid shrunk by the specified factor. 
    def shrink(self, factor):
        new_grid = []
        for row_index in range(0, len(self.grid), factor):
            row = self.grid[row_index]
            new_grid.append([])
            for col_index in range(0, len(self.grid[0]), factor):
                col = row[col_index]
                
                occupancy_value = 0
                for i in range(factor ** 2):
                    y = i // factor + row_index
                    x = i % factor + col_index
                    if y < len(self.grid) and x < len(self.grid[0]):
                        cell_value = self.grid[y][x]
                        if cell_value != None:
                            occupancy_value += cell_value
                new_grid[-1].append(occupancy_value)
        return new_grid
    
    #Pre: self.grid must have at least one element of type list. 
    #Post: Returns a list of lists which contain the column indices of 
    #cells that are occupied in self.grid. An empty 
    #row will be an empty list. 
    def compute_occupied_row_list(self):
        row_list = []
        for row_index in range(len(self.grid)):
            row = self.grid[row_index]
            row_list.append([])
            for col_index in range(len(self.grid[0])):
                cell_value = self.grid[row_index][col_index]
                if cell_value != None and cell_value > OCCUPIED_THRESHOLD:
                    row_list[row_index].append(col_index)
        return row_list

    #Pre: cell must be a tuple of positive integers.
    #factor must be a positive integer. 
    #Post: Returns a new cell with integer values corresponding to the 
    #original cell's coordinates in a shrunken grid. 
    def compute_shrunk_cell_coord(self, cell, factor):
        x, y = cell
        new_x = x // factor
        new_y = y // factor
        return (new_x, new_y)

    #Method:This prints a string version of self.grid
    #Pre:   Called by a string method
    #Att's: self.grid (type=List)
    #       self.location (type=Tuple/List)
    #Post:  The whole grid is returned as a string
    def __str__(self):
        #print("The number of outliers: ",self.outliers)
        string = ''
        loc = (int(round(self.location[0])),int(round(self.location[1])))
        for row in range(len(self.grid)):
            for col in range(len(self.grid[0])):
                if (col,row) == loc:
                    string += "8 "
                elif self.grid[row][col] == None:
                    string += ". "
                elif self.grid[row][col] >= OCCUPIED_THRESHOLD:
                    string += "0 "
                else:
                    string += "  "
            string += "\n"
        return string

    #Method:This method makes the grid class able to be accessed by index
    #Pre:   The index is given as an integer
    #Att's: self.grid (type=List)
    #Post:  The index location in self.grid is returned
    def __getitem__(self, index):
        return self.grid[index]

    #Method:This method returns the length of the grid
    #Pre:   The len() operator is called
    #Att's: self.grid (type=List)
    #Post:  The length of the grid is returned
    def __len__(self):
        return len(self.grid)

    
if __name__ == "__main__":
    grid = Grid()
    DIST = 30

    # for i in range(-45, 45):
    #     d = i % 360
    #     dist = DIST / math.cos(math.radians(d))
    #     point = (d, dist)
    #     grid.add_point(point)

    # for i in range(135, 225):
    #     d = i % 360
    #     dist = -DIST / math.cos(math.radians(d))
    #     point = (d, dist)
    #     grid.add_point(point)

    # for i in range(45, 135):
    #     d = i % 360
    #     dist = DIST / math.sin(math.radians(d))
    #     point = (d, dist)
    #     grid.add_point(point)

    # for i in range(225, 315):
    #     d = i % 360
    #     dist = -DIST / math.sin(math.radians(d))
    #     point = (d, dist)
    #     grid.add_point(point)

    for i in range(361):
        grid.add_point((i,DIST))

    print(grid)

    # dist_list = []
    # for i in range(-10,290):
    #     if i < 0:
    #         i = i % 360
    #     # dist = (i % 180)/8 + 15
    #     # if i == 90:
    #     #     dist = 50
    #     # if i == 180:
    #     #     dist = 50
    #     dist = 80/(float(i)/80 + 1)
    #     dist_list.append(int(dist))
    #     point = (i,dist)
    #     grid.add_point(point)
    # print(grid)

#    print("resized")
#    grid.resize()
#    print(grid)
    # for i in range(0,len(dist_list)-10,10):
    #     print()
    #     print(grid.return_dist_list()[i:i+10])
    #     print(dist_list[i:i+10])

