import math

def sum_of_ten(number):
    sum_of = 0
    for i in range (11):
        sum_of += number
    return sum_of



#print(" 0.1", decimal.Decimal(0.1))
print(" sum of 10 .1", sum_of_ten(0.1))
print('compare .3 == .1 + .2', 0.3 == 0.1 + 0.2)
print('2.675 rounded to two', round(2.675,2))
