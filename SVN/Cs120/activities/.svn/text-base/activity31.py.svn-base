import sys
import ppm

def shrink_image():
    if len(sys.argv) == 2:
        file_name = sys.argv[1]
    else:
        print('ERROR ERROR ERROR SYSTEM FAILURE')
        print('because ya typed too much brah')
    image = ppm.read_image(file_name)
    height = len(image)
    width = len(image[0])
    small_image = [[[0,0,0] for col in range(width//2)] for row in range(height//2)]
    for row in range(0, height, 2):
        for col in range(0, width, 2):
            (red,green,blue) = return_av_of_four(image, row, col)
            small_image[row//2][col//2] = [red, green, blue]
    ppm.write_image('small_image.ppm', small_image)


def return_av_of_four(image,row, top_left):
    red_tot = image[row][top_left][0] + image[row][top_left + 1][0] + image[row + 1][top_left][0] + image[row + 1][top_left + 1][0]
    green_tot = image[row][top_left][1] + image[row][top_left + 1][1] + image[row + 1][top_left][1] + image[row + 1][top_left + 1][1]
    blue_tot = image[row][top_left][2] + image[row][top_left + 1][2] + image[row + 1][top_left][2] + image[row + 1][top_left + 1][2]
    red = red_tot / 4
    green = green_tot / 4
    blue = blue_tot / 4
    return (red, green, blue)


shrink_image()
