#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define INPUT_FILE_NAME_LENGTH 50 // not include '\0'
#define RES_NUM_LIM 1000
#define RES_NAME_LEN_LIM_LIN 50 // not include '\0'

bool process_complete = false;
char * process(char *);

long count_str(const char *);
long count_file_str(FILE *); // do not include EOF, will invoke rewind() at start and end

char * to_string(FILE *);
void to_file(const char *, FILE *);

int check_include(const char *, long * loc, char res [][RES_NAME_LEN_LIM_LIN + 1]);
void put_in(const char * in, char ** out); // malloc for *out

void jump_blank(const char * in, long * index);

int main(const int str_num, char * str_arg [])
{
// set variables and open files
	FILE * in;
	FILE * out;
	
	char outfile_name[INPUT_FILE_NAME_LENGTH + 10]; // 10 is the char num of "_with_incl"
	strncpy(outfile_name, str_arg[1], RES_NAME_LEN_LIM_LIN);
	strcat(outfile_name, "_with_incl");
	if(str_num != 2) // read in
	{
		exit(1);
	}
	if ((in = fopen(str_arg[1], "r")) == NULL)
	{
		exit(2);
	}
	if ((out = fopen(outfile_name, "w")) == NULL)
	{
		exit(3);
	}


// start manipulate and write result
	char * input_str = to_string(in);
	char * output_str = process(input_str);
	to_file(output_str, out);
	free(output_str);


// close file and make the end
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
// open the include_rsc_file
	int count;
	long pos[RES_NUM_LIM]; // pos is the position of the last character : '\0' or '\n'
	char res_name[RES_NUM_LIM][RES_NAME_LEN_LIM_LIN + 1];
	
	count = check_include(in, pos, res_name);
	if (count == 0) // that indicates process has completed
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


// calculate and set needed values; malloc mem for *out
	long pos_pre[count + 1]; // pos_pre is the position of the firest char in the current line
	for (int i = 0; i < count; i++)
	{
		for (pos_pre[i] = pos[i] - 1; // - 1 because of current position is '\n' or '\0'
				pos_pre[i] >= 0 && in[pos_pre[i]] != '\n';
					pos_pre[i]--)
		{
			continue;
		}
		pos_pre[i]++; // for loop feature
	}
	pos_pre[count] = count_str(in) + 2; // define this for later comparison, to print the last thing in "in", +2 because of '\0' and the for loop feature

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
	
	int bet_sum = 0; // bet_sum is the num of char being deleted
	for (int i = 0; i < count; i++)
	{
		bet_sum += pos[i] - pos_pre[i];
	}
	
	long process_size =  count_str(in) - bet_sum + res_size_sum + 1; // + 1 because of the '\0' at the end
	if ((*out = malloc(process_size * sizeof(char))) == NULL)
	{
		exit(7);
	}
	

// start to manipulate and write to *out
	long out_index = 0;
	for (long in_index = 0 ; in_index < pos_pre[0]; in_index++, out_index++) // print thing before the first res_file
	{
		(*out)[out_index] = in[in_index];
	}
	for (int i = 0; i < count; i++) // print later things
	{		
		for (long res_index = 0; res_index < res_size[i]; res_index++, out_index++) // add i-th include file
		{
			(*out)[out_index] = getc(res_in[i]);
		}
		for (long in_index = pos[i]; in_index < pos_pre[i + 1]; in_index++, out_index++) // use pos[i] for the '\n'; use <= because of '\0' at end the out string
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
int check_include(const char * in, long pos[], char res_name [][RES_NAME_LEN_LIM_LIN + 1])
{
	int count = -1; // the num of include file, will start from 0 because of ++

	for (long index = 0; in[index] != '\0'; index++)
	{
	// check "#include
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


	// check resources files' name and write position
		jump_blank(in, &index);

		bool end = false; // indicates if it has '>' as the end
		bool end_std = true; // indicates if there is char after '>' and before '\n' or '\0', if have, then false.
		if (in[index] == '<')
		{
			index++;

			int index_2;
			for (index_2 = 0; in[index] != '\0' && in[index] != '\n' && index_2 < RES_NAME_LEN_LIM_LIN; index_2++, index++) // copy res file name; index_2 have go after file name
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


// set process state
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
