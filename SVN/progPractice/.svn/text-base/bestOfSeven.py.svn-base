import sys

def test_ratio(ratios):
    win_loss = [int(num) for num in sys.stdin.readline().split()]
    ratio.append(win_loss[0] / win_loss[1])
    return(max(win_loss) >= 4)

def generate_positions(teams):
    pos = []
    while (teams > 0):
        for i in range(teams//2): pos.append(0)

tourneys = int(sys.stdin.readline())
for i in range(tourneys):
    teams = int(sys.stdin.readline())
    possible = True
    ratios = []
    for g in range(teams):
        possible = possible and test_ratio(ratios)
    print("Tournament #"+str(i+1), end=": ")
    if possible: print("Possible")
    else: print("Impossible")
