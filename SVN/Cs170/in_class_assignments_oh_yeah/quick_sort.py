def quick_sort(lst):
    num = lst[0]
    (left, right) = (1, len(lst)-1)
    while left < right:
        ind = 1
        while (lst[ind] < num) and (ind <= right):
            ind += 1
            if lst[ind] >= num:
                left = ind
            if ind == right:
                left = right


        if right > partition:
            right -= 1
        

    return lst

list = [5,3,2,1,6,0,9,8]
print(quick_sort(list))
