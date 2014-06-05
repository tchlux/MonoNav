import random

lst = [i for i in range(100)]
ans = random.randint(0,100)
search = None
ind = len(lst) // 2
new_ind = 0
rang = len(lst)

while ans != search:
    try:
        search = lst[ind]
    except IndexError:
        if ind == len(lst):
            ind -= 1

    rang = rang//2
    if search >= ans:
        new_ind = int(ind/2)
    else:
        new_ind = ind + rang

    if ind == new_ind:
        print('answer not in list')
        ans = search

    ind = new_ind


print('answer found at index:', lst[ind])
print('search term:', search)
