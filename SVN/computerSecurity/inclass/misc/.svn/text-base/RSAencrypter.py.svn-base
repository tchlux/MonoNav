import random

LOWER = 14
UPPER = 300
START_E = 23

def checkPrime(num):
    for i in range(2,int(num**.5)):
        if (num % i) == 0:
            return False
    return True

def nearestLargerPrime(num):
    while not checkPrime(num):
        num += 1
    return num

def pickTwoPrimes():
    rand1 = random.randint(LOWER,UPPER)
    rand2 = random.randint(LOWER,UPPER)
    prime1 = nearestLargerPrime(rand1)
    prime2 = nearestLargerPrime(rand2)
    return prime1, prime2

def smallestDivisor(num):
    divisor = 2
    while (num%divisor) != 0:
        divisor += 1
    return divisor

def primeFactors(num):
    primeFactors = []
    largestPrime = 0
    while num > largestPrime:
        divisor = smallestDivisor(num)
        if (divisor > largestPrime):
            primeFactors.append(divisor)
            largestPrime = divisor
        num /= divisor
    return primeFactors

def isRelativelyPrime(num1, num2):
    pf1 = primeFactors(num1)
    pf2 = primeFactors(num2)
    for pf in pf1:
        if pf in pf2:
            return False
    return True

def pickE(num):
    e = START_E
    while not isRelativelyPrime(e,num):
        e += 1
    return e

def extendedEuclydian(a,b):
    if b == 0:
        return (1,0)
    else:
        (q,m) = a // b, a%b
        (x,y) = extendedEuclydian(b,m)
        return (y,x-y*q)

def printAllValues(prime1, prime2, phiOfn, e, d):
    print("The two prime numbers: *%d* *%d*"%(prime1,prime2))
    print("Phi of n:       ", phiOfn)
    print("E and D sequitor:      *%d* *%d*"%(e, d))

def RSAencrypter():
    p,q = pickTwoPrimes()
    phiOfn = (p-1)*(q-1)
    e = pickE(phiOfn)
    (x,y) = extendedEuclydian(e,phiOfn)
    d = x
    printAllValues(p,q,phiOfn,e,d)

RSAencrypter()
