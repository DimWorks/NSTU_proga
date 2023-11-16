#include <stdio.h>
#include <string.h>

char* reduction(char* input)
{
	char* text = _strdup(input);
	printf("Input(%d): %s\n", strlen(text), text);

	while ((strlen(text) % 8) != 0)
	{
		text = strcat(text, "#");
	}
	
	char output[9];
	int len = strlen(text) / 8;

	for (int i = 1; i < 9; i++)
	{
		int res = 0;
		for (int j = 0; j < (len * i); j++)
		{
			res += text[j] * text[j] * j;
		}

		res %= 1000;	
		int resulto = 0;

		while (res > 0) {
			resulto += res % 10;
			res /= 10;
		}
		resulto += 60;
		output[i - 1] = (char)resulto;
	}
	output[8] = '\0';
	return output;
}



int main()
{
	char* input = "https://www.youtube.com/watch?v=GFq6wH5JRA2";

	//char input[1000];
	//scanf("%s", &input);

	printf("Output: %s\n", reduction(input));
	//reduction(kl);
}