#include <stdio.h>


void LoadAchievements(int achArr[20])
{
    FILE *achievements = fopen("achievements.ach", "r");
    int i = 0;
    if(achievements){
        while(i<20){
            fscanf(achievements, "%d ", &achArr[i]);
            i++;
        }
    }

    fclose(achievements);
}

void LoadProgress(int progArr[2])
{
    FILE *progress = fopen("progress.prog", "r");
    int i = 0;
    if(progress){
        while(i<2){
            fscanf(progress, "%d ", &progArr[i]);
            i++;
        } 
    }   
    fclose(progress);
}

void SaveProgress(int progArr[2])
{
    
    FILE * progress = fopen("progress.prog","w");
    int i = 0;
    if(progress){
        while(i<2){
            fprintf(progress,"%d ",progArr[i]);
            i++;
        }
    }
    fclose(progress);
}

void CheckAchievements(int achArr[], int progArr[],int seconds, int score)
{
    //Alien kill achievement check
    if(progArr[0] >= 50){
        achArr[0] = 1;
    }
    if(progArr[0] >= 100){
        achArr[1] = 1;
    }
    if(progArr[0] >= 500){
        achArr[2] = 1;
    }
    if(progArr[0] >= 1000){
        achArr[3] = 1;
    }
    if(progArr[0] >= 5000){
        achArr[4] = 1;
    }
    
    //Wizard kill achievement check
    if(progArr[1] >= 50){
        achArr[5] = 1;
    }
    if(progArr[1] >= 100){
        achArr[6] = 1;
    }
    if(progArr[1] >= 500){
        achArr[7] = 1;
    }
    if(progArr[1] >= 1000){
        achArr[8] = 1;
    }
    if(progArr[1] >= 5000){
        achArr[9] = 1;
    }

    //Time survived achievement check
    if(seconds/60 >= 60){
        achArr[10] = 1;
    }
    if(seconds/60 >= 120){
        achArr[11] = 1;
    }
    if(seconds/60 >= 300){
        achArr[12] = 1;
    }
    if(seconds/60 >= 600){
        achArr[13] = 1;
    }
    if(seconds/60 >= 3600){
        achArr[14] = 1;
    }

    //Score achievement check
    if(score/60 >= 200){
        achArr[15] = 1;
    }
    if(score/60 >= 500){
        achArr[16] = 1;
    }
    if(score/60 >= 1000){
        achArr[17] = 1;
    }
    if(score/60 >= 5000){
        achArr[18] = 1;
    }
    if(score/60 >= 10000){
        achArr[19] = 1;
    }
}

void SaveAchievements(int achArr[20])
{
    FILE *achievements = fopen("achievements.ach","w");
    int i = 0;
    if(achievements){
        while(i<20){
            fprintf(achievements,"%d ",achArr[i]);
            i++;
        }    
    }
    fclose(achievements);
}