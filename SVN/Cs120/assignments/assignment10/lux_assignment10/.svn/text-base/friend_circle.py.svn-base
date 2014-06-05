import math
import turtle
import sys

#this function calculates the location of a string along a circle using a already initialized turtle object
#pre: the locatoin of the name in index, the set turn angle for the object, the set forward distance for the object, the window height as originally calculated, and the turtle object to use
#post: the x,y location around the edge of the created shape using standard variables(forward, turn)
def return_location(location, turn_angle, forward_distance, window_height, temp):
    temp.pu()
    temp.seth(0)
    turtle.tracer(10000,0)
    temp.goto(0, -window_height/2)
    for i in range(location):
        temp.left(turn_angle)
        temp.forward(forward_distance)
    (x,y) = temp.pos()
    return (x,y)

#this is a class used to put string values from a list around the edge of a shape that has the number of sides as there are items in the list, it uses the turtle module to do this
class Friend_circle:

#this method seemed to be needed? even though it has no parameters
    def __init__(self):
        pass

#this method is used to find the radius and circumference of the largest possible circle in the window height
#pre: the object, and the window height
#post: object .circumference and .radius are set to representative numbers
    def radius_and_circumference(self, window_height):
        self.circumference = ((window_height)*3.14159265359)
        self.radius = (window_height/2)

#this method finds the angle turned and forward distance for an object given a list length
#pre: the list length is an integer
#post: .turn_angle and .forward_distance are set to representative numbers
    def find_loop_angle_and_distance(self, list_length):
        self.turn_angle = (360 / list_length)
        self.forward_distance = (self.circumference / list_length)

#this method draws the names in a list along the perimeter and then calls the method that draws the lines between connected strings
#pre: the list of friends to be put around the edge and the list of everything to find out which friends are connected(mutual)
#post: the turtle window is opened and the shape is drawn
    def draw_friend_circle(self, friends_list, name_list):
        circle_maker = turtle.Turtle()
        circle_maker.speed(0)
        turtle.tracer(10000,0)
        window_height = turtle.window_height()
        self.radius_and_circumference(window_height)
        self.find_loop_angle_and_distance(len(friends_list))
        circle_maker.pu()
        circle_maker.goto(0, -window_height/2)
        for name in friends_list:
            circle_maker.write(name, False, align="right")
            circle_maker.left(self.turn_angle)
            circle_maker.forward(self.forward_distance)
        self.find_connections(friends_list, name_list, window_height)
        turtle.mainloop()

#this method finds out if two friends are mutual and in the user's friend list, the draws a line connecting the two friends that know eachother
#pre: the list of friends, the full list of names, and the window height (list, list, int)
    def find_connections(self, friends_list, name_list, window_height):
        line_maker = turtle.Turtle()
        line_maker.speed(0)
        turtle.tracer(10000,0)
        self.radius_and_circumference(window_height)
        self.find_loop_angle_and_distance(len(friends_list))
        for tup in name_list:
            if (tup[0] in friends_list) and (tup[1] in friends_list):
                self.draw_the_lines(window_height, friends_list, tup, line_maker)

#this method moves the turtle and officially draws the lines given the start and end locations
#pre: the window height, friends list, the current two friends, the line maker (int, list, tuple, turtle object)
    def draw_the_lines(self, window_height, friends_list, tup, line_maker):
        line_maker.pu()
        location_one = friends_list.index(tup[0])
        location_two = friends_list.index(tup[1])
        (start_x, start_y) = return_location(location_one, self.turn_angle, self.forward_distance, window_height, line_maker)
        (end_x, end_y) = return_location(location_two, self.turn_angle, self.forward_distance, window_height, line_maker)
        line_maker.goto(start_x, start_y)
        line_maker.pd()
        line_maker.goto(end_x,end_y)

