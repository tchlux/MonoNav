import math
import itertools as it

def sudoku_list():
    boxes = 81 - 18
    full = 100
    start = 0
    opts = [(n/boxes)*full for n in range(start, boxes+1)]
    return opts

def word_search_list():
    words = 17
    full = 100
    start = 0
    opts = [(n/words)*full for n in range(start, words+1)]
    return opts

def who_am_i_list():
    pics = 15
    full = 100
    start = 0
    opts = [(n/pics)*full for n in range(start, pics+1)]
    return opts

def greek_letters():
    letters = 22
    full = 100
    percent = 1.025
    start = 0
    opts = [(3.14)*(percent**n) for n in range(start, letters+1)]
    opts = [0.0] + opts
    return list(it.accumulate(opts))

def get_threes():
    threes = 3
    denom = 13
    full = 100
    start = 0
    opts = [(n/denom)*full for n in range(start, threes+1)]
    return opts

def diff_pi(num):
    return ((math.pi*100)-num)%1

def find_best_combination():
    sl = sudoku_list()
    wsl = word_search_list()
    wai = who_am_i_list()
    gl = greek_letters()
    th = get_threes()
    it.p = it.permutations
    corr_comb = [] #corresponding combinations
    opts = [] #options
    print(sl)
    print(wsl)
    print(wai)
    print(gl)
    print(th)
    for a in range(len(sl)): 
        for b in range(len(wsl)):
            for c in range(len(wai)): 
                for d in range(len(gl)):
                    for e in range(len(th)):
                        corr_comb.append([a,b,c,d,e])
                        opts.append(diff_pi(sl[a]+wsl[b]+wai[c]+gl[d]+th[e]))
    closest = min(opts)
    index = opts.index(closest)
    c = corr_comb[opts.index(min(opts))]
    pts_list = [sl[c[0]],wsl[c[1]],wai[c[2]],gl[c[3]],th[c[4]]]
    pts = sum(pts_list)
    # print("Best option:", closest)
    # print("Index:", index)
    print("Best combination:", c)
    print("Corresponding pts:", pts_list)
    print("Actual points total:", pts)
    print("Needed remaining:", 314-int(pts))
    print("Final score:", (314-int(pts))+pts)

find_best_combination()
