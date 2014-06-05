# Roanoke College: Team 35
# prob11.py
import sys, math

RADIUS = 2

def get_movement():
    line = sys.stdin.readline().split()
    radians = [[int(num) for num in el.split("|")] for el in line]
    return(sum([el[0]*el[1] for el in radians]))
    
def move(feet, clockwise):
    radians = feet / 2 #feet traveled around circumference of circle that center travels on
    movement = (1 - math.cos(radians), 1 - math.sin(radians))
    print(movement)
    return(movement)

commands = int(sys.stdin.readline())
center = (0.0,0.0)
for i in range(commands):
    left_wheel_radians  = get_movement()
    right_wheel_radians = get_movement()
    center += move(left_wheel_radians,  False)
    center += move(right_wheel_radians, True)
    print(center[0], center[1])
