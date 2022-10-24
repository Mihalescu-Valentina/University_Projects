#include <stdio.h>
typedef struct {
	int arr[101], len;

}Vector;

//this function returns the number of zeros from a variable
int nr_of_zeros(int product)
{
	int nr = 0;
	while (product != 0)
	{
		if (product % 10 == 0)
			nr = nr + 1;
		product = product / 10;


	}
	return nr;

}



Vector read_until_zero()
{
	Vector v;
	int x;
	v.len = 0;
	scanf("%d", &x);
	while (x != 0)
	{
		v.arr[v.len++] = x;
		scanf("%d", &x);


	}
	return v;
}

void menu()
{
	printf("1: Read a sequence of natural numbers (sequence ended by 0) and determine the number of 0 digits of the product of the read numbers.\n ");
	printf("2: Given a vector of numbers, find the longest contiguous subsequence such that the sum of any two consecutive elements is a prime number.\n ");
	printf("5: Exercise 5 suplimnetary \n");
	printf("6: Exit. \n");
}

int product_of_numbers(Vector v)
{
	int product = 1;
	for (int i = 0; i < v.len; ++i)
		product *= v.arr[i];

	return product;
}

