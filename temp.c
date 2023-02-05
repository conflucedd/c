#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define N

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
	int mid = (start + end) / 2;

	if (source[mid] == mid)
	{
		return mid;
	}
	else if (source[mid] > mid)
	{
		return search(source, start, mid - 1);
	}
	else // a[mid] < mid
	{
		return search(source, mid + 1, end);
	}
}
