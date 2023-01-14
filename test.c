#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>

int main(void)
{
// set rand seed
	srand((unsigned) time(NULL));


// set and initialize variables
	int I, J;
	scanf("%d %d", &I, &J);

	int a[J - I];
	
	bool a_used[J - I];
	for (int i = 0; i < J - I; i++)
	{
		a_used[i] = false;
	}
	

// start to manipulate
	int temp_for_assign;
	for (int i = 0; i < J - I; i++)
	{
		temp_for_assign = rand() % (J - I + 1) + I; // "rand() % (J - I + 1)" will be 0 to "J - I"
							    // so temp_for_assign will be "I" to "J"

		if (a_used[temp_for_assign - I] == false)
		{
			a[i] = temp_for_assign;
			a_used[temp_for_assign - I] = true;
		}
		else
		{
			i--;
			continue;
		}
	}


// print the answer
	for (int i = 0; i < J - I; i++)
	{
		printf("%d\n", a[i]);
	}

	return 0;
	
}
