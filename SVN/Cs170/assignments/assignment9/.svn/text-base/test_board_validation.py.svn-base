import sudoku
puzzle = sudoku.Sudoku("puzzle1.txt")
row = [1,2,3,4,5,6,7,8,1] #No 9
col = [2,3,4,6,7,8,9,6,4] #No 1 & 5
box = [1,3,4,5,7,8,9,4,5] #No 2 & 6

valid_row_value = 9
invalid_row_value = 8
valid_col_value = 5
invalid_col_value = 4
valid_box_value = 2
invalid_box_value = 5
#These are valid & invalid row/col/box values


###########These two tests will test the _check_valid_row method
##Test 1##
#This will test _check_valid_row given a valid value
print("Test 1:", puzzle._check_valid_row(row, valid_row_value))
print("Expected value: True")

##Test 2##
#This will test _check_valid_row given a invalid value
print("Test 2", puzzle._check_valid_row(row, invalid_row_value))

print("Expected value: False")


###########These two tests will test the _check_valid_col method
##Test 3##
#This will test _check_valid_col given a valid value
print("Test 3:", puzzle._check_valid_col(col, valid_col_value))
print("Expected value: True")

##Test 4##
#This will test _check_valid_row given a invalid value
print("Test 4:", puzzle._check_valid_col(col, invalid_col_value))
print("Expected value: False")


###########These two tests will test the _check_valid_box method
##Test 5##
#This will test _check_valid_box given a valid value
print("Test 5:", puzzle._check_valid_box(box, valid_box_value))

print("Expected value: True")

##Test 6##
#This will test _check_valid_box given a invalid value
print("Test 6:",puzzle._check_valid_box(box, invalid_box_value))
print("Expected value: False")
