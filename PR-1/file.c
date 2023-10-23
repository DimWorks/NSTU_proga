#include "adder.h"
#include <stdio.h>
#include <string.h>

char* decapitation(char* input, char* struc)
{
    char* output = strtok(input, ":");

    if (strcmp(output, struc) == 0)
    {
        return strtok(NULL, ":");
    }
    else
    {
        return NULL;
    }
}

void read_file(char* path, char* struc)
{
    FILE* mf = fopen(path, "r");

    if (!mf)
    {
        printf("ERROR: The file does not exist\n");
        return;
    }

    char mstr[100] = "Start";

    char* estr = "Start";

    while (estr != NULL)
    {
        estr = fgets(mstr, sizeof(mstr), mf);

        char* tmp = decapitation(mstr, struc);

        if (tmp != NULL)
        {
            printf("%s\n", tmp);
        }
    }

    fclose(mf);
}

void write_to_file(char* path, char* struc, char* data)
{
    FILE* mf = fopen(path, "a");

    if (!mf)
    {
        printf("ERROR: Can't open the file\n");
        return;
    }

    /*char* result = struc;
    strcat(&result, ":");
    strcat(&result, data);

    fputs(&result, mf);*/

    strcat(&struc, ":");
    strcat(&struc, data);

    fputs(&struc, mf);

    fclose(mf);
}

/*
int main()
{
    char* path = "data.txt";

    read_file(path, "HT");



    return 0;
}*/