# Roanoke College: Team 35
# prob2.py
import sys

def get_paths(dimension):
    lists = [[1 for i in range(dimension)]]
    size = dimension
    while (size > 1):
        new_list = []
        for i in range(size):
            if (len(new_list) > 0):
                try:
                    new_list.append(new_list[-1]+lists[dimension-size][i+1])
                except:
                    pass
            else:
                new_list.append(lists[-1][1])
        lists.append(new_list)
        size -= 1
    return(lists[-1][-1])
    
line = int(sys.stdin.readline())
while (line != 0):
    numPaths = get_paths(line+1)
    print(numPaths)
    line = int(sys.stdin.readline())
