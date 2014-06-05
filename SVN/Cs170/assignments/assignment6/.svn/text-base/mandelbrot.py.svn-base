import ppm
import turtle
import math
import sys
import time
import os

NUMBER_OF_SEGMENTS = 20
WIDTH = 80
HEIGHT = WIDTH
COLOR_FACTOR = 255
#Maximum color factor of 3.8*255
#for a, more positive moves picture left
#for b, more positive moves picture up

A = .2788
B = -.61
SIZE = .005

#                self.ppm.draw_pixel((x,y),(round((color/COLOR_FACTOR)*255), 10, 40))#Deep blue to red


#This class will hold all of the necessary equations for a mandelbrot image.
class Mandelbrot:
    #Constructor, this method will initialize all attributes and start
    #the process of calculating a mandelbrot image
    #Pre:   The mandelbrot class is created
    #Post:  The attributes are created and the process begins
    def __init__(self, parent, a, b, size, dimensions, rl, rm, rh, gl, gm, gh, bl, bm, bh, depth):
        self.parent = parent
        self.status = 0
        self.depth = depth
        self.rl = rl #red low
        self.rm = rm #red mid
        self.rh = rh #red high
        self.gl = gl #green low
        self.gm = gm #green mid
        self.gh = gh #green high
        self.bl = bl #blue low
        self.bm = bm #blue mid
        self.bh = bh #blue high
        self.dim = dimensions
        self.time = time.time()
        self.a, self.b, self.hsize = a, b, float(size/2)
        size = int(math.ceil((self.dim / NUMBER_OF_SEGMENTS)))
        self.ppm = [ppm.PPM(width=self.dim, height=size) for i in range(NUMBER_OF_SEGMENTS)]
        self.update_formulas()

    def run(self):
        self.mandelbrot()

    def begin(self):
        self.mandelbrot()

    #Method:This updates the formulas for x and y complex number algorithms
    #Pre:   called
    #Att's: self.a (type=Float)
    #       self.b (type=Float)
    #       self.hsize (type=Int)
    #Post:  
    def update_formulas(self):
        #These equations are used to convert pixels coordinates to
        #complex coordinates
        self.min_x = (self.a - self.hsize)
        self.min_y = (self.b - self.hsize)
        self.x_diff = (self.a+self.hsize) - self.min_x
        self.y_diff = (self.b+self.hsize) - self.min_y
        self.x_complex = lambda x: x/self.dim * (self.x_diff) + self.min_x
        self.y_complex = lambda y: y/self.dim * (self.y_diff) + self.min_y


    #This method converts complex coordinates to pixel coordinates
    #Pre:   The a and b values of the complex numer
    #Post:  Two numbers that are the corresponding pixel coordinates
    def convert_to_pixel_coord(self, x, y):
        pixx = self.dim/2 + ((x-2)/4)*self.dim
        pixy = self.dim/2 + ((y-2)/4)*self.dim
        return pixx, pixy

    #Method:Interpolates between two values with a percentage given
    #Pre:   The two values as three-length tuples and the percentage
    #Att's: None
    #Post:  The (r,g,b) tuple of integers
    def interpolate(self, c1, c2, i):
        return (int((1-i)*c1[0] + i*c2[0]), int((1-i)*c1[1] + i*c2[1]), int((1-i)*c1[2] + i*c2[2]))

    #Method:Calculates the depth of a given pixel coordinate
    #Pre:   The x,y euclydian coord is given
    #Att's: self.x_complex (type=equation)
    #       self.y_complex (type=equation)
    #Post:  The depth achieved is returned
    def calc_depth(self, x, y):
        init = complex(self.x_complex(x), self.y_complex(y))
        cnum = init
        for i in range(self.depth):
            cnum = cnum*cnum + init
            if abs(cnum) > 2:
                return i
        return self.depth

    #This method will create the mandelbrot image
    #Pre:   The method is called
    #Post:  The Mandelbrot image is made and written to a file
    def mandelbrot(self):
        self.update_formulas()
        #This loop goes through and draws the Mandelbrot by pixels
        for segment in range(NUMBER_OF_SEGMENTS):
            start = self.dim*(segment/NUMBER_OF_SEGMENTS)
            end = start + self.dim/NUMBER_OF_SEGMENTS
            for y in range(int(start),int(end)):
                self.parent.statbar["value"] = y
                self.parent.root.update_idletasks()
                for x in range(self.dim):
                    depth = self.calc_depth(x,y)
                    if depth <= self.depth//2:
                        c = depth/(self.depth//2)
                        (r,g,b) = self.interpolate((self.rl, self.gl, self.bl),(self.rm, self.gm, self.bm),c)
                        self.ppm[segment].draw_pixel((x,int(y % (self.dim/NUMBER_OF_SEGMENTS))),(r,g,b))
                    else:
                        c = (depth-self.depth//2)/self.depth
                        (r,g,b) = self.interpolate((self.rm, self.gm, self.bm),(self.rh, self.gh, self.bh),c)
                        self.ppm[segment].draw_pixel((x,int(y % (self.dim/NUMBER_OF_SEGMENTS))),(r,g,b))
            string = "Mandelbrot"+str(segment)+".ppm"
            self.ppm[segment].save_image(string)
            self.parent.update_picture(None)
            self.parent.statbar["value"] = 0
        self.parent.statbar.grid_forget()
        self.parent.root.informme["text"] = self.parent.inform



    #This method will recursively calculate the color for the complex number
    #provided through testing of recursion depth
    #Pre:   A complex number, and a current depth
    #Post:  The depth associated with that pixel
    def calculate_pixel(self, cnum, depth):
        cnum = cnum*cnum + self.initial
        if depth == self.depth or abs(cnum.magnitude()) > 2:
            return depth
        else:
            return self.calculate_pixel(cnum, depth+1)




#This class will represent a complex numer
class ComplexNumber:
    #Constructor, this will create a complex number with corresponding
    #attributes
    #Pre:   The a and b values are given
    #Post:  The complex number's attributes are created and ready to be used
    def __init__(self, a, b):
        self.a = a
        self.b = b

    #This method will return the magnitude of a complex number
    #Pre:   None, the method is called
    #Post:  The magnitude of the complex number is returned. (distance
    #from origin)
    def magnitude(self):
        return (self.a**2 + self.b**2)**(1/2)

    #This method will add the current complex number to another
    #complex number
    #Pre:   Another complex number is being added
    #Post:  The addition of the two is returned
    def __add__(self, cnum):
        return ComplexNumber(self.a+cnum.a, self.b+cnum.b)

    #This method will multiply the current complex number with another
    #Pre:   Another complex number is provided
    #Post:  The product of the complex numbers is returned
    def __mul__(self, cnum):
        return ComplexNumber(self.a*cnum.a - self.b*cnum.b, self.a*cnum.b + cnum.a*self.b)

    def __abs__(self):
        return (self.a**2 + self.b**2)**(1/2)

if __name__ == "__main__":
    class Stat:
        def grid_forget(self):
            pass
        def __getitem__(self,num):
            pass
        def __setitem__(self,num,value):
            pass
    class Root:
        def __init__(self):
            self.informme = Stat()
        def update_idletasks(self):
            pass
    class Parent:

        def __init__(self):
            self.statbar = Stat()
            self.root = Root()
            self.inform = None
        def update_picture(self, null):
            pass

    parent = Parent()
    a = 0
    b = 0
    size = 2
    dimensions = 100
    rl, rm, rh = 1, 1, 1
    gl, gm, gh = 1, 1, 1
    bl, bm, bh = 1, 1, 1
    depth = 100
    a = Mandelbrot(parent, a, b, size, dimensions, rl, rm, rh, gl, gm, gh, bl, bm, bh, depth)
    a.begin()


#Explore around this location!
# A = .28
# B = -.61
# SIZE = .2

# limit of program in the center of star
# A = .3663629834227642
# B = -0.5915337732614456
# SIZE = 1.7763568394002505 * 10 **(-15)
#Attempted zoom reached recursive limits for our program (can't see far enough)
# A = -.1025
# B = .894
# SIZE = .04
# A = -1.25516
# B = .38208
# SIZE = .0001
#Mandelbrot6
# A = -1.2558
# B = .3813
# SIZE = .007
#Mandelbrot5
# A = -.108855
# B = .892125
# SIZE = .0001
#Mandelbrot100
# A = .2720
# B = .4805
# SIZE = .0015
