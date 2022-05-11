#include "./include/score.h"
#include <stdio.h>

int main(void)
{
    int arr[5];

    ReadFromFile(arr);

    for(int i = 0; i<5;i++){
        printf("arr: %d\n", arr[i]);
    }

    return 0;
}