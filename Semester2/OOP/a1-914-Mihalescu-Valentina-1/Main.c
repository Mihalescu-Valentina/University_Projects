#include <stdio.h>

typedef struct {
	int arr[101], len;

}Vector;

int nr_of_zeros(int product);
Vector read_until_zero();
void menu();
int product_of_numbers(Vector v);
Vector read_n_numbers(n);
void longest_subsequence_prime_sum(Vector v,int *start_max,int *end_max);
void print_longest_sequence(Vector v,int start_max,int end_max);
float x_at_the_power_n(float x, unsigned n);

int main()
{
	int x = 0, option = 0, cont = 1, nr_zeros = 0, product = 1, n = 0, start_max, end_max;
	float result = 0.0,var;
	unsigned len = 0;
	Vector v;
	while (cont == 1)
	{
		printf("\n");
		menu();
		scanf("%d", &option);
		switch (option) {
		case 1:

			v = read_until_zero();
			product = product_of_numbers(v);
			nr_zeros = nr_of_zeros(product);
			printf("The product is %d . The number of zeros from the product is : % d\n", product, nr_zeros);
			break;

		case 2:
			printf("n is: ");
			scanf("%d", &n);
			v = read_n_numbers(n);
			longest_subsequence_prime_sum(v, &start_max, &end_max);
			print_longest_sequence(v, start_max, end_max);
			break;



		case 5:
			printf("n is: ");
			scanf("%u", &len);
			printf("x is equal to: ");
			scanf("%f", &var);
			result = x_at_the_power_n(var, len);
			printf("x at the power n is equal to %f", result);
			break;

		case 6:
			cont = 0;
			break;


		default:
			printf("You entered a wrong option!");
			break;


		}
	}

		return 0;
	
}