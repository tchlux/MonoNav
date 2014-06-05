import random
import math
RANGE = [11, 200]

# Pre:  An integer is given
# Post: Whether or not the number is prime
def is_prime(num):
    for i in range(2,math.ceil(num**.5)):
        if (num%i) == 0:
            return False
    return True

# Pre:  
# Post: A prime number is returned
def generate_prime_number():
    num = random.randint(RANGE[0], RANGE[1])
    while not is_prime(num):
        num = random.randint(RANGE[0], RANGE[1])
    return num

# Pre:  prime number and possible alpha
# Post: 
def is_ring(prime, alpha):
    seen_values = []
    for i in range(1,prime):
        new_value = ((alpha**i)%prime)
        if new_value in seen_values:
            return False
        else:
            seen_values.append(new_value)
    return True


# Pre:  Prime number
# Post: A ring generator of the prime
def generate_ring_generator(prime, ring=0):
    if ring != 0:
        print("Given:", ring, "Prime:", is_ring(ring))
    ring = prime-1
    all_rings = []
    while ring > 1:
        if is_ring(prime, ring):
#            return ring
            all_rings.append(ring)
        ring -= 1
    return all_rings


if __name__ == "__main__":
    prime = 997#generate_prime_number()
    alphas = generate_ring_generator(prime)
    print("Prime number: ", prime)
    print("Possible rings: ", alphas)
