#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define INPUT_FILE_NAME_LENGTH 20
#define RSC_NUM 10
#define RSC_NAME_LEN 20

bool process_complete = false;
char * process(char *);

long count_str(const char *);
long count_file_str(FILE *);

char * to_string(FILE *);
void to_file(const char *, FILE *);

int check_include(const char *, long * loc, char res [][RSC_NAME_LEN]);
void put_in(const char * in, char ** out); // malloc for *out

void jump_blank(const char * in, long * index);

int main(const int str_num, char * str_arg [])
{
	FILE * in;
	FILE * out;
	
	char outfile_name[30];
	strncpy(outfile_name, str_arg[1], 19);
	strcat(outfile_name, "_with_incl");
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
		return process(temp);
	}
	else
	{
		return in_str;
	}
}


long count_file_str(FILE * in) // do not include EOF
{
	rewind(in);

	char ch;
	long index;
	for (index = 0; (ch = getc(in)) != EOF; index++)
	{
		continue;
	}

	rewind(in);

	return index;
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

long count_str(const char * in) // do not include '\0'
{
	long index;
	for (index = 0; in[index] != '\0'; index++)
	{
		continue;
	}

	return index;
}

void put_in(const char * in, char ** out) // will malloc mem for *out
{
	int count;
	long pos[RSC_NUM + 1]; // pos is the position of the last character : '\0' or '\n', index add one for later comparison
	char res_name[RSC_NUM][RSC_NAME_LEN];
	
	count = check_include(in, pos, res_name);
	if (count == 0)
	{
		*out = malloc(count_str(in) * sizeof(char)); // because of the free() in recycle of process()
		strcpy(*out, in);

		return;
	}

	FILE * res_in [count];
	for (int i = 0; i < count; i++)
	{
		if ((res_in[i] = fopen(res_name[i], "r")) == NULL)
		{
			exit(6);
		}
	}

	
	long pos_pre[RSC_NUM + 1]; // pos_pre is the position of the firest chat in the current line, index add one for later manipulation
	int count_bet[RSC_NUM]; // count_bet is the current line char num

	for (int i = 0; i < count; i++)
	{
		for (pos_pre[i] = pos[i] - 1; // - 1 because of current position is '\n' or '\0'
				pos_pre[i] >= 0 && in[pos_pre[i]] != '\n';
					pos_pre[i]--)
		{
			continue;
		}
		pos_pre[i]++; // for loop feature

		count_bet[i] = pos[i] - pos_pre[i] + 1;
	}

	long res_size[count];
	for (int i = 0; i < count; i++)
	{
		res_size[i] = count_file_str(res_in[i]);
	}
	long res_size_sum = 0;
	for (int i = 0; i < count; i++)
	{
		res_size_sum += res_size[i];
	}

	int bet_sum = 0;
	for (int i = 0; i < count; i++)
	{
		bet_sum += count_bet[i];
	}
	
	long process_size =  count_str(in) - bet_sum + res_size_sum + 1; // + 1 because of the '\0' at the end
	if ((*out = malloc(process_size * sizeof(char))) == NULL)
	{
		exit(7);
	}

	pos[count] = process_size; // mark the last pos for later namipulation
	for (int i = 0; i < count; i++)
	{
		long out_index = 0;
		for (long in_index = 0; in_index < pos_pre[i] && out_index < pos_pre[i]; in_index++, out_index++)
		{
			(*out)[out_index] = in[in_index];
		}
		for (long in_index = 0; in_index < res_size[i]; in_index++, out_index++) // add include file
		{
			(*out)[out_index] = getc(res_in[i]);
		}
		for (long in_index = pos[i]; in_index <= count_str(in); in_index++, out_index++) // use pos[i] for the '\n'; use <= because of '\0' at end the out string
		{
			(*out)[out_index] = in[in_index];
		}
	}
}

void jump_blank(const char * in, long * index) // post it to the first non-blank or '\0' (current position must be blank)
{
	int index_2;
	for (index_2 = 0; in[*index + index_2] != '\0' && isblank(in[*index + index_2]) == true; index_2++)
	{
		continue;
	}
	*index += index_2;
}

extern bool process_complete; // default false
int check_include(const char * in, long pos[], char res_name [][RSC_NAME_LEN])
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
		
		index++; // go to first blank (if have)
		jump_blank(in, &index);

		char temp_for_cmp[8] = { [7] = '\0' };
		for (int i = 0; i < 7 && in[index] != EOF; i++, index++) // have passed to the first char after include
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
			for (index_2 = 0; in[index] != '\0' && in[index] != '\n' && index_2 < RSC_NAME_LEN; index_2++, index++) // index_2 have go after file name
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
			pos[count] = index; // current position is '\n' or '\0' at current line last
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
