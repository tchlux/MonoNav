import math
import random
import turtle
from wall import Wall
import time
import map_builder

PAUSE_TIME = 0
STEP_SIZE = 1
ROOM_LENGTH = 400
X_OFFSET = -100
Y_OFFSET = -130
TURN_AMOUNT = 3
TURN_VARIANCE = .3
SENSOR_ERROR = 3
ANGLE_BETWEEN_SENSORS = 120
RIGHT_SENSOR_COLOR = "blue"
LEFT_SENSOR_COLOR = "green"
ROTATIONS_DEGREES = 360*4
UPDATE_FREQUENCY = 180

DRAW_ERROR = False
DRAW_SCAN_BEAMS = False
DRAW_WALLS = True
DRAW_SENSOR_DOTS = True
map_builder.DRAW_REBUILD_DOTS = True
map_builder.DRAW_BEST_FIT_LINES = True

class MapData:
    #Method:
    #Pre:   
    #Att's: 
    #Post:  
    def __init__(self, turn_amount, turn_variance, angle_between_sensors):
        self.draw_error = DRAW_ERROR
        self.sensor_1_readings = []
        self.sensor_2_readings = []
        self.turn_amount = turn_amount
        self.turn_variance = turn_variance
        self.angle_between_sensors = angle_between_sensors
        self.deg_to_rad = math.pi / 180
        self.scanner = turtle.Turtle()
        self.scanner.pu()
        self.scanner.ht()
        self.turtle = turtle.Turtle()
        self.turtle.pu()
        self.turtle.ht()
        self.pointer = turtle.Turtle()
        turtle.tracer(0)
        self.build_room()
        self.mapa = map_builder.MapBuilder(ANGLE_BETWEEN_SENSORS)

    #Method:
    #Pre:    
    #Att's:  
    #Post:   
    def build_room(self):
        self.wall_list = []
        LENGTH1 = ROOM_LENGTH // 2
        LENGTH2 = ROOM_LENGTH // 4
        UNIT = ROOM_LENGTH // 10

        # ######TRIANGLE######
        # p1, p2 = (-LENGTH1+X_OFFSET, -LENGTH2+Y_OFFSET), (LENGTH1+X_OFFSET, -LENGTH2+Y_OFFSET)
        # p3 = (0+X_OFFSET, LENGTH1+Y_OFFSET)
        # self.wall_list.append(Wall(p1,p2, DRAW_WALLS))
        # self.wall_list.append(Wall(p2,p3, DRAW_WALLS))
        # self.wall_list.append(Wall(p3,p1, DRAW_WALLS))

        # #########BOX#######
        # p1, p2 = (-LENGTH1+X_OFFSET, LENGTH1+Y_OFFSET), (LENGTH1+X_OFFSET, LENGTH1+Y_OFFSET)
        # p3, p4 = (LENGTH1+X_OFFSET, -LENGTH1+Y_OFFSET), (-LENGTH1+X_OFFSET, -LENGTH1+Y_OFFSET)
        # self.wall_list.append(Wall(p1, p2, DRAW_WALLS))
        # self.wall_list.append(Wall(p2, p3, DRAW_WALLS))
        # self.wall_list.append(Wall(p3, p4, DRAW_WALLS))
        # self.wall_list.append(Wall(p4, p1, DRAW_WALLS))

        # #######TRAPEZOID########
        # p1, p2 = (-LENGTH2+X_OFFSET, LENGTH1+Y_OFFSET), (LENGTH2+X_OFFSET, LENGTH1+Y_OFFSET)
        # p3, p4 = (LENGTH1+X_OFFSET, -LENGTH1+Y_OFFSET), (-LENGTH1+X_OFFSET, -LENGTH1+Y_OFFSET)
        # self.wall_list.append(Wall(p1, p2, DRAW_WALLS))
        # self.wall_list.append(Wall(p2, p3, DRAW_WALLS))
        # self.wall_list.append(Wall(p3, p4, DRAW_WALLS))
        # self.wall_list.append(Wall(p4, p1, DRAW_WALLS))

        # ######OCTAGON######
        # p1, p2 = (-LENGTH1+X_OFFSET,LENGTH2+Y_OFFSET), (-LENGTH2+X_OFFSET, LENGTH1+Y_OFFSET)
        # p3, p4 = (LENGTH2+X_OFFSET, LENGTH1+Y_OFFSET), (LENGTH1+X_OFFSET, LENGTH2+Y_OFFSET)
        # p5, p6 = (LENGTH1+X_OFFSET, -LENGTH2+Y_OFFSET), (LENGTH2+X_OFFSET ,-LENGTH1+Y_OFFSET) 
        # p7, p8 = (-LENGTH2+X_OFFSET, -LENGTH1+Y_OFFSET), (-LENGTH1+X_OFFSET, -LENGTH2+Y_OFFSET)
        # self.wall_list.append(Wall(p1, p2, DRAW_WALLS))
        # self.wall_list.append(Wall(p2, p3, DRAW_WALLS))
        # self.wall_list.append(Wall(p3, p4, DRAW_WALLS))
        # self.wall_list.append(Wall(p4, p5, DRAW_WALLS))
        # self.wall_list.append(Wall(p5, p6, DRAW_WALLS))
        # self.wall_list.append(Wall(p6, p7, DRAW_WALLS))
        # self.wall_list.append(Wall(p7, p8, DRAW_WALLS))
        # self.wall_list.append(Wall(p8, p1, DRAW_WALLS))

        # #########CAVE#########
        # p1, p2 = (-6*UNIT+X_OFFSET, -2*UNIT+Y_OFFSET), (-6*UNIT+X_OFFSET, 5*UNIT+Y_OFFSET)
        # p3, p4 = (-UNIT+X_OFFSET, 5*UNIT+Y_OFFSET), (0+X_OFFSET, 2*UNIT+Y_OFFSET)
        # p5, p6 = (3*UNIT+X_OFFSET, 2*UNIT+Y_OFFSET), (3*UNIT+X_OFFSET, -3*UNIT+Y_OFFSET)
        # p7, p8 = (5*UNIT+X_OFFSET, -3*UNIT+Y_OFFSET), (2*UNIT+X_OFFSET, -8*UNIT+Y_OFFSET)
        # p9, p10 = (-5*UNIT+X_OFFSET, -8*UNIT+Y_OFFSET), (-8*UNIT+X_OFFSET, -3*UNIT+Y_OFFSET)
        # self.wall_list.append(Wall(p1, p2, DRAW_WALLS))
        # self.wall_list.append(Wall(p2, p3, DRAW_WALLS))
        # self.wall_list.append(Wall(p3, p4, DRAW_WALLS))
        # self.wall_list.append(Wall(p4, p5, DRAW_WALLS))
        # self.wall_list.append(Wall(p5, p6, DRAW_WALLS))
        # self.wall_list.append(Wall(p6, p7, DRAW_WALLS))
        # self.wall_list.append(Wall(p7, p8, DRAW_WALLS))
        # self.wall_list.append(Wall(p8, p9, DRAW_WALLS))
        # self.wall_list.append(Wall(p9, p10, DRAW_WALLS))
        # self.wall_list.append(Wall(p10, p1, DRAW_WALLS))

        #########FOX########
        #Room on bottom right
        p3, p4 = (1.5*UNIT+X_OFFSET, UNIT+Y_OFFSET), (2*UNIT+X_OFFSET, UNIT+Y_OFFSET)
        p5, p6 = (2*UNIT+X_OFFSET, 2*UNIT+Y_OFFSET), (5*UNIT+X_OFFSET, 2*UNIT+Y_OFFSET)
        p7, p8 = (5*UNIT+X_OFFSET, -2*UNIT+Y_OFFSET), (2*UNIT+X_OFFSET, -2*UNIT+Y_OFFSET)
        p9, p10 = (2*UNIT+X_OFFSET, Y_OFFSET), (1.5*UNIT+X_OFFSET, Y_OFFSET)
        #End room on bottom right
        p11, p12 = (1.5*UNIT+X_OFFSET, -5*UNIT+Y_OFFSET), (-4*UNIT+X_OFFSET, -5*UNIT+Y_OFFSET)
        p13, p14 = (-4*UNIT+X_OFFSET, -2*UNIT+Y_OFFSET), (-1.5*UNIT+X_OFFSET, -2*UNIT+Y_OFFSET)
        #Room on left
        p15, p16 = (-1.5*UNIT+X_OFFSET, 2*UNIT+Y_OFFSET), (-2*UNIT+X_OFFSET, 2*UNIT+Y_OFFSET)
        p17, p18 = (-2*UNIT+X_OFFSET, Y_OFFSET), (-5*UNIT+X_OFFSET, Y_OFFSET)
        p19, p20 = (-5*UNIT+X_OFFSET, 4*UNIT+Y_OFFSET), (-2*UNIT+X_OFFSET, 4*UNIT+Y_OFFSET)
        p21, p22 = (-2*UNIT+X_OFFSET, 3*UNIT+Y_OFFSET), (-1.5*UNIT+X_OFFSET, 3*UNIT+Y_OFFSET)
        #End room on left
        p23, p24 = (-1.5*UNIT+X_OFFSET, 8*UNIT+Y_OFFSET), (1.5*UNIT+X_OFFSET, 8*UNIT+Y_OFFSET)
        #Room on top right
        p25, p26 = (1.5*UNIT+X_OFFSET, 4*UNIT+Y_OFFSET), (2*UNIT+X_OFFSET, 4*UNIT+Y_OFFSET)
        p27, p28 = (2*UNIT+X_OFFSET, 6*UNIT+Y_OFFSET), (5*UNIT+X_OFFSET, 6*UNIT+Y_OFFSET)
        p29, p30 = (5*UNIT+X_OFFSET, 2.5*UNIT+Y_OFFSET), (2*UNIT+X_OFFSET, 2.5*UNIT+Y_OFFSET)
        p31, p32 = (2*UNIT+X_OFFSET, 3*UNIT+Y_OFFSET), (1.5*UNIT+X_OFFSET, 3*UNIT+Y_OFFSET)
        #End room on top right
        self.wall_list.append(Wall(p3, p4, DRAW_WALLS))
        self.wall_list.append(Wall(p4, p5, DRAW_WALLS))
        self.wall_list.append(Wall(p5, p6, DRAW_WALLS))
        self.wall_list.append(Wall(p6, p7, DRAW_WALLS))
        self.wall_list.append(Wall(p7, p8, DRAW_WALLS))
        self.wall_list.append(Wall(p8, p9, DRAW_WALLS))
        self.wall_list.append(Wall(p9, p10, DRAW_WALLS))
        self.wall_list.append(Wall(p10, p11, DRAW_WALLS))
        self.wall_list.append(Wall(p11, p12, DRAW_WALLS))
        self.wall_list.append(Wall(p12, p13, DRAW_WALLS))
        self.wall_list.append(Wall(p13, p14, DRAW_WALLS))
        self.wall_list.append(Wall(p14, p15, DRAW_WALLS))
        self.wall_list.append(Wall(p15, p16, DRAW_WALLS))
        self.wall_list.append(Wall(p16, p17, DRAW_WALLS))
        self.wall_list.append(Wall(p17, p18, DRAW_WALLS))
        self.wall_list.append(Wall(p18, p19, DRAW_WALLS))
        self.wall_list.append(Wall(p19, p20, DRAW_WALLS))
        self.wall_list.append(Wall(p20, p21, DRAW_WALLS))
        self.wall_list.append(Wall(p21, p22, DRAW_WALLS))
        self.wall_list.append(Wall(p22, p23, DRAW_WALLS))
        self.wall_list.append(Wall(p23, p24, DRAW_WALLS))
        self.wall_list.append(Wall(p24, p25, DRAW_WALLS))
        self.wall_list.append(Wall(p25, p26, DRAW_WALLS))
        self.wall_list.append(Wall(p26, p27, DRAW_WALLS))
        self.wall_list.append(Wall(p27, p28, DRAW_WALLS))
        self.wall_list.append(Wall(p28, p29, DRAW_WALLS))
        self.wall_list.append(Wall(p29, p30, DRAW_WALLS))
        self.wall_list.append(Wall(p30, p31, DRAW_WALLS))
        self.wall_list.append(Wall(p31, p32, DRAW_WALLS))
        self.wall_list.append(Wall(p32, p3, DRAW_WALLS))

    #Method:
    #Pre:    
    #Att's:  
    #Post:   
    def compute_sensor_reading(self, heading):
        path_length = 0
        self.turtle.pu()
        if DRAW_SCAN_BEAMS:
            self.scanner.goto(0,0)
            self.scanner.pd()
        self.turtle.goto(0,0)
        self.turtle.setheading(heading)
        while path_length < ROOM_LENGTH*2:
            path_length += STEP_SIZE
            self.turtle.forward(STEP_SIZE)
            for wall in self.wall_list:
                if wall.wall_path_intersect((0,0),self.turtle.pos()):
                    self.turtle.pu()
                    if DRAW_SCAN_BEAMS:
                        self.scanner.goto(self.turtle.pos())
                    if DRAW_ERROR:
                        self.turtle.pd()
                    self.turtle.forward(random.randint(-SENSOR_ERROR,SENSOR_ERROR))
                    self.turtle.pu()
                    turtle.update()
                    time.sleep(PAUSE_TIME)
                    self.scanner.clear()
                    return self.turtle.pos()
        raise(Exception("I don't know how to tell you this, but I couldn't find a point."))

    #Method:
    #Pre:    
    #Att's:  
    #Post:   
    def change_heading(self):
        turn_variance = (random.random() * 2 - 1) * TURN_VARIANCE
        turn_amount = TURN_AMOUNT + turn_variance
        self.heading += turn_amount
        self.pointer.setheading(self.heading) 

    #Method:
    #Pre:    
    #Att's:  
    #Post:   
    def run_sensor(self, color, heading, lst):
        self.turtle.pencolor(color)
        self.scanner.pencolor(color)
        sensor_1_x, sensor_1_y = self.compute_sensor_reading(heading)
        self.turtle.goto(sensor_1_x, sensor_1_y)
        if DRAW_SENSOR_DOTS:
            self.turtle.dot()
        lst.append(round((sensor_1_x**2 + sensor_1_y**2)**(.5)))

    #Method:
    #Pre:    
    #Att's:  
    #Post:   
    def run(self):
        self.heading = 0
        while self.heading < ROTATIONS_DEGREES:
            self.run_sensor(RIGHT_SENSOR_COLOR, (self.heading+ANGLE_BETWEEN_SENSORS/2), self.sensor_1_readings)
            self.run_sensor(LEFT_SENSOR_COLOR, (self.heading-ANGLE_BETWEEN_SENSORS/2), self.sensor_2_readings)
            if len(self.sensor_1_readings)%(UPDATE_FREQUENCY//TURN_AMOUNT) == 0:
                self.mapa.add_sensor_data_to_list(self.sensor_1_readings, self.sensor_2_readings)
                self.mapa.build_map()
                self.mapa.create_turtle_map()
            self.change_heading()
            self.scanner.clear()

        self.mapa.add_sensor_data_to_list(self.sensor_1_readings, self.sensor_2_readings)
        self.mapa.build_map()
        self.mapa.create_turtle_map()


#Method:
#Pre:    
#Att's:  
#Post:   
if __name__ == "__main__":
    map_data = MapData(TURN_AMOUNT, TURN_VARIANCE, ANGLE_BETWEEN_SENSORS)
    map_data.run()
    turtle.mainloop()

