# prints the correct number of spaces to make a triangle of stars
# pre: the number of rows needs to be a positive integer
# post: a particular number of spaces is printed
def number_of_spaces(number_of_rows, row):
    for i in range(number_of_rows - row):
        print(" ", end="")
    return()

# prints the correct number of stars based on the row it is on
# pre: the number is a positive integer
# post: a particular number of stars in printed
def number_of_stars(stars):
    for i in range(stars):
        print("*", end=(" "))

# this prints the stars and spaces to make a triangle_of_stars :)
# pre: number of rows must be a real positive integer
# post: a beautiful butterfly (a triangle of stars)
def print_star_triangle(number_of_rows):
    row = 0
    for i in range(number_of_rows):
        stars = i + 1
        row = i + 1
        number_of_spaces(number_of_rows, row)
        number_of_stars(stars)

        # for i in range(number_of_rows - row):
        #     print(" ", end="")
        # for i in range(number_of_stars):
        #     print("*", end=(" "))

        print("")
    return()

print_star_triangle(20)
print(" I'm a beautiful butterflY")
print("son")
