#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 5

int search(int source[N], int start, int end); // include start and end

int main(void)
{
	int a[N];
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &a[i]);
	}

	printf("%d", search(a, 0, N - 1));


	return 0;

}

int search(int source[N], int start, int end)
{
	int index_mid = (start + end) / 2;
	int value_mid = index_mid + 1; // the serial of element in the array
								   // which start from 1
	
	if (source[index_mid] == value_mid)
	{
		return value_mid;
	}
	else if(start == end) // the condition does not exist
	{
		return -1;
	}
	else if (source[index_mid] > value_mid)
	{
		return search(source, start, index_mid - 1);
	}
	else // a[index_mid] < value_mid
	{
		return search(source, index_mid + 1, end);
	}
}
