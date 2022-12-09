#include <stdio.h>
#include <stdlib.h>
#include <string.h>
long count_str(const char * in) // do not include '\0'
{
	long index;
	for (index = 0; in[index] != '\0'; index++)
	{
		continue;
	}

	return index;
}
int main(void)
{
	char a[30] = "sgr";
	printf("%ld\n", count_str(a));
}