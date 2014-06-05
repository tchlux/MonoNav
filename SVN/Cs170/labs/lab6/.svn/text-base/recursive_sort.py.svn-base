def recurs_sort(lst, start, end):
    print(lst[start:end])
    rng = (end-start)//2
    if (end-start) > 2:
        recurs_sort(lst, start, start+rng)
        recurs_sort(lst, start+rng, end)
        recombine(lst, start, end, rng)
    else:
        if lst[start] > lst[end-1]:
            lst[start],lst[end] = lst[end],lst[start]


def recombine(lst, start, end, rng):
    


    for fst in range(start, end//2):
        for sec in range(end//2, end):
            if lst[fst] > lst[sec]:
                lst[fst],lst[sec] = lst[sec],lst[fst]

listy = [1,3,2,5,6,7,4,8]
recurs_sort(listy, 0, len(listy))
print(listy)
