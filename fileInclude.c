#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool process_complete = false;
char * process(char *);

long count_str(char *);
long count_file_str(FILE *);

char * to_string(FILE *);
void to_file(char *);

bool check_include(char *, long * loc, char (* res) [20]);
long process_size(char *);
void put_in(char * in, char * out);

void jump_blank(char * in, int * index);

int main(int str_num, char * str_arg [])
{
	FILE * in;
	FILE * out;
	
	char * outfile_name = strcat(str_arg[1], "_with_incl");
	if(str_num != 1) // read in
	{
		exit(1);
	}
	if ((in = fopen(str_arg[1], "r")) == NULL)
	{
		exit(2);
	}
	if ((out = fopen(outfile_name, "wx")) == NULL)
	{
		exit(3);
	}

	char * input_str = to_string(in);
	char * output_str = process(input_str);
	to_file(output_str);

	free(input_str);
	free(output_str);

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

extern bool process_complete; // default false
char * process(char * in_str)
{
	char * temp;

	if (check_include(in_str) == true && process_complete == false)
	{
		if ((temp = (char *) malloc(process_size(in_str) * sizeof(char))) == NULL)
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
		return in_str;
	}
}


long count_file_str(FILE * in)
{
	char ch;
	long index;
	for (index = 0; (ch = getc(in)) != EOF; index++)
	{
		continue;
	}

	return index; // include '\0' at end
}

char * to_string(FILE * in)
{
	int count = count_file_char(in);
	char * ret_val = malloc(count * sizeof(char));
	
	char ch;
	long index;
	for (index = 0; (ch = getc(in)) != EOF; index++)
	{
		ret_val[index] = ch;
	}
	ret_val[index] = '\0';

	return ret_val;
}

long count_str(char * in)
{
	long index;
	for (index = 0; in[index] != '\0'; index++)
	{
		continue;
	}

	return index; // include '\0'
}

void put_in(char * in, char * out)
{
	long * pos = check_include(in);
	
	
}

void jump_blank(char * in, int * index);
{
	int index_2;
	for (index_2 = 0; in[*index + index_2] != '\0' && isblank(in[*index + index_2]) == true; index_2++)
	{
		continue;
	}
	*index += index_2;
}

bool check_include(char * in, long * pos, char (* res) [8])
{
	bool ret_val = false;
	int res_index = -1; // will start from 0 because of ++

	for (long index = 0; in[index] != '\0'; index++)
	{
		if (in[index] = '\n')
		{
			jump_blank(in, [&index]);
		}

		if (in[index] != '#')
		{
			continue;
		}
		
		index++;
		jump_blank[in, &index];

		char temp_for_cmp[8] = { [7] = '\0' };
		for (int i = 0; i < 7 && in[index] != EOF; i++, index++)
		{
			temp_for_cmp[i] = in[index];
		}
		if(strcmp(temp_for_cmp, "include") == 0)
		{
			count++;
			index += 7;
		}
		else
		{
			continue;
		}

		jump_blank[in, &index];

		bool end = false;
		bool end_std = true;
		if (in[index] = '<')
		{
			int index_2;
			for (index_2 = 1; in[index] != '\0' && in[index] != '\n' && i < 18; index_2++, index++)
			{
				if (in[index] != '>')
				{
					res[count][index_2] = in[index];
				}
				if (in[index] == '>')
				{
					end = true;
				}
			}
			res[count][index_2] = '\0';

			for (int i = 0; in[index] != '\0' && in[index] != '\n'; i++, index++)
			{
				if (isblank(in[index] == false))
				{
					end_std = false;
				}
			}
		}

		if ((end && end_std) != true)
		{
			count--;
		}
	}

	return ret_val;
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

