import turtle
import math
import random

loopy = turtle.Turtle()
max_number_of_dots = 300



def make_specified_area_test_triangle(triangle_turtle, max_i):
    a_x = -100
    a_y = -100
    b_x = 200
    b_y = -100
    c_x = -100
    c_y = 200
    print("area of this triangle is 45,000")
    triangle_turtle.penup()
    triangle_turtle.goto(a_x,a_y)
    triangle_turtle.pendown()
    triangle_turtle.goto(b_x,b_y)
    triangle_turtle.goto(c_x,c_y)
    triangle_turtle.goto(a_x,a_y)
    counter = make_random_dot(a_x, a_y, b_x, b_y, c_x, c_y, max_i)
    return counter

# this function draws random triangle
# pre: the turtle that is used as input has to already be initialized
# post: a random triangle is drawn, there is a chance that it is very small but it should
#      not exceede the sides of the screen, the multiplyers are arbitrary
def make_random_triangle(triangle_turtle, max_i, which_operation):
    a_x = (int(random.random() * 100) * (-1)) * 3
    a_y = (int(random.random() * 100) * 3)
    b_x = (int(random.random() * 100) * 3)
    b_y = (int(random.random() * 100) * (-1)) * 3
    c_x = (int(random.random() * 100) * 3)
    c_y = (int(random.random() * 100) * 3)
    #approximate_area_of_triangle = find_random_triangle_area(a_x,a_y,b_x,b_y,c_x,c_y)
    #print('The calculated area of triangle is ', approximate_area_of_triangle)
    triangle_turtle.speed(0)
    triangle_turtle.penup()
    triangle_turtle.goto(a_x, a_y)
    triangle_turtle.pendown()
    triangle_turtle.goto(b_x, b_y)
    triangle_turtle.goto(c_x, c_y)
    triangle_turtle.goto(a_x, a_y)
    if which_operation == 0:
        counter = make_random_dot(a_x, a_y, b_x, b_y, c_x, c_y, max_i)
        return counter
    elif which_operation == 1:
        counter = triangle_and_screen_filler(a_x, a_y, b_x, b_y, c_x, c_y)
        #print("The calculated area of the triangle is", approx_area_of_triangle)
        return counter
    else:
        print('There was an incorrect input into the which_operation category')

######################################################################
###### THIS CODE DOES NOT PROPERLY CALCULATE AREA, DIRECTION IS NOT ##
######################## ACCURATELY SPECIFIED ########################
######################################################################
# this function finds the area of a triangle given the vertices
# pre: all of the points must be correct
# post: the area is returned
def find_random_triangle_area(a_x,a_y,b_x,b_y,c_x,c_y):
    side_a_length = ((b_x - c_x)**2 + (b_y - c_y)**2)**(1/2)
    side_b_length = ((c_x - a_x)**2 + (c_y - a_y)**2)**(1/2)
    side_c_length = ((a_x - b_x)**2 + (a_y - b_y)**2)**(1/2)
    if side_a_length > side_b_length and side_a_length > side_c_length:
        half_way_point_x = (b_x - c_x) / 2
        half_way_point_y = (b_y - c_y) / 2
        side_d_length = ((half_way_point_x - a_x)**2 + (half_way_point_y - a_y)**2)**(1/2)
        triangle_area = (side_a_length / 2) * side_d_length
    elif side_b_length > side_c_length and side_b_length > side_a_length:
        half_way_point_x = (c_x - a_x) / 2
        half_way_point_y = (c_y - a_y) / 2
        side_d_length = ((half_way_point_x - b_x)**2 + (half_way_point_y - b_y)**2)**(1/2)
        triangle_area = (side_a_length / 2) * side_d_length
    elif side_c_length > side_a_length and side_c_length > side_b_length:
        half_way_point_x = (a_x - b_x) / 2
        half_way_point_y = (a_y - b_y) / 2
        side_d_length = ((half_way_point_x - c_x)**2 + (half_way_point_y - c_y)**2)**(1/2)
        triangle_area = (side_a_length / 2) * side_d_length
    else:
        print("an error has occured in the find_random_triangle_area function, no side is longest maybe?")
    return triangle_area
########################################################################
########################################################################


# this definition calls a random dot and then calls a judgement on the location of the dot
# pre: the input values must valid and accurate vertices
# post: all the random dots are made and colors are changed for ones in the triangle
def make_random_dot(a_x, a_y, b_x, b_y, c_x, c_y, max_i):
    counter = 0
    for i in range (1, max_i + 1):
        x = 0
        y = 1
        p_x = make_random_value_in_window(x)
        p_y = make_random_value_in_window(y)
        turtle.penup()
        turtle.tracer(200,2)
        turtle.speed(0)
        turtle.setpos(p_x,p_y)
        if test_if_dot_is_inside(a_x, a_y, b_x, b_y, c_x, c_y, p_x, p_y) == 0:
            counter = counter + 1
            turtle.dot(5,"red")
        else:
            turtle.dot(4)
    return counter


# this is the function called to make a random dot, simply to promote readability
# pre: no necessary input or pre conditions
# post: a random number that can be used as a coordinate value inside the turtle window
def make_random_value_in_window(x_or_y):
    half_window_height = (turtle.window_height()) / 2
    half_window_width = (turtle.window_width()) / 2
    if x_or_y == 0:
        rando = int(random.random() * half_window_width) * (-1) ** round(random.random())
    elif x_or_y == 1:
        rando = int(random.random() * half_window_height) * (-1) ** round(random.random())
    else:
        print("there was an incorrect input into make_random_value_in_window x_or_y")
    return rando


