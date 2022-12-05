#include <stdio.h>
#include <stdlib.h>

void PrintDigit(int);
void PrintOut(int);

int main(void)
{
	int a;
	scanf("%d", &a);
	
	if (a < 0)
	{
		printf("-");
	}
	PrintOut(abs(a));

	return 0;
}

void PrintDigit(int a)
{
	if (a >= 0 && a <= 9)
	{
		printf("%d", a);
	}
	else
	{
		fprintf(stderr, "Error!");
		exit(1);
	}
}

void PrintOut(int a)
{
	if (a >=0 && a <= 9)
	{
		PrintDigit(a);
		return;
	}
	else
	{
		PrintOut(a / 10);
	}

	PrintDigit(a % 10);
}
