import turtle

# Draw the path of a projectile using turtle graphics.
# PRE: initial_position is a tuple containing the x and y coordinates
# of the projectile's initial position
#      inital_velocity is a tuple containing the projetiles initial x
# and y velocity
#      gravity is the acceleration due to gravity where a positive
# number is down
#      wind is a tuple containing the acceleration due to wind in the
# x and y directions
#      max_segments is the number of line segments in the path that
# the function draws
# POST: A path will be drawn to a window.  The turtle will be moved to
# the end of the path without changing heading.
def draw_path(initial_position, initial_velocity, gravity, wind, max_segments):
    (position_x, position_y) = initial_position
    (velocity_x, velocity_y) = initial_velocity
    (wind_x, wind_y) = wind
    turtle.penup()
    turtle.goto(position_x, position_y)
    turtle.pendown()
    window_width = turtle.window_width() / 2
    window_height = turtle.window_height() / 2
    print('window width, height', window_width, window_height)
    (turtle_x, turtle_y) = turtle.pos()
    while (window_height >= turtle_y >= -window_height) and (window_width >= turtle_x >= -window_width):
        (turtle_x, turtle_y) = turtle.pos()
        position_x += velocity_x
        position_y += velocity_y
        velocity_x += wind_x
        velocity_y += wind_y - gravity
        turtle.goto(position_x, position_y)

# Test the draw_path function by drawing a projectile from the center
# of the window with an itial velocity to the right and up, a moderate
# amount of gravity, and no wind.
# PRE: none
# POST: the function should draw a parabolic path from the origin to
# the right side of the window.
def test_draw_path():
    initial_position = (0, 0)
    initial_velocity = (10, 10)
    gravity = 1
    wind = (0, 0)
    max_segments = 50
    draw_path(initial_position, initial_velocity, gravity, wind, max_segments)

test_draw_path()
turtle.mainloop()
