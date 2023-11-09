#include "queue.h"
#include "stack.h"
#include "set.h"
#include "hash_table.h"
#include "file.h"
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
            if (!strcmp(struc, "HT"))
            {
                printf("%s", tmp);
            }       

            if (!strcmp(struc, "Queue"))
            {
                //printf("%s", tmp);
                
                push_queue(tmp);
                
            }

            if (!strcmp(struc, "Stack"))
            {
                //printf("%s", tmp);
                push_stack(tmp);
            }

            if (!strcmp(struc, "Set"))
            {
                printf("%s", tmp);
            }
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

    char* result = strdup(struc);
    char* tmp = strdup(data);

    fputs(result, mf);
    fputs(":", mf);
    fputs(tmp, mf);
    fputs("\n", mf);
    fclose(mf);
}

void clear_file(char* path)
{
    FILE* mf = fopen(path, "w");

    if (!mf)
    {
        printf("ERROR: Can't open the file\n");
        return;
    }

    fputs("", mf);

}