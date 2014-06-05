import turtle
from tkinter import PhotoImage
from stack_and_queue import Stack
CANVAS_WIDTH = 640
CANVAS_HEIGHT = 480
CANVAS_CENTER_X = 0
CANVAS_CENTER_Y = 0

class OutOfBoundsException(Exception):
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __str__(self):
        rep = "either x = %i or y = %i are out of bounds." % (self.x, self.y)
        return rep

class PaintBucket:
    def __init__(self):
        turtle.setup(width=CANVAS_WIDTH, height=CANVAS_HEIGHT)
        canvas = turtle.getcanvas()
        canvas.bind("<ButtonPress-1>", self.fill_region)
        canvas.pack()
        self.image = PhotoImage(file="ovals.gif")
        position = (CANVAS_CENTER_X, CANVAS_CENTER_Y)
        image_id = canvas.create_image(position, image=self.image)
        turtle.mainloop()

    #Pre:  x and y are integers, x and y coordinates within the turtle
    #      canvas.
    #Post: Returns a 3-tuple of integers, representing red, green, and
    #      blue values for the color of the location clicked.
    def _get_pixel_color(self, x, y):
        if not self._in_bounds(x, y):
            raise OutOfBoundsException(x, y)

        return self.image.get(x, y)

    #Pre:  x and y are integers, x and y coordinates within the turtle
    #      canvas.  color is either a string that PhotoImage class can
    #      convert into a color, or a 3-tuple of integers of the red,
    #      green, and blue values of a color.
    #Post: Sets the (x,y) location within the turtle canvas to the
    #      specified color.
    def _set_pixel_color(self, x, y, color):
        if not self._in_bounds(x, y):
            raise OutOfBoundsException(x, y)

        self.image.put(color, (x, y))

    #Pre:  event is an event object, specified from the canvas click
    #      listener.
    #Post: Calls fill_region_recursive, which will recursively fills
    #      the the region that the user clicked within.
    def fill_region(self, event):
        click_x = event.x
        click_y = event.y
        click_color = self._get_pixel_color(click_x, click_y)
        self.fill_region_loop(click_x, click_y, click_color, "black")
    
    #Pre:  x and y are integers, which are locations within the turtle
    #      canvas. 
    #Post: Returns True if x and y are valid locations within the
    #      turtle canvas.  Returns False otherwise.
    def _in_bounds(self, x, y):
        return 0 <= x < CANVAS_WIDTH and 0 <= y < CANVAS_HEIGHT

    #Method: This method fills a region with the fill color using a
    #        stack and a loop
    #Pre:    The x,y coordinate (tuple), color_to_fill (string), and
    #        fill color (string) are given
    #Att's:  self._get_pixel_color (type=Method)
    #Post:   The region is filled with the fill color
    def fill_region_loop(self,x,y,color_to_fill,fill_color):
        points = Stack()
        points.push((x,y))
        while points.size > 0:
            (x,y) = points.pop()
            self._set_pixel_color(x,y,fill_color)
            if self._in_bounds(x+1,y) and self._get_pixel_color(x+1,y) == color_to_fill:
                points.push((x+1,y))
            if self._in_bounds(x-1,y) and self._get_pixel_color(x-1,y) == color_to_fill:
                points.push((x-1,y))
            if self._in_bounds(x,y+1) and self._get_pixel_color(x,y+1) == color_to_fill:
                points.push((x,y+1))
            if self._in_bounds(x,y-1) and self._get_pixel_color(x,y-1) == color_to_fill:
                points.push((x,y-1))

if __name__ == '__main__':
    PaintBucket()
