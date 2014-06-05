# Roanoke College: Team 35
# prob5.py

import sys

nums = {"0":"", "1":"one ", "2":"two ", "3":"three ", "4":"four ", "5":"five ", "6":"six ", "7":"seven ", "8":"eight ", "9":"nine "}
teens = {"0":"ten ", "1":"eleven ", "2":"twelve ", "3":"thirteen ", "4":"fourteen ", "5":"fifteen ", "6":"sixteen ", "7":"seventeen ", "8":"eighteen ", "9":"nineteen "}
tens = {"0":"", "2":"twenty ", "3":"thirty ", "4":"fourty ", "5":"fifty ", "6":"sixty ", "7":"seventy ", "8":"eighty ", "9":"ninety "}
large = ["", "thousand ", "million ", "billion ", "trillion ", "quadrillion ", "quintillion "]

def print_hundred(hundred):
    final = ""
    while (len(hundred) < 3):
        hundred = "0" + hundred
    if (hundred[1] == "1"):
        final = teens[hundred[2]]
    else:
        final = tens[hundred[1]] + nums[hundred[2]] + final

    if (hundred[0] != "0"):
        final = "hundred " + final
    final = nums[hundred[0]] + final
    return(final)

def chop(number):
    if (len(number) <= 3):
        return(number, "")
    else:
        final = number[0:len(number)-3]
        hundred = number[-3:len(number)]
        return hundred, final

def print_num(number):
    final = ""
    hundred = ""
    tens = ""
    place = 0
    number = number.strip()
    if (number == "0"):
        return "zero"
    while(len(number) > 0):
        hundred, number = chop(number)
        if (hundred.count("0") != 3):
            final = large[place] + final
        final = print_hundred(hundred) + final
        place += 1
    return final.strip()

lines = int(sys.stdin.readline())
for i in range(lines):
    print(print_num(sys.stdin.readline()))

# for i in range(100000000000000000, 100000000000000000000):
#     print(print_num(str(i)))
