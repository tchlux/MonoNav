from line_configure import *
import random
import turtle

THRESHOLD = 12 #The amount of variance allowed between two consecutive
               #line points
SOLUTION_THRESHOLD = 60 #This only includes offsets that have occured
                        #more than this many times, and this is also
                        #the range of the weighted sum that is
                        #preformed on the final solutions  
NUMBER_OF_SOLUTIONS = 8 #This is the number of solutions (1/2 on
                        #either side of the max) that are kept for
                        #later analysis (0 means only one solution)
MAX_DIFFERENCE = 10 #This number sets the max difference between two
                    #points for them to be printed to the screen
REBUILD_COLOR = "red" #This is the color used for the map rebuild
DRAW_BEST_FIT_LINES = False #This variable is whether or not lines
                            #will be drawn 
DRAW_REBUILD_DOTS = True #This variable turns on and off all of the
                         #rebuilt dots
 
class MapBuilder:
    #Method:This will construct the necessary attributes
    #Pre:   Two lists of sensor data can be given or they can be left
    #       empty, the angle between the sensors must be given
    #Att.'s:They are all created here
    #Post:  The attributes for the class are initialized
    def __init__(self, angle_between_sensors, l1=[], l2=[],
                 sol_thresh = SOLUTION_THRESHOLD):
        self.number_of_solutions = NUMBER_OF_SOLUTIONS
        self.solution_threshold = SOLUTION_THRESHOLD
        self.sense_ang = angle_between_sensors
        self.s_list1 = l1
        self.s_list2 = l2
        self.max_match_length = 0
        self.offset1_to_2 = 0
        self.offset_list = []
        self.solution_list = []
        self.line_builder = None #This will be configured later once
                                 #the data has been gathered 
        self.turtle = turtle.Turtle()

        self.turtle.ht()
        self.turtle.pu()
        self.turtle.pencolor(REBUILD_COLOR)

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

    #Method:This method will find the places in the two lists that
    #       have extensive amounts of overlap
    #Pre:   The two lists of sensor data that the map will be built
    #       off of are given
    #       
    #Att.'s:self.find_match_likelyhood (type=Method)
    #       
    #       
    #Post:  The lists will be alligned and the most likely offset and
    #       matching sections will be recorded and sent off
    def build_map(self):
