#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void swap(int *, int *);

int main(void)
{
// set rand seed
	srand((unsigned) time(NULL));


// set and initialize variables
	int N;
	scanf("%d", &N);

	int a[N];
	for (int i = 0; i < N; i++)
	{
		a[i] = i + 1;
	}


// start manipulate
	for (int i = 0; i < N; i++)
	{
		swap(&a[i], &a[rand() % (i + 1)]); // rand() % (i + 1) belog in 0 to "i"
	}


// print result
	for (int i = 0; i < N; i++)
	{
		printf("%d\n", a[i]);
	}


	return 0;
}


void swap(int *a, int *b)
{
	static int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}
