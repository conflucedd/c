#include <stdio.h>
#include <stdbool.h>

void clean_input(void);
void exist(char * laterword, char (*wordlist)[20], int word_num, int wordlist_loc[], bool result[]);

int main(void)
{



//add and test variable
	
	// for the matrix
	int N; // length of the matrix
	scanf("%d", &N);

	char a[N][N]; 
	int temp_scanf;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			while ((temp_scanf = getchar()))
			{
				if(temp_scanf != '\n' && temp_scanf != ' ')
				{
					break;
				}
			}
            
			a[i][j] = temp_scanf;
		}
	}

	
	// for the word
	int M; //number of words
	scanf("%d", &M);
	clean_input();
	
	char word[M][20];
	int wdloc[M]; // the end letter index in word string
	int temp_letter;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if ((temp_letter = getchar()) != '\n')
			{
				word[i][j] = temp_letter;
			}
			else
			{
				word[i][j] = '\0';
				wdloc[i] = j - 1; // for loop feature "- 1"
				break;
			}
		}
	}

	for (int i = 0; i < M; i++) // test input word
	{
		printf("%s %d\n", word[i], wdloc[i]);
	}



// manipulate
	char temp_string_row[20];
	char temp_string_column[20];
	char temp_string_ori1[20];
	char temp_string_ori2[20];
	
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			// convert
			int index;
			int k, m;
			for (index = 0, k = j; k < N; k++, index++)
			{
				temp_string_row[index] = a[i][k];
			}
			temp_string_row[index] = '\0'; // to make the end
			
			for (index = 0, k = i; k < N; k++, index++)
			{
				temp_string_column[index] = a[k][j];
			}
			temp_string_column[index] = '\0';

			for (index = 0, k = i, m = j;
					k < N && m < N && index < 19; // max index is 19
					k++, m++, index++)
			{
				temp_string_ori1[index] = a[k][m];
			}
			temp_string_ori1[index] = '\0';

			for (index = 0, k = i, m = j;
					k >= 0 && m >= 0 && index < 19;
					k++, m--, index++)
			{
				temp_string_ori2[index] = a[k][m];
			}
			temp_string_ori2[index] = '\0';

			
			// check and print
			bool result[M];
			for (int i = 0; i < M; i++)
			{
				result[M] = false;
			}
			
			exist(temp_string_row, word, M, wdloc, result);
			for (int n = 0; n < M; n++)
			{
				if (result[n] == true)
				{
					printf("%s\n", word[n]);
					printf("%d %d\n", i, j);
					printf("%d %d\n\n", i, j + wdloc[n]);
				}
			}

			exist(temp_string_column, word, M, wdloc, result);
			for (int n = 0; n < M; n++)
			{
				if (result[n] == true)
				{
					printf("%s\n", word[n]);
					printf("%d %d\n", i, j);
					printf("%d %d\n\n", i + wdloc[n], j);
				}
			}

			exist(temp_string_ori1, word, M, wdloc, result);
			for (int n = 0; n < M; n++)
			{
				if (result[n] == true)
				{
					printf("%s\n", word[n]);
					printf("%d %d\n", i, j);
					printf("%d %d\n\n", i + wdloc[n], j + wdloc[n]);
				}
			}

			exist(temp_string_ori2, word, M, wdloc, result);
			for (int n = 0; n < M; n++)
			{
				if (result[n] == true)
				{
					printf("%s\n", word[n]);
					printf("%d %d\n", i, j);
					printf("%d %d\n\n", i + wdloc[n], j - wdloc[n]);
				}
			}


		}
	}

	
	
	return 0;
}

void clean_input(void)
{
	while (getchar() != '\n')
	{
		continue;
	}
}

void exist(char * laterword, char (*wordlist)[20], int word_num, int wordlist_loc[], bool result[])
{
	for (int i = 0; i < word_num; i++)
	{
		result[i] = false;
	}
	
	bool found = false;
	for (int r = 0; r < word_num; r++)
    {
        int s; // justify each word from the wordlist with the given string
        for (s = 0; laterword[s] != '\0' && wordlist[r][s] != '\0'; s++)
        {
            found = true;
            if (laterword[s] != wordlist[r][s])
            {
                found = false;
                break;
            }
        }

         if (wordlist_loc[r] == s - 1) // for loop feature
        {
            result[r] = true;
        }
    }
}

