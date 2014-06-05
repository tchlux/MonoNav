# Roanoke College: Team 35
# prob6.py
import sys

elements = int(sys.stdin.readline())

grades = []
for i in range(elements):
    grades.append(int(sys.stdin.readline()))

def getAvg(l, start, end):
    new = l[:start] + l[end:]
    a = sum(new) / len(new)
    return a

avg = float("inf")
for start in range(1, len(grades) - 1):
    for end in range(start, len(grades)):
        new = getAvg(grades, start, end)
        if new < avg:
            avg = new
print(round(avg, 3))
