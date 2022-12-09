#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

bool process_complete = false;
char * process(char *);

long count_str(const char *);
long count_file_str(FILE *);

char * to_string(FILE *);
void to_file(const char *, FILE *);

int check_include(const char *, long * loc, char res [][20]);
void put_in(const char * in, char ** out);

void jump_blank(const char * in, long * index);

int main(const int str_num, char * str_arg [])
{
	FILE * in;
	FILE * out;
	
	char * outfile_name = strcat(str_arg[1], "_with_incl");
	if(str_num != 2) // read in
	{
		exit(1);
	}
	if ((in = fopen("a", "r")) == NULL)
	{
		exit(2);
	}
	if ((out = fopen(outfile_name, "w")) == NULL)
	{
		exit(3);
	}

	char * input_str = to_string(in);
	char * output_str = process(input_str);
	to_file(output_str, out);

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

	if (process_complete == false)
	{
		put_in(in_str, &temp);
		free(in_str);
		process(temp);
	}
	else
	{
		return in_str;
	}

	return NULL;
}


long count_file_str(FILE * in)
{
	rewind(in);

	char ch;
	long index;
	for (index = 0; (ch = getc(in)) != EOF; index++)
	{
		continue;
	}

	rewind(in);

	return index; // include '\0' at end
}

char * to_string(FILE * in)
{
	long count = count_file_str(in);
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

long count_str(const char * in)
{
	long index;
	for (index = 0; in[index] != '\0'; index++)
	{
		continue;
	}

	return index; // include '\0'
}

void put_in(const char * in, char ** out) // will malloc mem for *out
{
	int count;
	long pos[10];
	char res_name[10][20];
	
	count = check_include(in, pos, res_name); // at most 10 #include statement
	FILE * res_in [count];
	for (int i = 0; i < count; i++)
	{
		if ((res_in[i] = fopen(res_name[i], "r")) == NULL)
		{
			exit(6);
		}
	}

	long pos_pre[10];
	int count_bet[10] = { 0 };
	for (int i = 0; i < count; i++)
	{
		for (pos_pre[i] = pos[i]; pos_pre[i] >= 0 && in[pos_pre[i]] != '\n'; pos_pre[i]--, count_bet[i]++)
		{
			continue;
		}
	}

	int res_size_sum = 0;
	for (int i = 0; i < count; i++)
	{
		res_size_sum += count_file_str(res_in[i]);
	}

	int bet_sum = 0;
	for (int i = 0; i < 10; i++)
	{
		bet_sum += count_bet[i];
	}
	
	long process_size = (res_size_sum - count) + count_str(in) - (bet_sum - count);
	if ((*out = malloc(process_size * sizeof(char))) == NULL)
	{
		exit(7);
	}

	for (int i = 0; i < count; i++)
	{
		long count_temp = count_file_str(res_in[i]);
		for (int j = 0; j <= pos_pre[i]; j++)
		{
			(*out)[j] = in[j];
		}
		for (int j = pos_pre[i] + 1; j < count_temp; j++)
		{
			(*out)[j] = getc(res_in[i]);
		}
		for (int j = pos_pre[i] + count_temp + 1; j <= process_size; j++)
		{
			(*out)[j] = in[j];
		}	
	}
}

void jump_blank(const char * in, long * index)
{
	int index_2;
	for (index_2 = 0; in[*index + index_2] != '\0' && isblank(in[*index + index_2]) == true; index_2++)
	{
		continue;
	}
	*index += index_2;
}

extern bool process_complete; // default false
int check_include(const char * in, long pos[], char res_name [][20]) // at most 19 char file name
{
	int count = -1; // will start from 0 because of ++

	for (long index = 0; in[index] != '\0'; index++)
	{
		if (in[index] == '\n')
		{
			jump_blank(in, &index);
		}

		if (in[index] != '#')
		{
			continue;
		}
		
		index++;
		jump_blank(in, &index);

		char temp_for_cmp[8] = { [7] = '\0' };
		for (int i = 0; i < 7 && in[index] != EOF; i++, index++)
		{
			temp_for_cmp[i] = in[index];
		}
		if(strcmp(temp_for_cmp, "include") == 0)
		{
			count++;
		}
		else
		{
			continue;
		}

		jump_blank(in, &index);

		bool end = false;
		bool end_std = true;
		if (in[index] == '<')
		{
			index++;

			int index_2;
			for (index_2 = 0; in[index] != '\0' && in[index] != '\n' && index_2 < 19; index_2++, index++)
			{
				if (in[index] != '>')
				{
					res_name[count][index_2] = in[index];
				}
				if (in[index] == '>')
				{
					end = true;
					break;
				}
			}
			res_name[count][index_2] = '\0';

			for (int i = 0; in[index] != '\0' && in[index] != '\n'; i++, index++)
			{
				if (isblank(in[index] == false))
				{
					end_std = false;
				}
			}
		}

		if ((end && end_std) == true)
		{
			pos[count] = index;
		}
		else
		{
			count--;
		}
	}

	if (count == -1)
	{
		process_complete = true;
	}

	return (count + 1);
}

void to_file(const char * in, FILE * out)
{
	for (long i = 0; in[i] != '\0'; i++)
	{
		putc(in[i], out);
	}
}
