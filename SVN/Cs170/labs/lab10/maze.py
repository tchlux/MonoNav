from stack_and_queue import Stack

class Maze:

    def __init__(self, cells):
        self.cells = cells 

    def is_cell_empty(self, cell):
        return self.cells[cell[0]][cell[1]] == 0

    def is_cell_valid(self, cell):
        if cell[0] < 0 or cell[1] < 0:
            return False
        if cell[0] >= len(self.cells) or cell[1] >= len(self.cells):
            return False
        return True

    def mark_cell_visited(self, cell):
        self.cells[cell[0]][cell[1]] = 2

    #Method: This method returns true or false for if a maze can be
    #        traversed from a set start point
    #Pre:    The method is called
    #Att's:  self.is_cell_valid (type=Method)
    #        self.is_cell_empty (type=Method)
    #        self.mark_cell_visited(type=Method)
    #Post:   Whether or not the maze can be traversed is returned as a
    #        boolean
    def can_traverse(self, start_cell, end_cell):
        maze_runner = Stack()
        maze_runner.push(start_cell)
        self.mark_cell_visited(start_cell)
        success = False
        while maze_runner.size > 0 and not success:
            cell = maze_runner.pop()
            success = cell == end_cell
            above = (cell[0], cell[1]+1)
            right = (cell[0]+1, cell[1])
            left = (cell[0]-1, cell[1])
            below = (cell[0], cell[1]-1)
            if self.is_cell_valid(above) and self.is_cell_empty(above):
                maze_runner.push(above)
                self.mark_cell_visited(above)
            if self.is_cell_valid(left) and self.is_cell_empty(left):
                maze_runner.push(left)
                self.mark_cell_visited(left)
            if self.is_cell_valid(right) and self.is_cell_empty(right):
                maze_runner.push(right)
                self.mark_cell_visited(right)
            if self.is_cell_valid(below) and self.is_cell_empty(below):
                maze_runner.push(below)
                self.mark_cell_visited(below)
        return success

def test_linear_maze():
    cells = [[0, 0, 0, 0, 1],
             [1, 1, 1, 0, 1],
             [1, 0, 0, 0, 1],
             [1, 0, 1, 1, 1],
             [1, 0, 0, 0, 0]]
    start_cell = (0, 0)
    end_cell = (4, 4)
    maze = Maze(cells)
    can_traverse = maze.can_traverse(start_cell, end_cell)
    print("Actual: " + str(can_traverse) + " Expected: True")
    cells[3][3] = 1
    can_traverse = maze.can_traverse(start_cell, end_cell)
    print("Actual: " + str(can_traverse) + " Expected: False")

def test_fork_maze():
    cells = [[0, 0, 0, 1, 1],
             [1, 1, 0, 1, 1],
             [1, 0, 0, 0, 1],
             [1, 0, 1, 0, 1],
             [0, 0, 1, 0, 0]]
    start_cell = (0, 0)
    end_cell = (4, 4)
    maze = Maze(cells)
    can_traverse = maze.can_traverse(start_cell, end_cell)
    print("Actual: " + str(can_traverse) + " Expected: True")
    cells[3][3] = 1
    can_traverse = maze.can_traverse(start_cell, end_cell)
    print("Actual: " + str(can_traverse) + " Expected: False")


if __name__ == "__main__":
    test_linear_maze()
    test_fork_maze()
