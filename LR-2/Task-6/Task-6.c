#include "hash_table.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char* append(char* s, char c)
{
	s[0] = c;
	s[1] = '\0';
	return s;
}

bool isIsomorphic(char* first, char* second)
{
	int size1 = strlen(first);
	int size2 = strlen(second);

	if (size1 != size2)
	{
		return false;
	}

	HT* table = create_table(size2);

	char fst[2] = " ", snd[2] = " ";
	strcpy(fst, append(fst, first[0]));
	strcpy(snd, append(snd, second[0]));
	ht_insert(table, fst, snd);

	for (int i = 1; i < strlen(first); i++)
	{
		strcpy(fst, append(fst, first[i]));
		strcpy(snd, append(snd, second[i]));

		if (isKey(table, fst))
		{
			if ( strcmp(ht_search(table, fst), snd) != 0)
			{
				return false;
			}
		}
		else
		{
			ht_insert(table, fst, snd);
		}
	}

	return true;

}

int main()
{
	char* first = "ABCA";
	char* second = "XYZX";

	if (isIsomorphic(first, second))
	{
		printf("%s and %s are Isomorphic\n", first, second);
	}
	else
	{
		printf("%s and %s are NOT Isomorphic\n", first, second);
	}

}