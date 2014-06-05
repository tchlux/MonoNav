
def _find_index_of_min(a_list, begin, end):
    index_of_min = begin
    for index in range(begin + 1, end):
        if a_list[index] < a_list[index_of_min]:
            index_of_min = index
    return index_of_min
        
def selection_sort(a_list):
    for index in range(0, len(a_list)):
        index_of_min = _find_index_of_min(a_list, index, len(a_list))
    a_list[index], a_list[index_of_min] = a_list[index_of_min], a_list[index]

