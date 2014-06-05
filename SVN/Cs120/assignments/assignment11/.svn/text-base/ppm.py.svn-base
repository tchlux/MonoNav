NUMBER_OF_CHANNELS = 3 # number of channels in a ppm file R, G, and B
MAX_INTENSITY = 255 # maximum intensity for a channel in a ppm file

# Reads three int values from the current location in the specified
# file as a list of length three.
# PRE:  ppm_file is a handle to a file opened to read in text mode and
#       there are at least three lines that contain only an int after the
#       current location.
# POST: Returns a list containing the next three ints in the specified
#       file.  The current location in the file is after the three ints that
#       were read.
def read_pixel(ppm_file):
    pixel = []
    for channel in range(NUMBER_OF_CHANNELS):
        pixel.append(int(ppm_file.readline().strip()))
    return pixel

# Read a ppm file into a three-dimensional list of ints.
# PRE:  ppm_file is the name of a ppm file.  The file does not have a
#       comment, each rgb value is on its own line, and the max value
#       is 255.
# POST: Returns a three dimensional list that represents the image in
#       the input file name.  The list dimensions are 
#       height x width x 3.  Each pixel color is in the order r, g, b.
def read_image(ppm_file_name):
    ppm_file = open(ppm_file_name, "r")
    ppm_file.readline()
    dimension_list = ppm_file.readline().strip().split()
    [width, height] = [int(string) for string in dimension_list]
    ppm_file.readline()
    image = [[None for col in range(width)] for row in range(height)]
    for row in range(height):
        for col in range(width):
            image[row][col] = read_pixel(ppm_file)
    ppm_file.close()
    return image

# Write a three-dimensional list of ints to a ppm file.
# PRE:  ppm_file_name is the name of the ppm file to write.  The parent
#       directory of this file must exist.
#       image is a three-dimensional list of ints that represents an
#       image.  The dimensions of the image are height x width x 3.
#       Each pixel color is in the order r, g, b.  The maximum value
#       for a color is 255.
# POST: A ppm image with the specified file name and image contents is
#       written to memory.
def write_image(ppm_file_name, image):
    height = len(image)
    width = len(image[0])
    ppm_file = open(ppm_file_name, "w")
    ppm_file.write("P3\n")
    ppm_file.write("%d %d\n" % (width, height))
    ppm_file.write("%d\n" % MAX_INTENSITY)
    for row in range(height):
        for col in range(width):
            pixel = tuple(image[row][col])
            ppm_file.write("%d\n%d\n%d\n" % pixel)
    ppm_file.close()

