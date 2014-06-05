import ppm



def blur_image(ppm_file_name):
    image = ppm.read_image(ppm_file_name)
    height = len(image)
    width = len(image[0])
    for row in range(1, height-1, 3):
        for column in range(1, width-1, 3):
            blurred_pixel = blur_pixel(row, column, image)
    print(ppm_file_name)
    pass

def blur_pixel(row, column, image):
    red = [[image[row][column][0]for column in range(column-1,column+2)]for row in range(row-1, row+2)]
    green = [[image[row][column][1]for column in range(column-1,column+2)]for row in range(row-1, row+2)]
    blue = [[image[row][column][2]for column in range(column-1,column+2)]for row in range(row-1, row+2)]
    print(red,green,blue)
    red_average = sum(red) / 9
    green_average = sum(green) / 9
    blue_average = sum(blue) / 9

    print(red, green, blue)

image = ppm.read_image("python.ppm")
blur_pixel(3,3,image)

