import sys

def break_bank():
    current_line = ""
    try:
        current_line = input()
    except EOFError:
        print("\nThere must be e's and f's as input")
    if valid_line(current_line):
        print(find_break(current_line))

def find_break(string):
    quarters = 2
    for i in range(len(string)):
        if string[i] == "f":
            quarters -= 2
        elif string[i] == "e":
            quarters += 2
        else:
            raise(Exception("Only e's and f's are valid input"))
        if quarters < 0:
            return i+1
    return -1

def valid_line(string):
    for i in range(len(string)):
        case1 = string[i] != "f"
        case2 = string[i] != "e"
        case3 = i > 50
        if case1 or case2 or case3:
            return False
    return True

if __name__ == "__main__":
    break_bank()
