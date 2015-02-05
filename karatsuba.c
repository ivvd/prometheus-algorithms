#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define CHAR2INT(c)		((c) - 0x30)
#define INT2CHAR(i)		((i) + 0x30)

void ch_sum(char *num1, char *num2, uint8_t dim, char *result);

char result[100];

int main(void)
{
	printf("Hello!\n");
	char num1[] = "123";
	char num2[] = "678";
	printf("First number is %s \n", num1);
	printf("Second number is %s \n", num2);
	ch_sum(num1, num2, strlen(num1), result);
	printf("Result is %s \n", result);
	return 0;
}

void ch_sum(char *num1, char *num2, uint8_t dim, char *result)
{
	int16_t i = 0;
	uint8_t carry = 0;
	uint8_t new_carry = 0;
	memset(result, ' ', dim+1);
	for(i = dim - 1; i >= 0; i--)
	{
		uint8_t temp = CHAR2INT(num1[i]) + CHAR2INT(num2[i]);

		new_carry = 0;

		if(temp > 9)
		{
			new_carry = 1;
			temp -= 10;
		}
		printf("%i\n", temp);
		result[i+1] = INT2CHAR(temp + carry);
		carry = new_carry;
	}
	if(carry != 0)
	{
		//printf("%i\n", i);
		result[i+1] = INT2CHAR(carry);
	}
}

