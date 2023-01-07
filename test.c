#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define N 10

bool if_diff(int input, int * array, int input_index);
int main(void)
{
	srand((unsigned)time(NULL));

	int a[N];

	int temp_for_assign;
	for (int i = 0; i < N; i++)
	{
		if (if_diff(temp_for_assign = rand() % N + 1, a, i) == true)
		{
			a[i] = temp_for_assign;
		}
		else
		{
			i--;
			continue;
		}
	}

	for (int i = 0; i < N; i++)
	{
		printf("%d ", a[i]);
	}

	return 0;

}

bool if_diff(int input, int * array, int input_index)
{
	for (int i = 0; i < input_index; i++)
	{
		if (array[i] == input)
		{
			return false;
		}
	}

	return true;
}

