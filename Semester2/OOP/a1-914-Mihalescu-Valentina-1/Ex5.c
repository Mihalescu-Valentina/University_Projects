
/*this function calculates x at the power n by taking into account both cases - x even, x odd
* it returns a float value because x is float */

float x_at_the_power_n(float x,unsigned n)
{   
	float result = 1;
    while (n > 0) {
        if (n % 2 == 0) 
        {
            x = x * x;
            n = n / 2;
        }
        else 
        {
            result = result * x;
            n = n - 1;
        }
    }
    return result;
}
	
