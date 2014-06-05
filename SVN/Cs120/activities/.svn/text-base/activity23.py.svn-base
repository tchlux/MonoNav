def find_distance_between_two_points(one_x, one_y, two_x, two_y):
    x_sum = one_x + two_x
    y_sum = one_y + two_y
    mid_x = (x_sum / 2)
    mid_y = (y_sum / 2)
    return (mid_x, mid_y)


def prompt_for_number_list():
    input_string = input("enter list of integers: ")
    input_list = input_string.split(",")
    number_list = []
    for string in input_list:
        number_list.append(int(string))
    return number_list


def find_mode():
    number_dictionary = {}
    mode_list = []
    list_of_numbers = prompt_for_number_list()
    for item in list_of_numbers:
        if item in number_dictionary:
            number_dictionary[item] = number_dictionary[item] + 1
        else:
            number_dictionary[item] = 1
    list_of_values = list(number_dictionary.values())
    max_value = max(list_of_values)
    for key in number_dictionary
        if number_dictionary[key] == max_value:
            mode_list.append(key)
    print("list of mode(s)")
    print(mode_list)
    print('The number of occurances was', max_value)
