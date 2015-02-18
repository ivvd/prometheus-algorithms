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

void vl_sub(verylong_t *op1, verylong_t *op2, verylong_t *result)
{
	uint8_t i = 0;
	uint8_t sub_len = 0;
	uint8_t carry = 0;
	int8_t *op1_ptr = op1->numb; 
	int8_t *op2_ptr = op2->numb;
	
	if(op1->dim > op2->dim)
	{
		sub_len = op1->dim;
	}
	else
	{
		sub_len = op2->dim;
	}
	
	if(op1->numb[sub_len-1] < op2->numb[sub_len-1])
	{
		op1_ptr = op2->numb;
		op2_ptr = op1->numb;
	}

	for(i = 0; i < sub_len; i++)
	{
		//printf("op1[i]=%i; op2[i]=%i\n", op1_ptr[i], op2_ptr[i]);
		result->numb[i] = op1_ptr[i] - op2_ptr[i] - carry;
		carry = 0;
		if(result->numb[i] < 0)
		{
			carry = 1;
			result->numb[i] += 10;
		}
	}

	result->dim = sub_len;
}

void vl_mul10(verylong_t *op1, uint8_t exp, verylong_t *result)
{
	uint8_t i = 0;
	result->dim = op1->dim + exp;
	for(i = exp; i < (op1->dim + exp); i++)
	{
		result->numb[i] = op1->numb[i - exp];
	}
}

void vl_make_half(verylong_t *op1, verylong_t *op2, verylong_t *a, verylong_t *b, verylong_t *c, verylong_t *d)
{
    uint8_t half = 0;
    uint8_t i = 0;
    uint8_t max_dim = op2->dim;

    if(op1->dim > op2->dim)
    {
        max_dim = op2->dim;
    }

    if(max_dim % 2)
    {
        half = (max_dim / 2) + 1;
    }
    else
    {
        half = (max_dim / 2);
    }

    a->dim = b->dim = c->dim = d->dim = half;

    for(i=0; i<half; i++)
    {
        b->numb[i] = op1->numb[i];
    }
    for(i=half; i<op1->dim; i++)
    {
        a->numb[i-half] = op1->numb[i];
    }

    for(i=0; i<half; i++)
    {
        d->numb[i] = op2->numb[i];
    }
    for(i=half; i<op2->dim; i++)
    {
        c->numb[i-half] = op2->numb[i];
    }
}

void vl_mul(verylong_t *op1, verylong_t *op2, verylong_t *result)
{
    verylong_t a, b, c, d;
    verylong_t ac, bd;
    verylong_t a_plus_b, c_plus_d;
    verylong_t ab_mul_cd;
    verylong_t ad_plus_bc;
    verylong_t temp;

    vl_init("0", &a);
    vl_init("0", &b);
    vl_init("0", &c);
    vl_init("0", &d);
    vl_init("0", &ac);
    vl_init("0", &bd);
    vl_init("0", &a_plus_b);
    vl_init("0", &c_plus_d);
    vl_init("0", &ab_mul_cd);
    vl_init("0", &ad_plus_bc);
    vl_init("0", &temp);

    vl_print(op1);
    vl_print(op2);
    printf("\n-----\n");

    if((op1->dim == 1) && (op2->dim == 1))
    {
        int8_t temp;
        temp = op1->numb[0] * op2->numb[0];
        if(temp > 9)
        {
            result->dim = 2;
            result->numb[1] = temp/10;
            result->numb[0] = temp - result->numb[1]*10;
        }
        else
        {
            result->dim = 1;
            result->numb[0] = temp;
        }
        vl_print(result);
        return;
    }

    vl_make_half(op1, op2, &a, &b, &c, &d);
    
    vl_mul(&a, &c, &ac);
    vl_mul(&b, &d, &bd);
    vl_sum(&a, &b, &a_plus_b);
    vl_sum(&c, &d, &c_plus_d);
    vl_mul(&a_plus_b, &c_plus_d, &ab_mul_cd);
    vl_sub(&ab_mul_cd, &ac, &ad_plus_bc);
    vl_sub(&ad_plus_bc, &bd, &ad_plus_bc);

    vl_mul10(&bd, 0, result);
    vl_mul10(&ad_plus_bc, a.dim, &temp);
    vl_sum(&temp, result, result);
    vl_init("0", &temp);
    vl_mul10(&ac, op1->dim, &temp);
    vl_sum(&temp, result, result);

    printf("Result:\n");
    vl_print(&bd);
    vl_print(&ad_plus_bc);
    vl_print(&ac);
    vl_print(result);
    //vl_print(&ad_plus_bc);
}

int main(void)
{
	verylong_t num1, num2, result;
//	vl_init("123456789923456789", &num1);
//	vl_init("923456789678324098", &num2);
//	vl_init("0", &result);
//	vl_print(&num1);
//	vl_print(&num2);
//	vl_sum(&num1, &num2, &result);
//	vl_print(&result);
//
//	vl_init("6857434592", &num1);
//	vl_init("2334654654", &num2);
//	vl_init("0", &result);
//	vl_print(&num1);
//	vl_print(&num2);
//	vl_sub(&num1, &num2, &result);
//	vl_print(&result);
//	
//	vl_init("123", &num1);
//	vl_init("0", &result);
//	vl_print(&num1);
//	vl_mul10(&num1, 3, &result);
//	vl_print(&result);
//	
//    verylong_t a, b, c, d;
//	vl_init("46", &num1);
//	vl_init("134", &num2);
//	vl_init("0", &a);
//	vl_init("0", &b);
//	vl_init("0", &c);
//	vl_init("0", &d);
//	vl_print(&num1);
//	vl_print(&num2);
//    vl_make_half(&num1, &num2, &a, &b, &c, &d);
//	vl_print(&a);
//    vl_print(&b);
//    vl_print(&c);
//    vl_print(&d);

	vl_init("1234", &num1);
	vl_init("5678", &num2);
    vl_print(&num1);
    vl_print(&num2);
	vl_init("0", &result);
    vl_mul(&num1, &num2, &result);
    vl_print(&result);

	return 0;
}

