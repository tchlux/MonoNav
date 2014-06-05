def linear_search(lst, searching):
    itr = 0
    found = False
    for element in lst:
        itr += 1
        found = element == searching
        if found:
            break
    return (found, itr)

def binary_search(lst, searching):
    itr = 0
    rng = len(lst)
    start = 0
    end = rng - 1
    found = False
    mid = (start+end) //2
    while (not found) and (end >= start):
        itr += 1
        mid = (start+end) //2
        if lst[mid] > searching:
            end = mid-1
        elif lst[mid] < searching:
            start = mid+1
        else:
            found = True
    return (found, itr)

if __name__ == "__main__":
    lst = range(0, 1000)        
