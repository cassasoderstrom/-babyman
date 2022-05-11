#include <stdio.h>
#include "./include/score.h"


void SaveToFile(int scoreArr[5])
{
    FILE *fileptr = fopen("high.score","wb");

    if (fileptr){
       
        fwrite(scoreArr, sizeof(int),5, fileptr );
       
    }
    fclose(fileptr);
}

void ReadFromFile(int scoreArr[5])
{
    
    FILE *fileptr = fopen("high.score","rb");
    
    if(fileptr){
        
        fread(scoreArr, sizeof(int),5, fileptr );
      
    }
    fclose(fileptr);

    
}

int sortScore (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

void AddScore(int scoreArr[5], int score)
{
    int j = 0;
    do{
        if(score > scoreArr[j]){
            scoreArr[j] = score;
            while(j > 0){
                scoreArr[j] = scoreArr[j-1];
                j--;
            }
        }
    }while(score > scoreArr[j]);
}