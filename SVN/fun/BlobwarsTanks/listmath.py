#Function:This is to make the file importable
def __init__():
    pass

#Function:This function returns the value associated with a given key
#         in a given dictionary
#Pre:     A dictionary and a value to search for are given
#Post:    If it exists, the key associated with that value is
#         returned, otherwise None is returned
def get_key_of_value(dct, val):
    for key in dct:
        if dct[key] == val:
            return key
    raise(KeyError("The given value does not appear in the dictionary:", val))

#Function:This function returns the average distance every point in
#         list one is from list two given an offset, it ignores 0
#         values and does not return if there are not computable
#         values
#Pre:     Offset (integer) from list1 to list2, and two lists
#Post:    The average squared distance between the data points given
#         the offset is returned
def squared_distance(offset, lst1, lst2):
    diff_list = []
    start = max(0,-offset)
    end = min(len(lst1),len(lst1)-offset)
    for i in range(start,end):
        if lst1[i+offset] != 0 and lst2[i] != 0:
            diff_list.append((lst1[i+offset]-lst2[i])**2)
    if len(diff_list) != 0:
        return float(sum(diff_list))/len(diff_list)

#Function:This function aligns the lists by cycling through likely
#         offsets and picking the one with the least average squared
#         difference between data points
#Pre:     The new frame is given as a List, and the start and end of
#         the range of checkable offsets are provided
#Post:    The most likely offset between the frames is returned
def align_lists(lst1, lst2, s, e):
    off_dist_dict = {} #The dict of squared distance per offset
    length = len(lst1)
    for i in range(s,e):
        off_dist_dict[i] = squared_distance(i,lst1,lst2)
    min_squared = min(list(off_dist_dict.values()))
    return get_key_of_value(off_dist_dict, min_squared)


#Function:This slides a list to the right by interpolating between
#         values
#Pre:     A list is given
#Post:    A new slidden list is returned
def slide_right(lst):
    new = [(lst[i]+lst[i+1])/2.0 for i in range(len(lst)-1)]
    change = (lst[-1] - lst[-2])
    new.append(new[-1] + change)
    return new

#Function:This slides a list to the left by interpolating between
#         values
#Pre:     A list is given
#Post:    A new slidden list is returned
def slide_left(lst):
    new = [(lst[i]+lst[i-1])/2.0 for i in range(1,len(lst))]
    change = (lst[1] - lst[0])
    new.insert(0,new[0] - change)
    return new

#Function:This fxn returns the anti-derivative of a list, the value at
#         index 0 is simply considered to be c
#Pre:     A list is given and a constant (Float/Int)
#Post:    An anti-derived list is returned
def antiderivative(lst, c):
    anti = [c]
    for i in range(1,len(lst)):
        anti.append(anti[i-1]+lst[i])
    return anti

#Function:This fxn returns the derivative of a list, the derivative
#         at index 0 is given as the same as 1, should be disregarded 
#Pre:     A list is given
#Post:    The derivative is returned in list form
def derivative(lst):
    der = [lst[i]-lst[i-1] for i in range(0,len(lst))]
    der[0] = der[1]
    return der

#Function:Returns a list shrunk by a factor of two
#Pre:     A list is given
#Post:    A new shorter list is returned
def shrink(lst):
    return [(lst[i]+lst[i+1])/2.0 for i in range(0,len(lst),2)]

#Function:Returns a list expanded by a factor of two
#Pre:     A list is given
#Post:    A new longer list is returned
def expand(lst):
    new = []
    for i in range(len(lst)):
        new.append(lst[i])
        if i < len(lst)-1:
            new.append((lst[i]+lst[i+1])/2.0)
        else:
            change = lst[i]-lst[i-1]
            new.append((2*lst[i]+change)/2.0)
    return new


if __name__ == "__main__":
    lst = [0,1,2,3,4,5,6,7,8,9]
    print("List:",lst)
    print("Sliide to the left", slide_left(lst))
    print("Sliide to the right", slide_right(lst))
    print(antideriv(derivative(lst),0))
    print("Derivative:",derivative(lst))
    print("Shrunk:",shrink(lst))
    print("Expand:",expand(lst))
    assert lst == [0,1,2,3,4,5,6,7,8,9]
    lst = [0,1,1,1,1,1,1,1,1,1]
    c = 0
    print("Derivative list:",lst)
    print("Anti Deriv:",antiderivative(lst,c))
    assert lst == [0,1,1,1,1,1,1,1,1,1]

