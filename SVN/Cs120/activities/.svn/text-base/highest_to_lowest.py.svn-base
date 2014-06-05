def the_other_two_in_order(thing_1, thing_2, thing_3):
    print('')
    if thing_2 > thing_3:
        print(thing_1, ' ', thing_2, ' ', thing_3)
    if thing_3 > thing_2:
        print(thing_1, ' ', thing_3, ' ', thing_2)

def put_numbers_in_order(first, second, third):
    if first > second:
        the_other_two_in_order(first, second, third)

    if second > third:
        the_other_two_in_order(second, third, first)

    if third > first:
        the_other_two_in_order(third, first, second)

def put_numbers_in_order_boolean(a, b, c):
    if a>b and a>c and b>c:
        print(a, ' ', b, ' ', c)
    if a>b and a>c and c>b:
        print(a, ' ', c, ' ', b)
    if b>a and b>c and a>c:
        print(b, ' ', a, ' ', c)
    if b>a and b>c and c>a:
        print(b, ' ', c, ' ', a)
    if c>a and c>b and a>b:
        print(c, ' ', a, ' ', b)
    if c>a and c>b and b>a:
        print(c, ' ', b, ' ', a)


def ask_for_variables():
    a = input('First Number: ')
    b = input('Second Number: ')
    c = input('Third Number: ')
    put_numbers_in_order(a, b, c)



print('')
print('')
ask_for_variables()
print('')
print('')
