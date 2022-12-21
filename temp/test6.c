#include <stdio.h>

#define N

int main(void)
{
	int Sum = 0;
	for (int i = 1; i < N; i++)
	{
		for (int j = 1; j < i * i; j++)
		{
			if (j % i == 0)
			{
				for (int k = 0; k < j; k++)
				{
					Sum++;
				}
			}
		}
	}
}
