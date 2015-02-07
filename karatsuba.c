#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define CHAR2INT(c)		((c) - 0x30)
#define INT2CHAR(i)		((i) + 0x30)
#define MAX_DIM			50


typedef struct
{
	uint8_t dim;
	int8_t numb[MAX_DIM];
}verylong_t;

void vl_init(char *str_number, verylong_t *number)
{
	size_t len = strlen(str_number);
	int8_t *ptr = number->numb;
	number->dim = len;
	while(len > 0)
	{
		*ptr++ = str_number[len-1];
		--len;
	}
}

void vl_print(verylong_t *number)
{
	uint8_t i;
	for(i = number->dim; i > 0; i--)
	{
		putchar(number->numb[i-1]);
	}
	putchar('\n');
}

void vl_sum(verylong_t *op1, verylong_t *op2, verylong_t *result)
{
	uint8_t i = 0;
	uint8_t sum_len = 0;
	uint8_t res_len = 0;
	uint8_t carry = 0;
	
	sum_len = op2->dim;
	res_len = op1->dim;
	if(op1->dim > op2->dim)
	{
		sum_len = op1->dim;
		res_len = op2->dim;
	}

	for(i = 0; i < sum_len; i++)
	{
		result->numb[i] = op1->numb[i] + op2->numb[i] + carry;
		carry = 0;
		if(result->numb[i] > 9)
		{
			carry = 1;
			result->numb[i] -= 10;
		}
	}

	if(carry != 0)
	{
		result->numb[i+1] += carry;
		if(res_len < i+1)
		{
			res_len += 1;
		}
	}

	result->dim = res_len;
}

int main(void)
{
	verylong_t num1, num2, result;
	vl_init("1", &num1);
	vl_init("3", &num2);
	vl_print(&num1);
	vl_print(&num2);
	vl_sum(&num1, &num2, &result);
	vl_print(&result);

	return 0;
}