#This loop will cycle through the points in the list, this order does
#assume that the sensors are being turned to the left and that sensor
#one is on the left (in the lead)
        for d2 in range(len(self.s_list1)):
            for d1 in range(len(self.s_list2)):
                self.match_offsets(d1, d2)

        self.define_modal_offset()
        self.weighted_sum_final_offset()

        try:
            self.degrees_per_data_point = self.sense_ang/self.offset1_to_2
            self.complete_turn_degrees = len(self.s_list1)*self.degrees_per_data_point
            print(self.complete_turn_degrees)
        #This except occurs when there are not matches for possible
        #offsets due to the solution threshold, so the threshold is
        #decreased and the program is run again
        except ZeroDivisionError:
            print("Sorry, I had to try a second time because I couldn't find a match. :(")
            self.solution_threshold -= 10
            self.build_map()

    #Method:This method tests if two values are within the threshold
    #       of eachother and if they are it appends them to the offset
    #       list 
    #Pre:   The two indices are given as integers and the must be less
    #       than the length of the self.var lists and self.s_lists
    #Att.'s:self.threshold (type=Method)
    #       self.offset_list (type=List)
    #Post:  The offset list is populated
    def match_offsets(self, data1, data2):
        if self.threshold(data1, data2):
            self.offset_list.append(data2-data1)

    #Method:This method finds the most occuring offset value in the
    #       list self.offset_list
    #Pre:   The method is called and the self.offset_list has already
    #       been filled
    #Att.'s:self.offset_list (type=List)
    #       self.solution_list (type=List)
    #       self.offset1_to_2 (type=Integer)
    #       self.max_match_length (type=Integer)
    #       SOLUTION_THRESH (type=Global Variable)
    #Post:  The self.offset1_to_2 & self.max_match_length attributes
    #       are set and the possible solutions list is filled
    def define_modal_offset(self):
        self.offset_list.sort()
        count_list = []
        previous = 1
        count = 1
        for offset in self.offset_list:
            if offset != previous:
                count_list.append(count)
                previous = offset
                count = 1
            else:
                count += 1

        index = count_list.index(max(count_list))
        try:
            for i in range(-self.number_of_solutions//2,self.number_of_solutions+1):
                self.solution_list.append([self.offset_list[sum(count_list[:index+i])],count_list[index+i]])
        except IndexError:
            raise Exception("\nThe number of solutions pushed the index out of \nrange for the count_list or the self.offset_list.\nSuggested shortening of number of \nsoltuions or incresing the number of data points.")

    #Method:This method will go through the self.solution_list and
    #       get the values that are most appropriate to be used in a
    #       weighted sum of offsets based on the solution threshold
    #Pre:   The method is called
    #Att.'s:self.solution_list (type=List)
    #       self.number_of_solutions (type=Integer)
    #       self.solutions_threshold (type=Integer)
    #Post:  The best candidate for final offset is recorded
    def weighted_sum_final_offset(self):
        possibilities = []
        for data in self.solution_list:
            if data[1] > (self.solution_list[self.number_of_solutions//2][1] - self.solution_threshold):
                possibilities.append(data)
        mass_sum = sum([data[1] for data in possibilities])
        final_offset = sum([data[0]*(data[1]/mass_sum) for data in possibilities])
        print("Final offset with weighted sum:", final_offset)
        self.offset1_to_2 = final_offset

    #Method:This method will determine if two points are close enough
    #       to eachother within a given threshold
    #Pre:   The two numbers are given, and the current matching
    #       segment length as to adjust the threshold
    #Att.'s:self.s_list1 (type=List)
    #       self.s_list2 (type=List)
    #       THRESHOLD (type=Global Variable)
    #Post:  This will return True if the values are close enough,
    #       False if they are too far from eachother
    def threshold(self, start1, start2, length=1):
        sens1, sens2 = self.s_list1[start1], self.s_list2[start2]
        sens_threshold = THRESHOLD + (.01*length**2)
        s_diff = abs(sens1 - sens2)
        if s_diff < sens_threshold:
            return True
        else:
            return False

    #Method:This method will build the turtle image based on the x,y
    #       coordinates given
    #Pre:   The final list of x,y coordinates that are "walls" are
    #       given [list (tuple x,y)]
    #Att.'s:
    #Post:  The ppm image is saved
    def create_turtle_map(self):
        self.turtle.setheading(0)
        self.turtle.clear()
        turtle.tracer(0)
        if self.offset1_to_2 > 0:
            self.turtle.right(self.sense_ang/2)
            factor = -1
        else:
            factor = 1
            self.turtle.left(self.sense_ang/2)
        for i in range(round(self.offset1_to_2)):
            self.turtle.left(self.degrees_per_data_point)
        for i in range(round(self.offset1_to_2), len(self.s_list1)):
            index1 = i + int(factor * self.offset1_to_2)
            index2 = i
            if abs(self.s_list1[index1] - self.s_list2[index2]) < MAX_DIFFERENCE:
                self.turtle.forward((self.s_list1[index1]+self.s_list2[index2])/2)
                if DRAW_REBUILD_DOTS:
                    self.turtle.dot()
            self.turtle.goto(0,0)
            self.turtle.left(self.degrees_per_data_point)
        self.offset_list = []
        self.solution_list = []
        if DRAW_BEST_FIT_LINES:
            self.line_configure = LineConfigure(self.s_list1,
                                                self.s_list2,
                                                self.offset1_to_2,
                                                self.sense_ang, self.turtle)
            self.line_configure.construct_lines()


if __name__ == "__main__":
    sensor1_data = [(i+random.randint(-2,2)) for i in range(50,120)]
    sensor2_data = [(i+random.randint(-2,2)) for i in range(70)]
    map_data = MapBuilder()
    map_data.add_sensor_data_to_list(sensor1_data, sensor2_data)
    map_data.build_map()
