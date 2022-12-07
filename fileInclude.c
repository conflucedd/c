#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

bool process_complete = false;
char * process(char *);

int count_str(char *);
void to_string(FILE *); // return char count
void to_file(char *);

bool check_include(char *);
long process_size(char *);
void put_in(char * in, char * out, fpos_t *);

int main(int str_num, char * str_arg [])
{
	FILE * in;
	FILE * out;
	
	char * outfile_name = strcat(str_arg[1], "_with_incl");
	if(str_num != 1) // read in
	{
		exit(1);
	}
	if ((in = fopen(str_arg[1], "r") == NULL))
	{
		exit(2);
	}
	if ((out = fopen(outfile_name, "wx") == NULL))
	{
		exit(3);
	}

	char * input_str;
	to_string(in, input_str);
	to_file(process(input_str));

	if (fclose(in) != 0)
	{
		exit(4);
	}
	if (fclose(out) != 0)
	{
		exit(5);
	}

	return 0;
}

extern process_complete; // default false
char * process(char * in_str)
{
	char * res_str;

	if (check_include(in_str) == true && process_complete == false)
	{
		if ((char * temp = (char *) malloc(process_size(in_str) * sizeof char)) == NULL)
		{
			exit(6);
		}
		put_in(in_str, temp);
		free(in_str);
		process(temp);
	}
	else
	{
		process_complete = true;
		res_str = temp;
		return res_str;
	}
}

void to_string(FILE * in)
{
	int count = count_str(in);
	char * 
}

char ch; // start to check
	fpos_t include_pos [100]; int incpos_index = 0;

	while ((ch = getc(in)) != EOF)
	{
		if (ch != '#' && check_include(in) == true)
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

	if (fclose(in) != 0)
	{
		exit(4);
	}
	

	return 0;

