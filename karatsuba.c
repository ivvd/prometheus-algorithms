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
	memset(ptr, 0, MAX_DIM);
	while(len > 0)
	{
		*ptr++ = CHAR2INT(str_number[len-1]);
		--len;
	}
}

void vl_print(verylong_t *number)
{
	uint8_t i;
	for(i = number->dim; i > 0; i--)
	{
		putchar(INT2CHAR(number->numb[i-1]));
	}
	putchar('\n');
}

void vl_sum(verylong_t *op1, verylong_t *op2, verylong_t *result)
{
	uint8_t i = 0;
	uint8_t sum_len = 0;
	uint8_t carry = 0;
	
	if(op1->dim > op2->dim)
	{
		sum_len = op1->dim;
	}
	else
	{
		sum_len = op2->dim;
	}
	
	//printf("sum_len=%i\n", sum_len);

	for(i = 0; i < sum_len; i++)
	{
		result->numb[i] = op1->numb[i] + op2->numb[i] + carry;
		carry = 0;
		if(result->numb[i] > 9)
		{
			//printf("%i\n", result->numb[i]);
			carry = 1;
			result->numb[i] -= 10;
		}
	}

	if(carry != 0)
	{
		//printf("carry after cycle %i\n", carry);
		//printf("i=%i\n", i);
		//printf("result->numb[i]=%i\n", result->numb[i]);
		result->numb[i] += carry;
		//printf("result->numb[i]=%i\n", result->numb[i]);
		if(sum_len < i+1)
		{
			sum_len += 1;
		}
	}

	result->dim = sum_len;
	
	//printf("result->dim=%i\n", result->dim);
}

int main(void)
{
	verylong_t num1, num2, result;
	vl_init("123456789923456789", &num1);
	vl_init("923456789678324098", &num2);
	vl_init("0", &result);
	vl_print(&num1);
	vl_print(&num2);
	vl_sum(&num1, &num2, &result);
	vl_print(&result);

	return 0;
}

