import turtle
import math
import random
missle = turtle.Turtle()
unlucky = turtle.Turtle()

unlucky_initial_x_position = random.random()*(-300)
unlucky_initial_y_position = random.random()*200
unlucky_initial_x_velocity = random.random()*15
unlucky_initial_y_velocity = random.random()*10
gravity_ratio = -1
wind_on_the_x = (random.random()*5) * ((-1)**(int(random.random())))
wind_on_the_y = (random.random()*5) * ((-1)**(int(random.random())))
missle_initial_x = -300
missle_initial_y = -300
wind_resistance_for_unlucky = 0
wind_resistance_for_missle = 0
max_missle_speed_on_one_axis = 30
time_passed = 15

# this function calculates wind resistance for a given object on one axis
# pre:  the current axis velocity of the object should be given and also a constant that 
#         can represent the object's wind resistance in a ratio
# post: it returns the resistance on that axis
def calculate_wind_resistance(current_velocity, wr_constant):
    resistance = (wr_constant * current_velocity) * (-1)
    return resistance


# this function uses the best time calculated by another function to calculate how to get to
#      that position in the specified amount of time from a start point
# pre:  this function takes all prenamed values
# post: the initial x and y velocities for the interceptor is calculated
def calculate_intercept_velocity(unlucky_x_position, unlucky_y_position, time_passed, max_missle_speed_on_one_axis, wind_resistance_for_missle, wind_on_the_x, wind_on_the_y, missle_initial_x, missle_initial_y):

    x_difference = unlucky_x_position - missle_initial_x
    y_difference = unlucky_y_position - missle_initial_y
    average_x_velocity = x_difference / time_passed
    average_y_velocity = y_difference / time_passed
    missle_initial_x_velocity = ((x_difference - time_passed * (wind_on_the_x + calculate_wind_resistance(average_x_velocity, wind_resistance_for_missle))) / time_passed)
    missle_initial_y_velocity = ((y_difference - time_passed * (wind_on_the_y + calculate_wind_resistance(average_y_velocity, wind_resistance_for_missle))) / time_passed)
    print(' x,y difference', x_difference,y_difference)
    print(' wind on the x,y --> ', wind_on_the_x, wind_on_the_y)

    print(' average x velocity needed', average_x_velocity)
    print(' average y velocity needed ', average_y_velocity)
    hypot = ((missle_initial_x_velocity)**2 + (missle_initial_y_velocity)**2)**(1/2)
    print('missle max obtainable speed', max_missle_speed_on_one_axis)
    print(' missle firing at', hypot, "units per second in")
    print("                                                        3")
    print('                                   2')
    print('             1')
    print(' bogey going down')
    return (missle_initial_x_velocity, missle_initial_y_velocity)

# this function runs the location of the object based on initial conditions over an indefinite period of time to calculate what distance is ideal for the missle to be firing at based off of a maximum speed for the interceptor and the specific amount of time passed before the object is at that location
#  pre:  all precalculated values and variable names are inputed
#  post:  the ideal time to strike the object is calculated
def calculate_best_location_of_unlucky(unlucky_initial_x_position, 
unlucky_initial_y_position, unlucky_initial_x_velocity, unlucky_initial_y_velocity, 
gravity_ratio, wind_resistance_for_unlucky, wind_on_the_x, wind_on_the_y, time_passed, 
max_missle_speed_on_one_axis):
    i = 0
    returning_value = 0
    unlucky_x_position = unlucky_initial_x_position
    unlucky_y_position = unlucky_initial_y_position
    while (returning_value == 0) and i < 1000:
        i += 1
        (unlucky_x_position, unlucky_y_position, time_passed, returning_value) = calculate_best_location_of_unlucky_test(unlucky_x_position, unlucky_y_position, unlucky_initial_x_velocity, unlucky_initial_y_velocity, gravity_ratio, wind_resistance_for_unlucky, wind_on_the_x, wind_on_the_y, time_passed, max_missle_speed_on_one_axis, i)
    if returning_value == 1:
        return(unlucky_x_position, unlucky_y_position, time_passed)
    else:
        print('an error occured in the calc_best_loc_unluck fxn #abbreviations used')
        print('most likely the max missle speed was less than the object speed')
        print('')
        return ()


def calculate_best_location_of_unlucky_test(unlucky_x_position, unlucky_y_position, unlucky_initial_x_velocity, unlucky_initial_y_velocity, gravity_ratio, wind_resistance_for_unlucky, wind_on_the_x, wind_on_the_y, time_passed, max_missle_speed_on_one_axis, i):
    unlucky_x_position = (unlucky_x_position + unlucky_initial_x_velocity + 
    wind_on_the_x)
    unlucky_y_position = (unlucky_y_position + unlucky_initial_y_velocity + 
    wind_on_the_y)
    unlucky_initial_x_velocity += (calculate_wind_resistance(unlucky_initial_x_velocity, wind_resistance_for_unlucky))
    unlucky_initial_y_velocity += (calculate_wind_resistance(unlucky_initial_y_velocity, wind_resistance_for_unlucky) + gravity_ratio)
    x_distance = (((unlucky_x_position - missle_initial_x)**2)**(1/2)) + (i * wind_on_the_x)
    y_distance = (((unlucky_y_position - missle_initial_y)**2)**(1/2)) + (i * wind_on_the_y) + (i * gravity_ratio)
    hypot = ((x_distance)**2 + (y_distance)**2) ** (1/2)
    if hypot < (i*(max_missle_speed_on_one_axis)):
        print("The object will be intercepted in", i,"units")
        time_passed = i
        returning_value = 1
    elif hypot > (i*(max_missle_speed_on_one_axis)):
        print(" distance is too great at t -", i,"units")
        returning_value = 0
    elif hypot == (i*(max_missle_speed_on_one_axis)):
        print('somehow the hypot equals exactly the missle speed over time units!!')
        print(' this is totally super duper rare!! :P')
        returning_value = 0
    else:
        print(' there has been an error on ..unlucky_test function')
    return(unlucky_x_position, unlucky_y_position, time_passed, returning_value)


