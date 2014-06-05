def image_color_prompt():
    print('Input a number between 0 and 100 for color intensities')
    red = input("Red intensity? ")
    green = input("Green intensity? ")
    blue = input("Blue intensity? ")
    return (red, green, blue)

def create_and_fill_picture_file():
    (red, green, blue) = image_color_prompt()
    file_name = input('Picture name?')
    picture = open(file_name+'.ppm' , "w")
    picture.write('P3\n')
    picture.write('# this file was created by ppmimage_program.py\n')
    picture.write('600 600\n')
    picture.write('100\n')
    for i in range(600*600):
        picture.write(red+'\n')
        picture.write(green+'\n')
        picture.write(blue+'\n')
    picture.close()

create_and_fill_picture_file()
