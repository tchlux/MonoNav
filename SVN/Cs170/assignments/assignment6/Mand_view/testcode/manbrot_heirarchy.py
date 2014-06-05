#This will be the width of the image
WIDTH = 1000
#This will be the height of the image
HEIGHT = WIDTH
#This is how detailed the colors will be
COLOR_FACTOR = 3*255

#This class will hold all of the necessary equations for a mandelbrot image.
class Mandelbrot:
    #Constructor, this method will initialize all attributes and start
    #the process of calculating a mandelbrot image
    #Pre:   The mandelbrot class is created
    #Post:  The attributes are created and the process begins
    def __init__(self):
        self.time #TYPE: TIME MODULE INSTANCE: This will be how time is recorded for funsies
        lst #TYPE: LIST: This will be the temporary storage for the system arguments
        self.a, self.b = self.convert_to_pixel_coord #TYPE: INTEGERS: This is where the first complex number will come from
        self.hsize #TYPE: INTEGER: This will be half of the image size requested (half for simplicity)
        self.ppm = #TYPE: PPM MODULE INSTANCE: This will be the initialized ppm image

    #This method converts complex coordinates to pixel coordinates
    #Pre:   The a and b values of the complex numer
    #Post:  Two numbers that are the corresponding pixel coordinates
    def convert_to_pixel_coord(self, x, y):
        pixx #TYPE: INTEGER: This will be the corresponding x pixel coordinate to a complex a
        pixy #TYPE: INTEGER: This will be the corresponding y pixel coordinate to a complex b

    #This method will create the mandelbrot image
    #Pre:   The method is called
    #Post:  The Mandelbrot image is made and written to a file
    def mandelbrot(self):
        min_x #TYPE: INTEGER: This will be the minimum x value
        min_y #TYPE: INTEGER: This will be the minimum y value
        x_diff = #TYPE: INTEGER: This will be the difference between x's
        y_diff = #TYPE: INTEGER: This will be the difference between y's
        #These two equations are used to convert pixels coordinates to complex coordinates
        x_complex = lambda x: x/WIDTH * (x_diff) + min_x
        y_complex = lambda y: y/HEIGHT * (y_diff) + min_y
        value #TYPE: COMPLEX NUMBER CLASS INSTANCE: This will be the complex number for a pixel
        self.initial #TYPE: COMPLEX NUMBER CLASS INSTANCE: This will be used in the recursive calculation
        i = #TYPE: INTEGER: This will be the color of the final pixel

    #This method will recursively calculate the color for the complex number
    #provided through testing of recursion depth
    #Pre:   A complex number, and a current depth
    #Post:  The depth associated with that pixel
    def calculate_pixel(self, cnum, depth):
        cnum #This will represent the newly calculated complex number


#This class will represent a complex numer
class ComplexNumber:
    #Constructor, this will create a complex number with corresponding
    #attributes
    #Pre:   The a and b values are given
    #Post:  The complex number's attributes are created and ready to be used
    def __init__(self, a, b):
        self.a = a#TYPE: INTEGER: This will be the a value for the current complex number
        self.b = b#TYPE: INTEGER: This will be the b value for the current complex number

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



