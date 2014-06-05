#pre: an integer is given
#post: true of false of is_prime
# this function will return a true or false if the number is prime
def prime_check(integer):
    boolean = True
    for i in range(2,integer):
        if (integer % i == 0):
            boolean = False
    return boolean

#pre: the function is called
#post: hello world and other important things are printed
# this function prints hello world and other important things when called
def hello_world():
    for i in range(2,100):
        if prime_check(i):
            print(i)

hello_world()
