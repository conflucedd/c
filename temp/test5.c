#include <stdio.h>

#define N

int main(void)
{
	int Sum = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < i * i; j++)
		{
			for (int k = 0; k < j; k++)
			{
				Sum++;
			}
		}
	}

}
