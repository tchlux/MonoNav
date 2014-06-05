import sys, math

num = int(sys.stdin.readline())

while num != 0:
    total = 0
    power = 1
    for digit in str(num):
        digit = int(digit)
        total += digit ** power
        power += 1
    s = str(num) + " "
    if total == num:
        s += "is a powerful number."
    else:
        s += "is not a powerful number."
    print(s)
    num = int(sys.stdin.readline())
