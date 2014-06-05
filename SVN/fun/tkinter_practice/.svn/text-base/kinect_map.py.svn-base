import freenect
import math, os
import Tkinter as tk
import threading
import kinect_ppm

SCREEN_WIDTH = 660
SCREEN_HEIGHT = 500
PIXEL_CM_FACTOR = 2
START = (0, -100)
MAX_DATA_POINTS = 632
KINECT_WIDTH = 640 - 8
KINECT_FOV = 56.0#53.7#57.1
MIDDLE_PIXEL_Y = 480 // 2
DATA_W = 640
DATA_H = 480
S = 3
JUMP = 1
IMAGE = kinect_ppm.PPM(DATA_W,DATA_H)


DATA_FILE = ["401 1003.5","391 1002", "381 999.5","371 997.5","361 995.5","351 993","341 989","331 985.5","321 982.5","311 980","301 975.5","291 971.5","281 968","271 963","261 957.5","251 952.5","241 945.5","231 940","221 934","211 925","201 917.5","191 908.5","181 898.5","171 887.5","161 875","151 860","141 845","131 827","121 804.5","111 777","101 749","91 711","81 665.5","71 606","61 530","51 425"]

#Function:This function converts an rgb tuple (in range 0-255) into a
#         hexidecimal string
def to_hex(rgb,final="#"):
    hex_keys = {0:"0",1:"1",2:"2",3:"3",4:"4",5:"5",6:"6",7:"7",8:"8",9:"9",10:"A",11:"B",12:"C",13:"D",14:"E",15:"F"}
    for i in rgb: final=final+hex_keys[i//16]+hex_keys[i%16]
    return final

#Function:Turns a kinect reading into an rgb scaled value from 0 to 255
def to_rgb(value):
    a = 255 - int(max(min(value * 255/1000,255),0))
    return (a,a,a)

class Kinect:
    #Pre: data_points should be a positive integer less than 632,
    #or the string 'max'.
    #movement should be a Movement object. 
    #kinect_nav should be a KinectNav object.
    #Post: Initializes the general functionality of kinect data 
    #processing. 
    def __init__(self, data_points, interface):
        self.data_points = data_points
        self.angles = self.compute_angles()
        self._prepare_numeric_attributes()
        self.interface = interface
        self.keep_running = True
        self.take_picture = False
        self.frame_loop = False

    #Method:This method prepares all number based attributes, loading
    #       them, sorting them, and saving related attributes to them
    def _prepare_numeric_attributes(self):
        self.kinect_values = []
        self.distances = []
        for line in DATA_FILE:
            cm_str, value_str = line[:-1].split(" ")
            self.kinect_values.append(float(value_str))
            self.distances.append(float(cm_str))
        self.kinect_values.sort()
        self.distances.sort()
        self.min = min(self.kinect_values)
        self.max = max(self.kinect_values)

    #Method:Returns a list of cm values on a single bar
    #Pre:   data is given as a single dimensional list of numbers
    #Post:  The appropriate values are extracted from data based off
    #       of the number of data points desired
    def get_data_points(self, data):
        if self.data_points == 1: return data[len(data)//2]
        return_data = []
        for i in range(self.data_points):
            return_data.append(data[min(int(i * (len(data) / self.data_points-1)),len(data)-1)])
        return return_data

    #Method: Creates a list with angle-to-pixel inedex correspondance
    #Pre: Uses self.get_data_points and self.data_points
    #Post: Returns a list of angles.
    def compute_angles(self):
        pixel_indices = self.get_data_points(list(range(KINECT_WIDTH)))
        angles = []
        for index in pixel_indices:
            angles.append(KINECT_FOV * (index / float(KINECT_WIDTH - 1)))
        return angles

    #Method:This calls the diplay functionality of the visual depth map
    #Pre:   The arguments provided by freenect.mainloop's depth call
    #Post:  The depth map is displayed to the user
    def depth(self, dev, data, ctx):
        try:
            if self.take_picture or self.frame_loop:
                print("Starting the picture process")
                self.interface.display_frame(data)
                self.take_picture = False
        except:
            print("Error in depth callback")
            self.keep_running = False
            
    #Method:One of the mandatory methods for freenect to call while in
    #       it's mainloop
    #Pre:   The arguments that freenect provides to it's body method
    #Post:  If the program has been ended, freenect is ended
    def body(self, dev, ctx):
        if not self.keep_running:
            raise freenect.Kill

    #Method:This method begins freenect's runloop and assigns the
    #       methods to be called during operation
    #Pre:   Called
    #Post:  The mainloop begins
    def run(self):
        freenect.runloop(depth=self.depth, body=self.body)

    #Method:This method terminates the thread
    def stop_running(self):
        self.keep_running = False

#This is a base frame for tkinter to be used as a root for other
#frames
class DepthMap:
    #Constructor expanded from the normal tk.Tk
    def __init__(self):
        self.root = tk.Tk()
        (w, h) = self.root.winfo_screenwidth(), self.root.winfo_screenheight()
#        self.root.geometry('%dx%d+%d+%d' % (w/2, h/2, w/2, 0))
        self.root.geometry('%dx%d+%d+%d' % (SCREEN_WIDTH, SCREEN_HEIGHT, w/4, h/4))
        self.root.title("DepthMap: Kinect and Tkinter in one package")
        self.root.configure(bg="black")
        self.canvas = tk.Canvas(master=self.root,bg="grey")
        self.canvas.pack(side="left",fill="both", expand=True)
        self.canvas.configure(cursor="pencil")
        self.setup_bindings()
        self.height = h
        self.width = w
        self.kinect = Kinect(MAX_DATA_POINTS, self)
        self.k_thread = threading.Thread(target=self.kinect.run)
        self.k_thread.start()

    #Method:Clears the drawing canvas
    def clear_canvas(self, event=None):
        self.canvas.delete('all')

    #Method:prepares keyboard bindings for user
    def setup_bindings(self):
        self.root.bind("<Key-g>", self.start_stop_loop)
        self.root.bind("<Key-t>", self.take_picture)
        self.root.bind("<Key-q>", self.quit)
        self.root.bind("<Key-x>", self.quit)
        self.root.focus_set()

    #Method: This method begins the automatic updating of kinect frames
    def start_stop_loop(self, event=None):
        self.kinect.frame_loop = not self.kinect.frame_loop

    #Method:This sets a variable that will cause one snapshot from the
    #       kinect to be taken
    def take_picture(self, event=None):
        self.kinect.take_picture = True

    #Method:Draws the depth map to the canvas using a ppm image
    #Pre:   The numpy array of kinect data is given
    #Post:  The new image is saved and then posted to the canvas
    def draw_depth_map(self, data):
        print("Starting a depth map", len(data), len(data[0]),DATA_H,DATA_W)
        for row in range(0,len(data)):
            for col in range(0,len(data[0])):
                IMAGE.draw_pixel((col,row),to_rgb(data[row][col]))
        IMAGE.save_image("depth_map.ppm")
        self.canvas.image = tk.PhotoImage(file="depth_map.ppm")
        self.clear_canvas()
        self.canvas.create_image(330,250,image=self.canvas.image)

    #Method:Orchestrates the redrawing of the depth map
    #Pre:   Called, data is given as a numpy array
    #Post:  The new map drawing begins
    def display_frame(self, data):
        self.draw_depth_map(data)

    #Method:Ends the program properly, the only way to do so
    def quit(self, event=None):
        self.kinect.keep_running = False
        self.root.destroy()

if __name__ == "__main__":
    k = DepthMap()
    tk.mainloop()



#### POSSIBLY USELESS METHODS REMOVED FROM KINECT


    # #Method:Compensates for the kinects arc pattern in data values
    # #       from left to right
    # #Pre:   The cm distance to the point, and the angle difference
    # #       from the center of the kinect's FOV
    # #Post:  The compensated, and final distance to the point is returned
    # def compensate(self, cm, angle):
    #     return float(cm) / math.cos(math.radians(angle))

    # #Method:This method returns the cm distance of a kinect value
    # #Pre:   The value given is generated by the kinect
    # #Post:  The cm distance
    # def distance(self, kinect_value):
    #     if kinect_value > self.max:
    #         return 0
    #     i = 0
    #     while self.kinect_values[i] < kinect_value:
    #         i += 1
    #     return self.interpolate(i)

    # #Method:This method interpolates between two known distance values
    # #       to gather the actual distance to a point
    # #Pre:   An index (integer) is given
    # #Post:  The interpolated distance is returned
    # @staticmethod
    # def interpolate(i):
    #     larger_value = self.kinect_values[i]
    #     smaller_value = self.kinect_values[i - 1]
    #     t = (kinect_value - smaller_value) / float(larger_value - smaller_value)
    #     smaller_dist = self.distances[i - 1]
    #     larger_dist = self.distances[i]
    #     return t * (larger_dist - smaller_dist) + smaller_dist

    # #Pre: data should be a numpy array taken directly from a 
    # #kinect depth callback. 
    # #Post: Processes the data:
    # #Takes the middle row.
    # #Removes the last 8 bad pixels.
    # #Shortens the data by only getting self.data_points number of
    # #evenly spaced values from the list.
    # #Converts the raw kinect data to cm values.
    # #Compensates the kinect circular error. 
    # #Compensates for camera being in front of the robot pivot point. 
    # #Reverses the list for the convenience of the KinectNav class. 
    # def process_data(self, data):
    #     mid_data = data[MIDDLE_PIXEL_Y] #grab only middle row
    #     non_bad_data = mid_data[:KINECT_WIDTH] #chop end
    #     shortened_data = self.get_data_points(non_bad_data)
    #     cm_data = [self.distance(value) for value in shortened_data]
    #     compensated = []
    #     for i in range(len(cm_data)):
    #         cm = cm_data[i]
    #         angle = self.angles[i] - KINECT_FOV / 2.0
    #         compensated.append(self.dist_convert.compensate(cm, angle))
    #     processed_data = compensated[::-1]#Reverse list. >:( 
    #     return processed_data
