# Solve the problem from the third set here problem 15
"""
the function returns the sum of the divisors of a number n(without including n)
s: natural number, contains the sum
"""


def sumdiv(n):
    s = 0
    for i in range(1, n // 2 + 1):
        # the greatest divisor of a number(excluding itself) cannot be greater than the halved number
        if n % i == 0:
            s = s + i
    return s
"""
-the function returns the largest perfect number(equal to the sum of its divisors except itself) smaller than n
-if there are no such numbers then n becomes 0 and the functions ends due to the second condition 
 on the while loop which is not satisfied
"""

def perfect(n):
    ok = 1
    while ok == 1 and n != 0:
        n = n - 1
        if sumdiv(n) == n:
            ok = 0
    return n


def mesaj(n):
    if perfect(n) == 0:
        print("No numbers satisfy the condition") #a message is displayed if there are no numbers which satisfy the condition
    else:
        print(perfect(n)) #the desired number is returned if it exists


if __name__ == '__main__':
    mesaj(int(input('enter a natural value'))) #prints the desired result
