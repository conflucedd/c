#include <stdio.h>

#define RES_SIZE 1000

int count = 0;

void process(long a, char * result);

int main(void)
{
	long a; scanf("%ld", &a);

	char result[RES_SIZE];
	process(a, result);

	for (int i = count; i >= 0; i--)
	{
		putchar(result[i]);
	}

	return 0;
}

char char_set[] = "0123456789ABCDE";
extern int count; // default 0
void process(long a, char * result)
{	
	if (a >= 16)
	{
		result[count] = char_set[a % 16];
		count++;

		process (a / 16, result);
	}
	else
	{
		result[count] = char_set[a % 16];
		
		return;
	}
}