# Roanoke College: Team 35
# prob12.py

import sys

def get_probs(probs, envelopes, total):
    default = 1 / total
    current_prob = default
    print(envelopes)
    for i in range(len(envelopes)):
        if envelopes[i] == '1':
            print("CURREN", current_prob)
            probs.append(current_prob)
            current_prob = default
        else:
            probs.append(0.0)
            current_prob += default
    if current_prob > default:
        probs[0] += (current_prob-default)

def run_test():
    line = [int(num) for num in sys.stdin.readline().strip().split()]
    total = line[0]
    rounds = line[1]
    probs = []
    envelopes = sys.stdin.readline().split()
    get_probs(probs, envelopes, total)
    for i in range(len(probs)):
        print(round(probs[i], 6), end=" ")
    print()

tests = int(sys.stdin.readline().strip())
for i in range(tests):
    run_test()
