# pppppppaaatrick

# this function computes the numbers in between the ones in each row
# pre: the previous row in a list form
# post: outputs the current row in list form
def return_numbers_in_row(list_number_one):
    row_number = len(list_number_one)
    list_number_two = list()
    for i in range (1, row_number):
        number = list_number_one[i-1] + list_number_one[i]
        list_number_two.insert(i, number)
    list_number_two.insert(0, 1)
    list_number_two.insert(row_number, 1)
    return list_number_two

# this function prints a pascal triangle
# pre: the number of rows must be an integer greater or equal to two
# post: The triangle is printed
def print_final_pascal_triangle():
    list_number_one = list()
    list_number_one.append(1)
    list_number_one.append(1)
    print("1")
    print("1 1")
    for i in range (3, number_of_rows + 1):
        list_number_one = (return_numbers_in_row(list_number_one))
        for var in range (i):
            print(list_number_one[var], end = " ")
        print("")


print_final_pascal_triangle()
