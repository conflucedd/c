#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	FILE * in;
	if ((in = fopen("a", "r")) == NULL)
	{
		exit(1);
	}
}