#include<stdio.h>
#include <math.h>

typedef struct {
	int arr[101], len;

}Vector;




int check_prime(int x)
{
	int i;
	if (x <= 1)
		return 0;

	for (i = 2; i <= sqrt(x); i++)
		if (x % i == 0)
			return 0;
		
	return 1;
	    


}


Vector read_n_numbers(int n)
{
	Vector v = { 0 };
	v.len = n;
	for (int i = 0; i < v.len; i++)
		scanf("%d", &v.arr[i]);
	
	return v;
}


/* This function transmitts using pointers the start and the end index of the longest contiguous subsequence for which 
the sum of any 2 consecutive numbers is a prime number*/
void longest_subsequence_prime_sum(Vector v,int *start_max,int *end_max)
{
	int start = 0, end = 0;
	for (int i = 0; i < v.len-1; i++)
	{
		if (check_prime(v.arr[i] + v.arr[i +1]) == 1)
			end = end + 1;
		else
		{
			if (end - start > *end_max - *start_max)
			{
				*start_max = start;
				*end_max = end;

			}
			start = i + 1;
			end = i + 1;
		}

	}
	if (end - start > *end_max - *start_max)
		{
			*start_max = start;
			*end_max = end;
		}

	
	
}

/*
this function prints the longest contiguous subsequence delimited by end and start which are the values transmitted throug the previous function*/

void print_longest_sequence(Vector v, int start, int end)
{
	for (int i = start; i <= end; i++)
		printf("%d \n", v.arr[i]);
	    

}









	




