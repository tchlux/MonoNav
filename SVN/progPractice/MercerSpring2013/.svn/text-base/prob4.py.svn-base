# Roanoke College: Team 35
# prob4.py

import sys
import math as m

def is_prime(num):
    for i in range(2,num//2+1):
        if num%i == 0:
            return False
    return True

def get_factors(numbers):
    primes = []
    for number in numbers:
        for i in range(number//2+1):
            if (i>1) and (number%i == 0) and (is_prime(i)):
                primes += [i, number/i]
                break
    return(primes)

def get_primes(num_keys):
    primes = []
    for i in range(m.ceil(num_keys/5)):
        nums = [int(num) for num in sys.stdin.readline().split()]
        primes += get_factors(nums)

    final = []
    for prime in primes:
        if prime not in final:
            final.append(prime)
    final.sort()
    return(final)

def print_stuff(primes):
    while (len(primes) > 0):
        for i in range(5):
            if (len(primes) > 0):
                print(int(primes.pop(0)), end=" ")
        print()

lines = int(sys.stdin.readline())
for i in range(lines):
    info = [int(el) for el in sys.stdin.readline().split()]
    primes = get_primes(info[1])
    print(info[0])
    print_stuff(primes)




