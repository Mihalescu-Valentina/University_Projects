#
# Write the implementation for A2 in this file
#

# UI section
# (write all functions that have input or print statements here).
# Ideally, this section should not contain any calculations relevant to program functionalities
def print_menu():
    print("\tx - exit the program ")
    print("\tadd - add a new complex number to the dictionary")
    print("\t0 - displays all the numbers on the screen")
    print("\t5 - displays the longest sequence of real numbers")
    print("\t11 - displays the longest sequence of numbers having a real part in form of a mountain ")


def printsequenceprop11(n):
    list = secvmax(complexnumbers, n)
    if list[2] - list[1] >= 2:
        print("the longest sequence of complex numbers with the real part in form of a mountain is")
        for i in range(list[1], list[2] + 1):
            print(complex(get_realpart(complexnumbers, i), get_imaginarypart(complexnumbers, i)))

    else:
        print("there are no sequences of complex numbers with the real part in form of a mountain")


def printsequenceprop5(n):
 list = realnumbers(complexnumbers, n)
 if list[2]-list[1]==1 and get_imaginarypart(complexnumbers,list[2])!=0:
     print("the longest sequence of real numbers(imaginary part=0) is")
     print(complex(get_realpart(complexnumbers, list[1]),get_imaginarypart(complexnumbers,list[1])))
 elif list[2]-list[1]==1 and get_imaginarypart(complexnumbers,list[2])==0:
       print("the longest sequence of real numbers(imaginary part=0) is")
       for i in range(list[1], list[2] + 1):
           print(complex(get_realpart(complexnumbers, i), get_imaginarypart(complexnumbers, i)))
 elif list[2]-list[1]>1 :
   print("the longest sequence of real numbers(imaginary part=0) is")
   for i in range(list[1], list[2] + 1):
    print(complex(get_realpart(complexnumbers, i),get_imaginarypart(complexnumbers,i)))


 elif list[2]-list[1]==0 and get_imaginarypart(complexnumbers,n)==0:
     print(complex(get_realpart(complexnumbers,n),get_imaginarypart(complexnumbers,n)))
 elif list[2]-list[1]==0 and get_imaginarypart(complexnumbers,n)!=0:
  print("there are no sequences of real numbers in the dictionary")
 """
 the function prints the numbers from the longest sequence of real numbers by taking into account all the exitsent cases
 param:
 list-a list which stores the values returned in the function realnumbers()
 i-index
 n-the number of values in the dictionary at the moment of printing
 """

def print_typing_error_message():
    """
 It prints an error message for invalid option.
 """
    print('Enter a valid option!')



# Function section
# (write all non-UI functions in this section)
# There should be no print or input statements below this comment
# Each function should do one thing only
# Functions communicate using input parameters and their return values
import random


def randomlist():

    complex = []

    #this function is used to generate 10 random numbers

    for i in range(0, 10):
        realpart = random.randint(-10, 10)
        imaginarypart = random.randint(-10, 10)
        complexnumber = createcomplexnumber(i, realpart, imaginarypart)
        complex.append(complexnumber)
    return complex



def createcomplexnumber(index, realpart, imaginarypart):
    return {'index': index, 'real_part': realpart, 'imaginary_part': imaginarypart}
"""
in this function a dictionary with 3 fields is created in order to store a complex number
"""


def get_imaginarypart(complexnumbers, k):
    return complexnumbers[k]['imaginary_part']
"""
getter function used for security and for storing the imaginary part of a complex number
param:
complexnumbers-the dictionary that stores the complex numbers
k-indicates which one of the complex numbers is used
"""

def get_realpart(complexnumbers, k):
    return complexnumbers[k]['real_part']
"""
getter function used for security and for storing the real part of the complex number
param:
complexnumbers-the dictionary that stores the complex numbers
k-indicates which one of the complex numbers is used
"""


def secvmax(complexnumbers, n):
    """
    the programme returns a tuple with the length of the maximum sequence with the real part in form of a mountain number
    parameters:
    i-natural number,index
    nrmax-the value of the longest sequence
    in-the starting position of the longest sequence
    fin-the final position of the longest sequence
    n-the number of complex numbers from the dictionary at the moment of the operation
    """
    i = 0
    nrmax = 0
    init = 0
    fin = 0
    while i < n - 1:
        k = i
        nr = 0
        while k < n - 1 and get_realpart(complexnumbers, k) < get_realpart(complexnumbers, k + 1):
            nr = nr + 1
            k = k + 1
        while k < n - 1 and get_realpart(complexnumbers, k) > get_realpart(complexnumbers, k + 1) and nr != 0:
            nr = nr + 1
            k = k + 1
        if nr > nrmax:
            nrmax = nr
            init = i
            fin = k
        i = i + 1

    return nrmax, init, fin


def realnumbers(complexnumbers, n):
    """"
    the function returns a tuple with the value of the longest sequence of real numbers,the initial index of the sequence and the end of it
    parameters:
    i-index
    in-the beggining of the longest sequence
    fin-the end of the longest sequence
    """
    i = 0
    nrmax = 0
    init = 0
    fin = 0
    while i < n:
        k = i
        nr = 0
        while k<n and get_imaginarypart(complexnumbers, k) == 0:
            nr = nr + 1
            k = k + 1
        if nr >= nrmax:
            nrmax = nr
            init = i
            fin = k
        i = i + 1
    return nrmax, init, fin


def add_complex_number_to_list(complexnumbers, newcomplexnumber):
 """
 It adds a new complex number at the end of the list.
 :param complex_numbers_list: the list where the new number needs to be added
 :param complex_number: the complex number that needs to be added
 """
 complexnumbers.append(newcomplexnumber)




if __name__ == '__main__':
    """
    parameters:
    complexnumbers is a dictionary which stores the complex numbers, 10 randomly generated and then the user can add more
    option is used for the menu
    i is used as an index that represents the number of the complex number in the dictionary
    this part of the programme represents a menu which makes the communication between the user and the programme easier
    """
    complexnumbers = randomlist()
    i = 9
    while True:
        print_menu()
        option = input('Option: ').lower()
        if option == 'x':
            break
        elif option != 'add' and option != '5' and option != '11' and option!='0': #if the user does not enter a valid value a message of error is displayed
            print_typing_error_message()
            continue
        elif option == 'add':
            i = i + 1
            real_part = int(input('Enter the real part: '))
            imaginary_part = int(input('Enter the imaginary part: '))

            newcomplexnumber = createcomplexnumber(i, real_part, imaginary_part)
            add_complex_number_to_list(complexnumbers, newcomplexnumber)
            print(complexnumbers)

        elif option == '0':
            print(complexnumbers)

        elif option == '5':
            print(complexnumbers)
            printsequenceprop5(i)




        elif option == '11':
            print(complexnumbers)
            printsequenceprop11(i)


        elif option == '11':
            print(complexnumbers)
            printsequenceprop11(i)


