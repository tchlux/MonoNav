def bubble(a_list):
    for end in range(len(a_list)-1, 0, -1):
        for index in range(end):
            if a_list[index] > a_list[index+1]:
                a_list[index], a_list[index+1] = a_list[index+1], a_list[index]
