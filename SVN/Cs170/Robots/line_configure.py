import math
from wall import Wall
from point_list import PointList
import turtle

#ALL CALCULATIONS OF DISTANCE WILL BE DONE IN TERMS OF PIXELS

LINE_THRESHOLD = 3 #This number determines how high the magnitude of
                   #change in slope must be for the spot to be
                   #considered at vertex (higher is more selective)

DEGREE_THRESHOLD = 10 #This determines how close two points have to be
                      #to eachother to be considered the same vertice

MINIMAL_POINT_OCCURANCE = 4 #This determains the minimal number of
                            #occurances of a point before it will be
                            #used in the final drawing of lines

class LineConfigure:
    #Method:Constructor, this method initializes all attributes of the
    #       LineConfigure class
    #Pre:   Two lists of data from sensors, an offset between the
    #       two, and the variance lists for the two lists given
    #Att.'s:None, they're initialized here
    #Post:  Attributes are initialized
    def __init__(self, s_list1, s_list2, offset, angle, turtle):
        self.turtle = turtle
        self.turtle.pu()
        self.turtle.ht()
        self.degrees_per_data_point = angle/offset
        self.s_list1 = s_list1
        self.s_list2 = s_list2
        self.offset1_to_2 = offset
        self.sense_ang = angle
        self.point_list = PointList(DEGREE_THRESHOLD)
        self.var_list1 = []
        self.var_list2 = []
        self.var_var1 = [] #This list will hold the variance of
                           #var_list1
        self.var_var2 = [] #This list will hold the variance of
                           #var_list2
                           #also known as the 2nd derrivative of the
                           #sensor data
        self.append_lists_of_vars()

    #Method:This will add the modified sensor data to the sensors list
    #       and update the variance lists as well
    #Pre:   Two lists will be given
    #Att.'s:self.s_list1 (type=List)
    #       self.s_list2 (type=List)
    #       self.append_lists_of_vars (type=Method)
    #Post:  the self.sensors lists will be updated
    def add_sensor_data_to_list(self, s_list1, s_list2):
        for index in range(len(self.s_list1),len(s_list1)):
            self.s_list1.append(s_list1[index])
        for index in range(len(self.s_list2),len(s_list2)):
            self.s_list2.append(s_list2[index])
        self.append_lists_of_vars()

    #Method:This method will update the variance lists after being
    #       called by self.add_sensor_data_to_list
    #Pre:   None need be given
    #Att.'s:self.var_list1 (type=List)
    #       self.var_list2 (type=List)
    #       self.s_list1 (type=List)
    #       self.s_list2 (type=List)
    #Post:  The list of variances is updated
    def append_lists_of_vars(self):
        for index in range(len(self.var_list1),len(self.s_list1)):
            self.var_list1.append(self.s_list1[index] -
                                  self.s_list1[index-1])
        for index in range(len(self.var_list2),len(self.s_list2)):
            self.var_list2.append(self.s_list2[index] -
                                  self.s_list2[index-1])
        self.append_var_var_lists()

    #Method:This method will calculate the list of change in variance
    #Pre:   The method is called
    #Att.'s:self.var_list1 (type=List)
    #       self.var_list2 (type=List)
    #Post:  The self.var_var lists are created
    def append_var_var_lists(self):
        for index in range(len(self.var_var1),len(self.var_list1)):
            self.var_var1.append(self.var_list1[index] -
                                  self.var_list1[index-1])
        for index in range(len(self.var_var2),len(self.var_list2)):
            self.var_var2.append(self.var_list2[index] -
                                  self.var_list2[index-1])


    #Method:This method refines two lists given by a factor given
    #Pre:   The two lists as type=List and the factor to refine by is
    #       given as an Integer 
    #Att.'s:None of the class
    #Post:  the refined lists are created and returned
    def refine_lists(self, list1, list2, refine_factor):
        refined_list1 = []
        refined_list2 = []
        for i in range(0,len(list_1),refine_factor):
            refined_list1.append((list1[i]+list1[i-1])/2)
        for i in range(0,len(list2),refine_factor):
            refined_list2.append((list2[i]+list2[i-1])/2)
        return refined_list1, refined_list2

    #Method:This method will find all points to be used as vertices in
    #       the line building project based on a given var_var list
    #Pre:   the var_var list is built
    #Att.'s:None requred
    #Post:  The list of points in terms of their index into the list
    #       are returned
    def find_verts_for_lines(self, var_var_list):
        points = []
        points.append(0)
        for i in range(1,len(var_var_list)):
            if abs(var_var_list[i]) > LINE_THRESHOLD:
                points.append(i-1)
        return points

    #Method:This method will return the x,y and the degree of an
    #       indexed location into a list
    #Pre:   A list of distances and the index into the list to be
    #       accessed
    #Att's: self.degrees_per_data_point (type=Integer)
    #       self.sense_ang (type=Integer)
    #Post:  The tuple (x,y) is returned along with the degree to that
    #       point
    def return_x_y_coordinates(self, lst, index_into_list):
        hypot = lst[index_into_list]
        degree = -1 * (index_into_list * self.degrees_per_data_point - self.sense_ang/4)
        x = hypot * math.sin(math.radians(degree))
        y = hypot * math.cos(math.radians(degree))
        return (x,y), degree

    #Method:This method will insert the points into self.point_list
    #Pre:   Called
    #Att's: self.point_list (type=PointList)
    #       self.find_verts_for_lines (type=Method)
    #       self.return_x_y_coordinates (type=Method)
    #       self.s_list1 (type=List)
    #Post:  The point is added to the list
    def check_points(self):
        indices1 = self.find_verts_for_lines(self.var_var1)
        for i in range(len(indices1)):
            new_point, degree = self.return_x_y_coordinates(self.s_list1, indices1[i])
            self.point_list.insert(new_point, degree%360)
        indices2 = self.find_verts_for_lines(self.var_var2)
        for i in range(len(indices2)):
            new_point, degree = self.return_x_y_coordinates(self.s_list2, indices2[i])
            self.point_list.insert(new_point, degree%360)

    #Method:This method will draw all of the lines
    #Pre:   The method is called
    #Att's: self.check_points (type=Method)
    #       self.point_list (type=PointList)
    #Post:  The lines are drawn to a turtle canvas
    def construct_lines(self):
        self.check_points()
        for point in self.point_list:
            if point.next != None:
                self.turtle.goto(point.point)
                self.turtle.pd()
                self.turtle.goto(point.next.point)
                self.turtle.pu()
            else:
                self.turtle.goto(point.point)
                self.turtle.pd()
                self.turtle.goto(self.point_list.first.point)
                self.turtle.pu()
                
                



#Method:This is for testing purposes
if __name__ == "__main__":
    import turtle
    s_list1 = [i**2 for i in range(-10,10)]
    s_list2 = [i**2 for i in range(5,25)]
    offset = 5
    angle = 120
    a = LineConfigure(s_list1, s_list2, offset, angle)
    a.construct_lines()
    turtle.mainloop()
