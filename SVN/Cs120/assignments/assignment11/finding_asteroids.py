import sys
import ppm
import math

#this function gives each pixel a classification given a number of divisions of intensity
#pre: the total intensity of the given pixel and the number of divisions of intensity
#post: the classification for the given intensity is given
def give_classification(total_intensity, number_of_levels):
    levels_list = []
    for i in range(number_of_levels):
        levels_list.append(i+1)
    max_pixel_intensity = 255*3
    condition_size = (max_pixel_intensity / len(levels_list))
    for level in levels_list:
        level_max = condition_size * level
        if number_of_levels == 1:
            if total_intensity >= 760:
                classification = "not dark"
                return classification
        else:
            if total_intensity <=  level_max:
                classification = level
                return classification

#this function is used to compare the two given pixels to eachother
#pre: two pixels, the number of divisions of intensity(levels), the tots are just
#    initialized here for convenience
#post: a True or False bool of if the pixels are the same
def brightness_comparison(pix1, pix2, number_of_levels, tot1=0, tot2=0):
    tot1 = pix1[0] + pix1[1] + pix1[2]
    tot2 = pix2[0] + pix2[1] + pix2[2]
    pix1_class = give_classification(tot1, number_of_levels)
    pix2_class = give_classification(tot2, number_of_levels)
    if pix1_class == pix2_class:
        return True
    else:
        return False

#this function compares each pixel of two images to eachother given 'classifications' of
#    each pixel
#pre: two ppm images, a number of possible classifications to be given
#post: a list of pixels that were not classified as the same intensity between the pictures
def check_pixels(image1, image2, number_of_levels):
    diff_pix_list = []
    height = len(image1)
    width = len(image1[0])
    for row in range(height):
        for col in range(width):
            if not brightness_comparison(image1[row][col], image2[row][col], number_of_levels):
                diff_pix_list.append([row,col])
    return diff_pix_list

#this function is a loop that actually draws the box of specified parameters
#pre: the image to be edited, the coord of the point, the box_size
#post: the image with a red box around the point specified
def final_box(image, row, col, box_size):
    if len(image) > (row + box_size):
        if len(image[0]) > (col + box_size):
            lst = [255,0,0]
            for i in range(-box_size,box_size+1):
                image[row+i][col + box_size] = lst
                image[row+i][col - box_size] = lst
                image[row + box_size][col+i] = lst
                image[row - box_size][col+i] = lst
        else:
            print('box could not be drawn at (',row,col,')')
    else:
        print('box could not be drawn at (',row,col,')')
    return image
    
#this function is used to create the red box of a specified size around the possible
#    asteroids
#pre: the list of locations to draw boxes, both images to be edited and the box size(if no
#    box size is given then it defaults to 6 pixel side length
#post: the two images with the boxes drawn in them, boxes will not be drawn if they are too
#    close to the edge of the picture
def draw_red_box(location_list, image1, image2, box_size=6):
    for location in location_list:
        row = location[0]
        col = location[1]
        image1 = final_box(image1, row, col, box_size)
        image2 = final_box(image2, row, col, box_size)
    return (image1, image2)

#this function looks at all the pixels in a group of pixels that are connected to eachother and calculates the center pixel
#pre: a list of pixels in one group (tuples in a list)
#post: one tuple of the xy coordinate of the center pixel
def find_center(group):
    total_x = 0
    total_y = 0
    for loc in group:
        total_x += loc[0]
        total_y += loc[1]
    length = len(group)
    center_x = int(total_x / length)
    center_y = int(total_y / length)
    return [center_x, center_y]

#this function tests if two pixels are adjacent to eachother, within 1 pixel difference on the x or y axis
#pre: two tuples that represent xy coordinates
#post: bool True or False if they are touching
def test_if_adjacent(pix1, pix2):
    x = math.fabs(pix1[0] - pix2[0])
    y = math.fabs(pix1[1] - pix2[1])
    if (x <= 1) or (y <= 1):
        return True
    else:
        return False

#this function creates a list of lists, the sub lists are of pixels(xy coordinates) that by some path are directly connected to eachother (list[group][pixel])
#pre: the group list either already 3-depth or a single empty list and a pixel to be tested and put into the proper group
#post: the final group list (3 depth)
def create_groups(group_list, test_pixel):
    if group_list != []:
        temp = group_list
        for i in range(len(group_list)):
            for location in group_list[i]:
                if test_if_adjacent(test_pixel, location):
                    group_list[i].append(test_pixel)
                    return group_list
        if temp == group_list:
            group_list.append([test_pixel])
            return group_list
    else:
        group_list.append([test_pixel])
        return group_list

