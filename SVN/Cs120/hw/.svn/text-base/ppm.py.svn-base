NUMBER_OF_CHANNELS = 3
MAX_INTENSITY = 255

def read_pixel(ppm_file):
    pixel = []
    for channel in range(NUMBER_OF_CHANNELS):
        pixel.append(int(ppm_file.readline().strip()))
    return pixel

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

