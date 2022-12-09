#include <stdio.h>
#include <stdlib.h>
int main(void)
{
	FILE * in;
	in = fopen("a", "rw");
rewind(in);
}