#this function narrows all of the possible asteroids given to the two most dense groups of changed pixels (this and its child functions will create lists of changed pixels that touch eachother)
#pre: a list of tuples, each of which signifies a xy coordinate of a pixel
#post: two xy coordinates in a list that represent the density center of the two largest groups of changed pixels
def find_most_likely_asteroid(ast_list):
    groups = []
    longest = []
    second_long = []
    for asteroid in ast_list:
        groups = create_groups(groups, asteroid)
    for group in groups:
        if len(group) > len(longest):
            longest = group
        else:
            if len(group) > len(second_long):
                second_long = group
    return [find_center(longest),find_center(second_long)]

#this function calculates the distance between the two given pixels
#pre: it is expected that the pixels are tuples of x,y coordinates
#post: the distance(in coordinate values) between the two pixels approximated to the nearest int
def calculate_number_of_pixels_between(pix1, pix2):
    pix1_x = pix1[0]
    pix1_y = pix1[1]
    pix2_x = pix2[0]
    pix2_y = pix2[1]
    x_distance = (pix1_x - pix2_x)
    y_distance = (pix1_y - pix2_y)
    return int(((x_distance**2) + (y_distance**2))**(1/2))

#this function calculates the parallax distance of an asteroid from earth given the distance between the shooting locations of the photos, it defaults to 1000 km between pics
#pre: this function takes a list of two possible asteroids, if specified it takes the distance of one Astronomical Unit(AU) and the conversion rate between AU and Parallax
#post: the kilometers distance between the two objects
def calculate_parallax_distance(ast_list, au_to_kilometers_conversion=1000, parallax_to_au_conversion=206265):
    distance = calculate_number_of_pixels_between(ast_list[0], ast_list[1])
    half_dist = distance / 2
    radians = math.radians(half_dist)
    dpc = 1 / radians
    num_au = dpc * parallax_to_au_conversion
    kilometers = num_au * au_to_kilometers_conversion
    return kilometers

#this is a function full of print statements, I was just trying to create some organization
#pre: the number statement to be used and any extra data which defaults to and empty string
#post: a line is printed with its extra data
def print_statements(statement_number, extra_data=''):
    print_dict = {1:'the proper number of input files was not specified',2:'Image read has begun, please wait.',3:'length of image1 row, col',4:'length of image2 row, col',5:'Images read in, searching for asteroids..',6:'List of changed pixels made.',7:'Possible asteriods found:',8:'final images with highlights made, writing..',9:'final images written out as: first_image = stars1, sedond_image = stars2', 10:'The distance of the asteroid from earth in kilometers is approximately: '}
    print(print_dict[statement_number],extra_data)

#this function operates the finding_asteroids.py program, printing updates, prompting for input, and calculating and writing new images
#pre: all prompts need responses with the exception of the Box size and refine inputs
#post: the two input images are reproduced with the pixels that changed between the twohighlighted
def find_asteroids_main():
    if len(sys.argv) != 3:
        print_statements(1)
    box_size = (input('How big of a box do you want around the possible asteriods? Default = 6 : '))
    number_of_levels = int(input('How many classes of brightness do you want? (Three is reccomended.) : '))
    print_statements(2)
    image1 = ppm.read_image(sys.argv[1])
    image2 = ppm.read_image(sys.argv[2])
    print_statements(3, (str(len(image1))+' '+str(len(image1[0]))))
    print_statements(4, (str(len(image2))+' '+str(len(image2[0]))))
    print_statements(5)
    list_changed_pixels = check_pixels(image1, image2, number_of_levels)
    print_statements(6)
    print_statements(7,len(list_changed_pixels))
    yes_no = input('Do you want to refine these results to the two most dense spots of change\n and find the parallax distance between the two identified asteroids? ')
    if yes_no == 'yes':
        list_changed_pixels = find_most_likely_asteroid(list_changed_pixels)
        print_statements(7,len(list_changed_pixels))
        distance = calculate_parallax_distance(list_changed_pixels)
        print_statements(10, int(distance))
    if box_size == '':
        (image1, image2) = draw_red_box(list_changed_pixels, image1, image2)
    else:
        box_size = int(box_size)
        (image1, image2) = draw_red_box(list_changed_pixels, image1, image2, box_size)
    print_statements(8)
    ppm.write_image('stars1.ppm',image1)
    ppm.write_image('stars2.ppm',image2)
    print_statements(9)


find_asteroids_main()
