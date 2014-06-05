import sys, itertools

for line in sys.stdin:
    line = line.strip()
    stickLens = [int(e) for e in line.split(" ")[1:]]
    best = []
    low = float("inf")
    for selectNum in range(1, (len(stickLens) // 2) + 1):
        selections = list(itertools.combinations(stickLens, selectNum))
        for selects in selections:
            sum1 = sum(selects)
            sum2 = sum(stickLens) - sum1
            if abs(sum1 - sum2) < low:
                best = selects
                low = abs(sum1 - sum2)
    sum1 = sum(best)
    sum2 = sum(stickLens) - sum1
    print(round(0.5 * sum1 * sum2))
    # sticks = line.split()[1:]
    # sticks = [int(element) for element in sticks]
    # greatest = max(sticks)
    # sticks.remove(greatest)
    # second = max(sticks)
    # sticks.remove(second)
    # big_stick = [greatest, second]
    # while sticks != []:
    #     minimum = max(sticks)
    #     sticks.remove(minimum)
    #     big_min = min(big_stick)
    #     big_min_index = big_stick.index(big_min)
    #     big_stick[big_min_index] = big_min+minimum
    # area = big_stick[0]*big_stick[1]//2
    # print(area)
