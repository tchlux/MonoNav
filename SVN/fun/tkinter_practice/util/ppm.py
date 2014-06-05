import math

ROW_LOC = 1
COL_LOC = 2

#These are typical color constants.
#You can use these, but they aren't required.
BLACK = (0,0,0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
CYAN = (0, 255, 255)
MAGENTA = (255, 0, 255)
YELLOW = (255, 255, 0)

#Default constants
WIDTH = 640
HEIGHT = 480

class PPM:

    #Constructor
    #Pre:  Parameters rows and cols are two integers, representing image size
    #Post: Creates a list to represent the image internally.  Defaults the
    #      image.
    def __init__(self, width=WIDTH, height=HEIGHT):
        self._image_list = []
        self.reset_image(width, height)

    #Pre:  Parameters rows and cols are two integers representing
    #      the rows and columns of the image.
    #Post: Sets the _img_list attribute to a new list of tuples that is 
    #      rows x cols in size, all pixels are white
    def reset_image(self, cols, rows):
        self._image_list = [[WHITE for i in range(cols)] for i in range(rows)]
        

    #Pre:  Parameter location is a tuple, representing a 2-d coordinate in the
    #      image.  Parameter color is a 3-tuple, representing an RGB value
    #      to write to the specified pixel.
    #Post: Sets the self._image_list attribute at x,y to be color.
    def draw_pixel(self, location, color):
        y_loc, x_loc = location
        try:
            self._image_list[x_loc][y_loc] = color
        except IndexError:
            print("Caught Exception: Either x =", x_loc, "or y =", y_loc,
                  "is out of range.")

    #Pre:  Parameters start_loc and end_loc are tuples, representing
    #      2-d coordinates in the image.
    #      Parameter color is a 3-tuple, representing RGB values
    #      to use for the line color.
    #Post: Writes a color line into self._image_list from start_loc to end_loc
    def draw_line(self, start_loc, end_loc, color):
        if start_loc == end_loc:
            return

        start_y, start_x = start_loc
        end_y, end_x = end_loc

        delta_x = abs(end_x - start_x)
        delta_y = abs(end_y - start_y)

        sx = -1
        if start_x < end_x:
            sx = 1

        sy = -1
        if start_y < end_y:
            sy = 1
        
        err = delta_x - delta_y

        cx = start_x
        cy = start_y
        go_on = True
        while go_on:
            try:
                self._image_list[cx][cy] = color
            except IndexError:
                print("Either", cx, "or", cy, "is out of range")
            go_on = not(cx == end_x and cy == end_y)

            error = 2*err
            if error > -delta_y:
                err -= delta_y
                cx += sx

            if error < delta_x:
                err += delta_x
                cy += sy
        """
        start_y, start_x = start_loc
        end_y, end_x = end_loc

        #Need to check the type of line, need slope.
        rise = int(end_y - start_y)
        run = int(end_x - start_x)

        #Special Case: Vertical Line
        if run == 0:
            begin = min(start_y, end_y)
            end = max(start_y, end_y)
            for i in range(begin, end, 1):
                try:
                    self._image_list[end_x][i] = color
                except IndexError:
                    print("Caught Exception: y=", i, "is out of range")

            return

        assert run != 0, "Something has gone horribly wrong"

        #Run is valid, so this will not raise an exception
        #General Case: Normal line
        slope = rise / run
        y_int = end_y - slope * end_x

        #This is special syntax for defining a dynamic function.
        #It literally creates a function, in the traditional mathematical
        #sense, for a line.
        y_pt = lambda x : slope * x + y_int

        begin = min(start_x, end_x)
        end = max(start_x, end_x)

        for i in range(begin, end, 1):
            try:
                self._image_list[i][int(y_pt(i))] = color
            except IndexError:
                print("Caught Exception: Either", i, "or", int(y_pt(i)),
                      "are out of range")
        """

    #Remember, any attributes or methods that begin with an "_" are
    #"Private", and should not be used externally from the class.
    #Pre:  f_obj is a valid file object we can write to.
    #      a_list is the list of tuples we want to write to the file.
    #Post: writes the tuples to the file separated by spaces, with a new line at
    #      the end.
    def _write_list(self, f_obj, a_list):
        for tup in a_list:
            f_obj.write(bytes(tup))



    #Opens a file and writes the list to the file PPM style
    #Pre:  Parameter file_name is a valid string of a file we
    #      have access to write to.
    #Post: writes the self._image_list attribute to the
    #      specified file in PPM format, and closes the file.
    def save_image(self, file_name):
        try:
            f = open(file_name, "wb")

            #The PPM file magic number!
            f.write(bytes("P6 ",'UTF-8'))

            #Row and column information
            f.write(bytes(str(len(self._image_list[0])) + " " +
                    str(len(self._image_list)) + " ", "UTF-8"))

            #Color Information
            f.write(bytes("255\n","UTF-8"))
            
            for row in self._image_list:
                self._write_list(f, row)

        except IOError:
            print("Exception: Error opening file", file_name)
        finally:
            f.close()


if __name__ == "__main__":
    #The code below is provided as an example of how to use the above class
    cols = WIDTH
    rows = HEIGHT
    image = PPM()

    image.draw_line((cols//2, 0), (cols//2, rows), RED)
    image.draw_line((0, rows//2), (cols, rows//2), BLUE)
    image.draw_line((0,0), (cols,rows), CYAN)
    image.draw_line((cols, 0), (0, rows), MAGENTA)
    image.save_image("my_ppm.ppm")

