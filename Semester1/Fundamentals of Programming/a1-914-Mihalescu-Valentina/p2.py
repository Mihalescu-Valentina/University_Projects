# Solve the problem from the second set here-problem 7
from math import sqrt  # we import the math library in order to use the sqrt on n

"""
the function checks if n is a prime number
n: natural non-null number
i: variable used to verify if n can be divided to other numbers than 1 and itself
"""


def isprimenumber(n):
    if n < 2:
        return False
    for i in range(2, int(sqrt(n)) + 1):  # we use sqrt for efficiency
        if n % i == 0:
            return False
    return True


"""
the function returns the next prime number after n 
ok: variable used to stop the programm when the desired number is found 
"""


def nextprime(n):
    ok = 1
    while ok == 1:
        n = n + 1
        if isprimenumber(n) == True:
            ok = 0
    return n;


"""
the function returns the twin prime numbers p1 and p2 (their difference is 2) immediately larger than n
n: non-null natural number 
the function works constantly with pairs of two values which are connected to each other
(p1 and p2 are always prime consecutive numbers)
ok: variable used to stop the function when the two desired values are found
"""


def istwin(n):
    ok = 1
    while ok == 1:
        p1 = nextprime(n)
        p2 = nextprime(p1)
        if p2 - p1 == 2:
            ok = 0
        if ok != 0:
            n = p1
            p1 = p2
    return p1, p2


if __name__ == '__main__':
    print(istwin(int(input('enter a non null natural value'))))  # prints the result of the problem
