import sys

def find_solutions(number):
    found = False
    sol = [1]
    curr = 3
    while (curr < number):
        if sum(sol) == number:
            found = True
            print(str(number)+": [",sol[0],",",sol[-1],"]")
        if (sum(sol) >= number):
            sol.pop(0)
        else:
            sol.append(curr)
            curr += 2
    if not found:
        print(str(number)+":", "impossible")

probs = int(sys.stdin.readline())
for i in range(probs):
    num = int(sys.stdin.readline())
    find_solutions(num)
