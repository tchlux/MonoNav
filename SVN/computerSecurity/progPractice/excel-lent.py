TERMINATE = "R0C0"
ALPHA = 26
ORD_A = ord('A')

# Pre:  A number as an integer >= 0
# Post: the alpha converted version
def convert_to_alpha(num):
    return_string = ''
    while num > 0:
        ord_value = ((num) % ALPHA) + ORD_A - 1
        if ord_value == ORD_A - 1:
            return_string = 'Z' + return_string
            num -= 1
        else:
            return_string = chr(ord_value) + return_string
        num = num // ALPHA
    return return_string

# Pre:  R followed by nums and C followed by nums in a string
# Post: the converted alpha version of the column is returned
def get_col(input_given):
    c_index = input_given.find("C")
    num = int(input_given[c_index+1:])
    return (convert_to_alpha(num))

# Pre:  The full input given
# Post: then string version of the row integer
def get_row(input_given):
    c_index = input_given.find("C")
    num = (input_given[1:c_index])
    return (num)

# Pre:  
# Post: sends out the corresponding location
def main():
    row_col = input()
    return_string = ''
    while row_col != TERMINATE:
        col = get_col(row_col) #get the string version of the col
        row = get_row(row_col) #get the row number
        return_string = col + row
        print(return_string)
        row_col = input()

if __name__ == "__main__":
    for i in range(1, 82):
        print(i, convert_to_alpha(i))
#$    main()
