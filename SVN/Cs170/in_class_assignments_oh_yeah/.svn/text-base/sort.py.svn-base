def find_min(lst, search_start):
    minimum = lst[search_start]
    min_index = search_start
    for i in range(search_start,len(lst)):
        if lst[i] < minimum:
            minimum = lst[i]
            min_index = i
    return min_index

def sort(lst):
    for start in range(len(lst)):
        min_index = find_min(lst, start)
        lst[start], lst[min_index] = lst[min_index], lst[start]
    return lst


long_list = [4,1,3,4,6,4,2,1,4,8,9,7,6,34,5,3,2,4,34,5,6,5,43,188]
short_list = [5,3,4,2,1,0]
print(sort(long_list))
print(sort(short_list))
