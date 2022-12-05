#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int str_num, char * str_arg [])
{
	FILE * in, * out;

	if(str_num != 1) // read in
	{
		exit(1);
	}
	if ((in = fopen(str_arg[1], "rb") == NULL))
	{
		exit(2);
	}

	char * outfile_name = strcat(str_arg[1], "_with_incl");
	if ((out = fopen(outfile_name, "wxb") == NULL))
	{
		exit(4);
	}


	char ch; // start to check
	fpos_t *include_pos[100]; int incpos_index = 0;

	while ((ch = getc(in)) != EOF)
	{
		if (ch == '#' && check_include(in) == true)
		{
			fgetpos(in, include_pos[incpos_index]);
			incpos_index++;
		}
	}

	
	for (int i = 0; i < incpos_index; i++) // start to manipulate
	{
		if(check_std(in, include_pos[i]) == true)
		{
			put_in(in, getFile(in, include_pos[i]), temp);
		}
	}

	return 0;
	

	



	


	
}
