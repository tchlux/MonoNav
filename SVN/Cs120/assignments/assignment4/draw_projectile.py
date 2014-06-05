import turtle
import math
canonball = turtle.Turtle()
monkey = turtle.Turtle()


# all velocities are per one unit time (one run of the loop)

initial_x_velocity = 20
initial_y_velocity = 10
# 20 and 10 respectively return a hit combined with all other hit categories
# cut on wind resistance to see a miss (that is the var "constant")

gravity = 2
# 2 is good test data that returns a hit

wind_on_the_x = 0
# 0
# any other number may affect the hit but it works on both turtles

wind_on_the_y = 0
# 0
# any other number may affect the hit but it works on both turtles

ground = -10
sky = 100
max_number_of_time_units = 30

other_turtle_initial_x = 200
# 200 is test data that returns a hit
# he's gotta be pretty far away

other_turtle_initial_y = 100
# 100 is test data that returns a hit
# he's in a tree right??

constant = 0
# the constant is for wind resistance
# -.02 is a good small object wind resistance that returns a miss
# wind resistance for our purposes can be calculated using the formula 
# F(resistance)= -constant (velocity)


# this calculates the wind resistance on the horizontal using a given velocity and constant
# pre: real number input
# post: the wind resistance on the x-axis
def calculate_x_wind_resistance(current_x_velocity,constant):
    x_resistance = constant * (current_x_velocity)
    return x_resistance


# this calculates the wind resistance on the vertical using a given velocity and constant
# pre: real number input
# post: the wind resistance on the y-axis
def calculate_y_wind_resistance(current_y_velocity,constant):
    y_resistance = constant * (current_y_velocity)
    return y_resistance


# this function gives the shooter a little room to miss and still give him credit
# pre: numbers that are real
# post: a little bit of a skewed idea of a hit
## if you want to change how close they have to come, change the hypot < NUMBER
def hit_magnet(cannon_x, cannon_y, monkey_x, monkey_y, flyguy, monkey_response, hit):
    if hit == 1:
        return(hit)
    else:
        x_distance = (((cannon_x - monkey_x)**2)**(1/2))
        y_distance = (((cannon_y - monkey_y)**2)**(1/2))
        hypot = ((x_distance)**2 + (y_distance)**2) ** (1/2)
        # this is where the idea of a monkey with a 10 unit long body comes into play
        if hypot < 5:
            hit = 1
            monkey_response.write("Ow!   ",False, align="right")
            return(hit)
        else:
            return(hit)

# this will move the established turtle(deamed flyguy) through the trajectory based on the provided variables of x & y velocity and resistance factors
# pre:  the variables all need to be real
# post: the arch based on the given factors is produced in the turtle module
def calculate_movement_of_projectile(init_x,init_y, grav, wind_x, wind_y, flyguy, constant, other_turtle, other_turtle_x, other_turtle_y, ground, sky, max_number_of_time_units):
    hit = 0
    other_turtle_x_velocity = 0
    other_turtle_y_velocity = 0
    constant_two = constant * 3
    other_turtle.penup()
    other_turtle.goto(other_turtle_x, other_turtle_y)
    other_turtle.pendown()
    time_passed = 0
    (x,y) = flyguy.position()
    for i in range (0,max_number_of_time_units):
        # this ends the loop if the monkey is hit
        if hit == 1:
            pass
        else:
        # this if statement runs the program until ground or sky is hit
            if sky > (y) > ground:
                other_turtle_y_velocity = other_turtle_y_velocity - grav + wind_y + calculate_y_wind_resistance(other_turtle_y_velocity, constant_two)
                other_turtle_x_velocity = other_turtle_x_velocity + wind_x  + calculate_x_wind_resistance(other_turtle_x_velocity, constant_two)
                other_turtle_x = other_turtle_x + other_turtle_x_velocity
                other_turtle_y = other_turtle_y + other_turtle_y_velocity
                other_turtle.goto(other_turtle_x,other_turtle_y)
                init_x = init_x + wind_x + calculate_x_wind_resistance(init_x,constant)
                init_y = init_y - grav + wind_y + calculate_y_wind_resistance(init_y,constant)
                flyguy.goto((x + init_x),(y + init_y))
                time_passed = time_passed + 1
                (x,y) = flyguy.position()
                #this next function determines hit or miss
                hit = hit_magnet(x, y, other_turtle_x, other_turtle_y, flyguy, other_turtle, hit)

    # this if statement says whether or not the monkey was hit
    if hit == 1:
        flyguy.write("    I definitely got him!!")
    else:
        flyguy.write("Darn I missed")
    turtle.mainloop()
    return(time_passed)

calculate_movement_of_projectile(initial_x_velocity, initial_y_velocity, gravity, wind_on_the_x, wind_on_the_y, canonball, constant, monkey, other_turtle_initial_x, other_turtle_initial_y, ground, sky, max_number_of_time_units)
