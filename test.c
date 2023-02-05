#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <time.h>

#define N 5

int main(void)
{
	srand((unsigned) time(NULL));

	int a[N];
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &a[i]);
	}


	int sum_min = 0;
	int sum_temp = 0;
	for (int i = 0; i < N; i++)
	{
		if (sum_temp < 0)
		{
			sum_temp += a[i];
		}
		else
		{
			sum_temp = a[i]; // sum from this
		}

		if (sum_temp < sum_min)
		{
			sum_min = sum_temp;
		}
	}

	
	printf("%d\n", sum_min);


	return 0;
}
