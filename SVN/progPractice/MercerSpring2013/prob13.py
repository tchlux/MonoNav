import sys
num = int(sys.stdin.readline())

def add(hier, boss, name):
    for sub in hier:
        if sub[0] == boss:
            sub[2].append([name, 0, []])
            break
        else:
            add(sub[2], boss, name)

def sale(hier, name, amt):
    for person in hier:
        if person[0] == name:
            person[1] = amt
        else:
            sale(person[2], name, amt)

def getSale(person, total):
    if len(person) == 0:
        return 0
    total += person[1]
    for sub in person[2]:
        total += getSale(sub, total)
    return total

def query(hier, name, total):
    #print(hier)
    for person in hier:
        if person[0] == name:
            print(getSale(person, 0))
        else:
            query(person[2], name, total + person[1])

for companyNum in range(num):
    print("COMPANY", companyNum + 1)
    coms = int(sys.stdin.readline())
    hier = []
    for comIndex in range(coms):
        command = sys.stdin.readline().strip().split(" ")
        if command[0] == "ADD":
            if len(hier) == 0:
                hier = [[command[2], 0, []]]
            else:
                add(hier, command[1], command[2])
        elif command[0] == "SALE":
            sale(hier, command[1], int(command[2]))
        else:
            query(hier, command[1], 0)