# this calls a function that tests to see if the dot is on the correct side of one wall
#     of the triangle and then prints a colored dot if it is inside all walls
# pre: the vertices and the point coordinates must all be accurate and real numbers
# post: the corresponding color dot is printed
def test_if_dot_is_inside(a_x, a_y, b_x, b_y, c_x, c_y, p_x, p_y):
    yes_no = 2
    a = compare_dot_and_vert(a_x, a_y, b_x, b_y, c_x, c_y, p_x, p_y)
    b = compare_dot_and_vert(b_x, b_y, c_x, c_y, a_x, a_y, p_x, p_y)
    c = compare_dot_and_vert(c_x, c_y, a_x, a_y, b_x, b_y, p_x, p_y)
    if (a + b + c) == 0:
        yes_no = 0
    else:
        yes_no = 1
    return yes_no

#this is the function that does all the hard work, it is called to test if the dot is on the
#  inside of one line of the triangle, it's called three times to reference each side
# pre: all the vertices are accurate, as well as the point
# post: a 0 is returned for a pass(inside) and a 1 is returned for a fail(ouside)
def compare_dot_and_vert(first_vert_x, first_vert_y, second_vert_x, second_vert_y,
third_vert_x, third_vert_y, point_x, point_y):
    yes_no = 2
    first_second_x_diff = first_vert_x - second_vert_x
    first_second_y_diff = first_vert_y - second_vert_y
    first_point_x_diff = first_vert_x - point_x
    first_point_y_diff = first_vert_y - point_y
    first_third_x_diff = first_vert_x - third_vert_x
    first_third_y_diff = first_vert_y - third_vert_y
    s_for_point = first_second_x_diff * first_point_y_diff - first_second_y_diff * first_point_x_diff
    s_for_vert = first_second_x_diff * first_third_y_diff - first_second_y_diff * first_third_x_diff
    comp_value = s_for_point / s_for_vert
    if comp_value > 0:
        yes_no = 0
    else:
        yes_no = 1
    return yes_no

# this is the definition sends the designated turtle to all pixels on the screen and tests
#  whether or not they land inside the triangle
# pre: the coordinates of the triangle are defined and accurate
# post: the triangle is filled in with black
def triangle_and_screen_filler(a_x, a_y, b_x, b_y, c_x, c_y):
    counter = 0
    filler = turtle.Turtle()
    window_height = int(turtle.window_height())
    window_width = int(turtle.window_width())
    half_window_height = int(window_height / 2)
    half_window_width = int(window_width / 2)
    window_area = int(window_height * window_width)
    turtle.tracer(window_area//25, 2)
    filler.penup()
    filler.goto((-1)*half_window_width, half_window_height)
    filler.pendown()
    for i in range(half_window_height):
        counter = counter + (one_window_width_line_filler(filler, window_width, a_x, a_y, b_x, b_y, c_x, c_y))
    return counter

# this function sends the turtle accross the window on a single pixel plain and then back
# pre: the turtle is specified, window width is accurate, triangle vertices are accurate
# post: the turtle is sent accross, down 1, and back
def one_window_width_line_filler(filler, window_width, a_x, a_y, b_x, b_y, c_x, c_y):
    counter = 0
    window_width_factor_and_jump_speed = 1
    filler.speed(0)
    filler.penup()
    for i in range ((window_width // window_width_factor_and_jump_speed) + 1):
        filler.forward(window_width_factor_and_jump_speed)
        (p_x, p_y) = filler.pos()
        if test_if_dot_is_inside(a_x, a_y, b_x, b_y, c_x, c_y, p_x, p_y) == 0:
            filler.dot(.5)
            counter = counter + 1
    filler.right(90)
    filler.forward(window_width_factor_and_jump_speed)
    filler.right(90)
    for i in range ((window_width // window_width_factor_and_jump_speed) + 1):
        filler.forward(window_width_factor_and_jump_speed)
        (p_x, p_y) = filler.pos()
        if test_if_dot_is_inside(a_x, a_y, b_x, b_y, c_x, c_y, p_x, p_y) == 0:
            filler.dot(.5)
            counter = counter + 1
    filler.left(90)
    filler.forward(window_width_factor_and_jump_speed)
    filler.left(90)
    return counter

#this function begins the random dot and area estimation formula calculation
# pre: input a pre-initialized turtle and a max number of dots
# post: a random triangle is drawn, dots are created at random, and the values of various 
#       counters are returned and used to calculate estimated area of the triangle
def run_the_whole_shebang(funny_name, max_number_of_dots):
    window_height = turtle.window_height()
    window_width = turtle.window_width()
    window_area = window_height * window_width
    counter = make_random_triangle(funny_name, max_number_of_dots, 0)
#    counter = make_specified_area_test_triangle(funny_name, max_number_of_dots)
#  un_note the previous line and note the line before it if you want a specified test tri
    ratio = counter / max_number_of_dots
    area_of_triangle = window_area * ratio
    print("window height", window_height)
    print("window width", window_width)
    print('counter, ratio:  ', counter,",", ratio)
    print("The triangle is approximately", area_of_triangle, "square units")


# this is the function that must be called if you would like to fill the triangle with dots
# pre: a pre-initialized turtle is input
# post: the random triangle is made and the turtle tests every point on the screen
def turtle_run_the_screen(funny_name):
    area = make_random_triangle(funny_name, 0, 1)
    print("the actual area of the triangle is",area)

turtle_run_the_screen(loopy)
#run_the_whole_shebang(loopy, max_number_of_dots)
turtle.mainloop()
