# Solve the problem from the first set here-ex 3
"""
the function returns the number of zeroes from n
n: natural number
k: the number of zeroes
aux: an additional variable initially equal to n which will be used in order to keep the value of n
"""


def numberofzeroes(n):
    k = 0
    aux = n
    while aux != 0:
        if aux % 10 == 0:
            k = k + 1
        aux = aux // 10
    return k


"""
the function returns the minimal number which can be formed with the digits of n
k: natural value initialised with the number of zeroes from n
m: natural value, the minimal number formed(the result of the problem)
i: natural value used to create the desired number from the smallest digit: 1 to the largest: 9
d: natural value used to store digits of n
the function takes every digit from 1 to 9 and checks its existence in n
"""


def minimalnr(n):
    k = numberofzeroes(n)
    m = 0
    for i in range(1, 10):
        aux = n
        while aux != 0:
            d = aux % 10
            if d == i:  # the function takes every digit from 1 to 9 and checks its existence in n
                m = m * 10 + i
                # when the minimum digit is found, k zeroes are added to m;
                # this while loop will be run only for the minimum digit
                while k != 0:
                    m = m * 10
                    k = k - 1
            aux = aux // 10
    return m


if __name__ == '__main__':
    print(minimalnr(int(input('enter a natural value'))))  # prints the result of the problem
