from timeit import timeit
from timeit import Timer
from linked_list import *
import math
import sys

class Sieve_of_Eratosthenes:
    #Method:Constructor for sieve class
    #Pre:   The n (non-inclusive) is given
    #Att.s: created in this method
    #Post:  self.primes is created
    def __init__(self, n):
        self.n = n
        self.linked_list = LinkedList()
        self.primes = LinkedList()
        for i in range(2,n):
            self.linked_list.add_last(i)
        self.find_all_primes()

    #Method:This method finds all of the primes in the list
    #Pre:   Method is called
    #Att.s: self.linked_list (type=LinkedList)
    #       self.primes      (type=LinkedList)
    #Post:  The self.primes list is created
    def find_all_primes(self):
        while self.linked_list.size > 0:
            value = self.linked_list.remove_first()
            self.primes.add_last(value)
            self.remove_multiples(value)

    #Method:This method removes all multiples of the value given from
    #       self.linked_list 
    #Pre:   value (type=Integer) is given
    #Att.s: self.linked_list (type=LinkedList)
    #Post:  All of the multiples of value are removed from
    #       self.linked_list 
    def remove_multiples(self, value):
        for item in self.linked_list:
            if item % value == 0:
                self.linked_list.remove(item)

    #Method:This method returns the string of the self.primes
    #       LinkedList 
    #Pre:   Print is called
    #Att.s: self.primes (type=LinkedList)
    #Post:  string version of self.primes
    def __str__(self):
        return str(self.primes)

    #Method: This method checks if the integer is a prime number
    #Pre:    Positive integer
    #Att.s:  
    #Post:   Returns True or False
    def prime_check(self, integer):
        boolean = True
        for i in range(2,integer):
            if (integer % i == 0):
                boolean = False
        return boolean

    #Method: This appends prime numbers to a new list
    #Pre:    This method is called
    #Att.s:  self.n (type=integer)
    #Post:   A num_list is created and if the number is prime
    #        it is appended
    def brute_force_find_primes(self):
        num_list = []
        for i in range(2,self.n):
            if self.prime_check(i):
                num_list.append(i)

    #Method: This method times the Sieve of Eratosthenes Algorithm
    #Pre:    This method is called
    #Att.s:  self.n (type=integer)
    #Post:   Returns the amount of time taken to run the algorithm
    def time_the_sieve_of_eratosthenes(self):
        self.__init__(self.n)
        timer = Timer(self.find_all_primes)
        a = timer.timeit(100)
        return a

    #Method: This method times the Brute Force Algorithm
    #Pre:    This method is called
    #Att.s:  self.n (type=integer)
    #Post:   Returns the amount of time taken to run the algorithm
    def time_the_brute_forcy_stuff(self):
        self.__init__(self.n)
        timer = Timer(self.brute_force_find_primes)
        a = timer.timeit(100)
        return a

    #Method: Takes the times and stores them in variables and then
    #        prints them
    #Pre:    This method is called
    #Att.s:  None
    #Post:   Prints each time taken for the two algorithms being
    #        compared
    def time_some_stuff(self):
        a = self.time_the_sieve_of_eratosthenes()
        b = self.time_the_brute_forcy_stuff()
        print("Eratosthenes: ", a)
        print("Brute force:  ", b)

a = Sieve_of_Eratosthenes(104)
sys.stdout.flush()
for i in range(10):
    a.time_some_stuff()