#this function will be the main run with the for loops and velocities and positions
# pre: all the variables are real
# post: the turtles and graphics move
def goto_and_run_the_loops_with_calculated_input(missle, missle_x, missle_y, missle_x_velocity, missle_y_velocity, wind_resistance_for_missle, unlucky, unlucky_x, unlucky_y, unlucky_x_velocity, unlucky_y_velocity, wind_resistance_for_unlucky, wind_on_the_x, wind_on_the_y, gravity_ratio, time_passed):
    hit = 0
    missle.penup()
    unlucky.penup()
    missle.goto(missle_x, missle_y)
    unlucky.goto(unlucky_x, unlucky_y)
    missle.pendown()
    unlucky.pendown()
    for i in range (time_passed):
        missle_x += (missle_x_velocity + wind_on_the_x)
        missle_y += (missle_y_velocity + wind_on_the_y)
        unlucky_x += (unlucky_x_velocity + wind_on_the_x + calculate_wind_resistance(unlucky_x_velocity, wind_resistance_for_unlucky))
        unlucky_y += (unlucky_y_velocity + wind_on_the_y + calculate_wind_resistance(unlucky_y_velocity, wind_resistance_for_unlucky))
        missle.goto(missle_x, missle_y)
        unlucky.goto(unlucky_x, unlucky_y)
        missle_x_velocity += calculate_wind_resistance(missle_x_velocity, wind_resistance_for_missle)
        missle_y_velocity += (calculate_wind_resistance(missle_y_velocity, wind_resistance_for_missle) + gravity_ratio)
        unlucky_x_velocity += calculate_wind_resistance(unlucky_x_velocity, wind_resistance_for_unlucky)
        unlucky_y_velocity += (calculate_wind_resistance(unlucky_y_velocity, wind_resistance_for_unlucky) + gravity_ratio)
        hit = hit_magnet(missle_x, missle_y, unlucky_x, unlucky_y, unlucky, hit)
    # this if statement says whether or not the unlucky was hit
    if hit == 1:
        missle.write("    Intercepted")
    else:
        missle.write("Miss")
    turtle.mainloop()

# pre: numbers that are real
# post: a little bit of a skewed idea of a hit
## if you want to change how close they have to come, change the hypot < NUMBER
def hit_magnet(missle_x, missle_y, unlucky_x, unlucky_y, unlucky, hit):
    if hit == 1:
        return(hit)
    else:
        x_distance = (((missle_x - unlucky_x)**2)**(1/2))
        y_distance = (((missle_y - unlucky_y)**2)**(1/2))
        hypot = ((x_distance)**2 + (y_distance)**2) ** (1/2)
        # this is where the idea of a unlucky with a 10 unit long body comes into play
        if hypot < 5:
            hit = 1
            unlucky.write("boooomm!!      ",False, align="right")
            return(hit)
        else:
            return(hit)

# this function calls all the calculate value functions and sends them to the movement fxn
# pre: all the variable names, some get renamed, sorry for the inconvenience
# post: this essentially is a middle of the pyramid program operator
def begin_movement_of_turtles(unlucky_initial_x_position, unlucky_initial_y_position, unlucky_initial_x_velocity, unlucky_initial_y_velocity, gravity_ratio, wind_on_the_x, wind_on_the_Y, missle_initial_x, missle_initial_y, wind_resistance_for_unlucky, wind_resistance_for_missle, max_missle_speed_on_one_axis, time_passed, missle, unlucky):

    (unlucky_x_position, unlucky_y_position, time_passed) = calculate_best_location_of_unlucky(unlucky_initial_x_position, unlucky_initial_y_position, unlucky_initial_x_velocity, unlucky_initial_y_velocity, gravity_ratio, wind_resistance_for_unlucky, wind_on_the_x, wind_on_the_y, time_passed, max_missle_speed_on_one_axis)
    (missle_initial_x_velocity, missle_initial_y_velocity) = calculate_intercept_velocity(unlucky_x_position, unlucky_y_position, time_passed, max_missle_speed_on_one_axis, wind_resistance_for_missle, wind_on_the_x, wind_on_the_y, missle_initial_x, missle_initial_y)
    missle_x = missle_initial_x
    missle_y = missle_initial_y
    unlucky_x = unlucky_initial_x_position
    unlucky_y = unlucky_initial_y_position
    missle_x_velocity = missle_initial_x_velocity
    missle_y_velocity = missle_initial_y_velocity
    unlucky_x_velocity = unlucky_initial_x_velocity
    unlucky_y_velocity = unlucky_initial_y_velocity
    goto_and_run_the_loops_with_calculated_input(missle, missle_x, missle_y, missle_x_velocity, missle_y_velocity, wind_resistance_for_missle, unlucky, unlucky_x, unlucky_y, unlucky_x_velocity, unlucky_y_velocity, wind_resistance_for_unlucky, wind_on_the_x, wind_on_the_y, gravity_ratio, time_passed)





begin_movement_of_turtles(unlucky_initial_x_position, unlucky_initial_y_position, unlucky_initial_x_velocity, unlucky_initial_y_velocity, gravity_ratio, wind_on_the_x, wind_on_the_y, missle_initial_x, missle_initial_y, wind_resistance_for_unlucky, wind_resistance_for_missle, max_missle_speed_on_one_axis, time_passed, missle, unlucky)



