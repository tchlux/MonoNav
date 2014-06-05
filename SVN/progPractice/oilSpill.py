import sys

SPILL_SIZE = 100 #square miles per block in spill

# Pre:  matrix is a 2-d accessible list
#       x,y are integers
# Post: Whether or not x and y are in bounds of the matrix
def check(matrix, x, y):
    if (0 <= y < len(matrix)) and (0 <= x < len(matrix[0])):
        return True
    return False

# Pre:  x, y, day are integers
#       land and spill are 2-d accessible lists
# Post: spill is filled with true for all W locations in land that
#       reached within 'day' days
def expand(x, y, day, land, spill):
    if (day > 0):
        for xs in range(-1,2,1):
            for ys in range(-1,2,1):
                if check(land, x+xs, y+ys):
                    if land[x+xs][y+ys] == "w":
                        spill[x+xs][y+ys] = True
                        expand(x+xs, y+ys, day-1, land, spill)

# Pre:  The next line from sys.stdin is of 5 integers
# Post: The oil spill results for that line are produced
def oil_spill():
    nums = [int(num) for num in (sys.stdin.get_line()).split(" ")]
    spill = [[False for x in range(nums[0])] for y in range(nums[1])]
    land = [sys.stdin.get_line() for line in range(nums[1])]
    if not check(land, nums[2]-1, nums[3]-1):
        print("Invalid Coordinates.")
    else:
        if land[nums[3]-1][nums[2]-1] == "L":
            print("Hits land.")
        else:
            expand(nums[2]-1, nums[3]-1, nums[4], land, spill)
            
            print("%d square miles."%(sum([l.count(True) for l in spill]) * SPILL_SIZE))            


LOOPS = int(sys.stdin.get_line()) #number of oild spills
for tragic_oil_spill in range(LOOPS):
    oil_spill()
