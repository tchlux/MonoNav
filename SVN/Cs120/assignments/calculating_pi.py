import math



def calculate_pi(number_of_sides):
    degrees_in_circle = 360
    radius = 1
    theta_for_large_triangle = degrees_in_circle / number_of_sides
    theta_for_small_triangle = theta_for_large_triangle / 2
    half_side_length = radius * math.sin(math.radians(theta_for_small_triangle))
    circumference = 2 * half_side_length * number_of_sides
    pi = circumference / 2 * radius
    return pi


number_of_sides = 8

print("If a polygon has", number_of_sides, "sides, then pi is approximately", calculate_pi(number_of_sides),"!!! woo hoo, I think..")
