#include <stdio.h>
#include <stdlib.h>

typedef struct need {
    int startIndex;
    int endIndex;
    int maxSum;
}need;

void letsDoIt(int arr[], need* myStruct, int size)
{
    int currSum = 0;
    myStruct->startIndex = 0;
    myStruct->maxSum = 0;

    for (myStruct->endIndex = 0; myStruct->endIndex < size; myStruct->endIndex++)
    {
        currSum += arr[myStruct->endIndex];

        //if(maxSumRange == 0 || )
        if (currSum > myStruct->maxSum)
        {
            myStruct->maxSum = currSum;
        }
        else if (currSum < 0)
        {
            currSum = 0;
            myStruct->startIndex = myStruct->endIndex + 1;
        }
    }
    myStruct->endIndex--;
}

int main()
{
    need* myStruct = (need*)malloc(sizeof(need));
    int arr[10] = { 4, -7, 1, 5, -4, 0, -3, 2, 4, 1 };
    int size = sizeof(arr) / sizeof(int);
    //int arr[5] = { 4, -7, 5, -1, 8 };

    printf("\nInput: ");
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }

    letsDoIt(arr, myStruct, size);

    printf("\nOutput: ");
    for (int i = myStruct->startIndex; i <= myStruct->endIndex; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\tsum: %d\n", myStruct->maxSum);
}