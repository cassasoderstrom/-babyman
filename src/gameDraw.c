#include "gameDraw.h"
#include "game.h"
#include <stdio.h>

bool shouldLoad = true;


void DrawGame(GameStruct g, int seconds, int score, Texture2D textures[25], float portalscale, int choice)
{
    BeginMode2D(g.camera);
        //platforms
        for (int i = 0; i < g.envItemsLength; i++){
            DrawRectangleRec(g.envItems[i].rect, g.envItems[i].color);
        }

        //texture for platforms
        if(choice == 0){
        
            for(int j = 2; j < 6;j++){
                for(int i = 0;i < g.envItemsLength;i++){
                    if(g.envItems[i].rect.width == textures[j].width){
                        DrawTextureEx(textures[j], (Vector2){g.envItems[i].rect.x, g.envItems[i].rect.y-30}, 0, 1, WHITE);
                    }
                }
            }
        }
        else if(choice == 1 || choice == 2){
            for(int j = 2; j < 6;j++){
                for(int i = 0;i < g.envItemsLength;i++){
                    if(g.envItems[i].rect.width == textures[j].width){
                        DrawTextureEx(textures[j], (Vector2){g.envItems[i].rect.x, g.envItems[i].rect.y}, 0, 1, WHITE);
                    }
                }
            }
        }
        
        //Ufo textures
        DrawTextureRec(textures[8], g.ufoLeft.rec,(Vector2){ g.ufoLeft.position.x,g.ufoLeft.position.y}, WHITE);
        DrawTextureRec(textures[8], g.ufoRight.rec ,(Vector2){ g.ufoRight.position.x,g.ufoRight.position.y}, WHITE);
        
        //Portal texture
        if(g.isSpawningWizard){
            DrawTextureRec(textures[12],g.portalRec, (Vector2){ 445, 215}, WHITE);
        }
          
        //Bullet "textures"
        for (int i = 0; i < NUM_SHOOTS; i++)
        {
            if (g.shoot[i].active) DrawRectangleRec(g.shoot[i].rec, g.shoot[i].color);
        }
                
        //Ufo beam texture
        if(g.isSpawning){
            DrawTextureEx(textures[9], (Vector2){793,-100},0,1,WHITE);
            DrawTextureEx(textures[9], (Vector2){-5,-100},0,1,WHITE);
            
        }
    
        //Enemy textures
        for(int i = 0;i<MAX_ENEMY;i++){
            int minenemy = 0;
                    
            for (;minenemy<g.maxenemy;minenemy++){    
                if(g.player.position.x < g.enemy[minenemy].position.x){
                    g.frameRecEnemy = (Rectangle){ 40.0f, 0.0f, (float)textures[7].width/2, (float)textures[7].height};
                }
                else{
                    g.frameRecEnemy = (Rectangle){ 0.0f, 0.0f, (float)textures[7].width/2, (float)textures[7].height};
                }
                        
                if(g.enemy[minenemy].active){
                    DrawTextureRec(textures[7], g.frameRecEnemy, (Vector2){g.enemy[minenemy].position.x - 20, g.enemy[minenemy].position.y - 40}, WHITE);
                    DrawRectangle(g.enemy[minenemy].position.x-20,g.enemy[minenemy].position.y-40,g.enemy[minenemy].rec.width,g.enemy[minenemy].rec.height, GetColor(00));
                }
            }
        }

        for(int i = 0;i<100;i++){
            int minmedkit = 0;
            for(;minmedkit<g.maxmedkit;minmedkit++){
                

                if(g.medkit[minmedkit].active){
                    DrawTexture(textures[18],g.medkit[minmedkit].position.x - 30, g.medkit[minmedkit].position.y - 50, WHITE);
                    DrawRectangle(g.medkit[minmedkit].position.x-30,g.medkit[minmedkit].position.y-50,g.medkit[minmedkit].rec.width,g.medkit[minmedkit].rec.height, GetColor(00));
                }
            }
        }
        // Wizard textures
        for(int j = 0; j<MAX_WIZARD_ENEMY;j++){
            int minWizEnemy = 0;

            for(;minWizEnemy<g.maxWizard;minWizEnemy++){
                if(g.player.position.x < g.wizard[minWizEnemy].position.x){
                    g.frameRecWizard = (Rectangle){0.0f, 0.0f, (float)textures[13].width/2, (float)textures[13].height};
                    
                }
                else{
                    g.frameRecWizard = (Rectangle){50.0f, 0.0f, (float)textures[13].width/2, (float)textures[13].height};
                }

                if(g.wizard[minWizEnemy].active){
                    DrawTextureRec(textures[13], g.frameRecWizard, (Vector2){g.wizard[minWizEnemy].position.x - 30, g.wizard[minWizEnemy].position.y - 50}, WHITE);
                    DrawRectangle(g.wizard[minWizEnemy].position.x-30,g.wizard[minWizEnemy].position.y-50,g.wizard[minWizEnemy].rec.width,g.wizard[minWizEnemy].rec.height, GetColor(00));
                }
            }
        }

        for (int i = 0; i < NUM_WIZARD_SHOOTS; i++)
        {
            if (g.wizardShoot[i].active) DrawCircleGradient(g.wizardShoot[i].rec.x+15,g.wizardShoot[i].rec.y+15,15.0f, YELLOW,RED);
        }

        //Player textures

        DrawRectangle(g.player.position.x - 30, g.player.position.y - 50, 50,50, GetColor(00));        
        DrawTextureRec(textures[0], g.frameRec, (Vector2){g.player.position.x - 30, g.player.position.y - 50}, WHITE);
        
        
    EndMode2D();
            
    //Draws seconds elapsed
    char charseconds[10];
    sprintf(charseconds, "%d", seconds/60);
    DrawText(charseconds, 100,100,50,GREEN);
    DrawText("Seconds", 95,75,30,GREEN);

    //Draws score
    char charScore[15];
    sprintf(charScore, "%d", score/60);
    DrawText(charScore, 900, 100, 50, RED);
    DrawText("Score", 895,75,30,RED);
    // heart textures
    switch(g.player.hearts){
        case 1:
            g.heartsFrameRec = (Rectangle){64.0f, 0.0f, textures[6].width/3, textures[6].height};
        break;
        case 2:
            g.heartsFrameRec = (Rectangle){62.0f, 0.0f, textures[6].width/1.5, textures[6].height};
        break;
        case 3:
            g.heartsFrameRec = (Rectangle){0.0f, 0.0f, textures[6].width, textures[6].height};
        break;
        default:
            // game over
            g.heartsFrameRec = (Rectangle){61.0f, 62.0f, textures[6].width/60, textures[6].height};
        }
    DrawTextureRec(textures[6], g.heartsFrameRec, (Vector2){ 1600, 75}, WHITE);
}

void DrawGameOver(Texture2D textures[25], int score)
{
    DrawTextureEx(textures[11],(Vector2){220,-100},0,2,WHITE);
    char charScore[15];
    sprintf(charScore, "%d", score/60);
    DrawText("Your score: ", 830,600,40,ORANGE);
    DrawText(charScore, 925, 650, 80, ORANGE);

    
    DrawRectangle(825,740,250,100,GetColor(100));
    if((GetMouseX() > 825 && GetMouseX() < 1075) && (GetMouseY() > 740 && GetMouseY() < 840) ){
        DrawRectangleLinesEx((Rectangle){825,740,250,100},8,WHITE);
    }
    else{
        DrawRectangleLinesEx((Rectangle){825,740,250,100},8,DARKBLUE);
    }
    DrawText("Play again", 850,770,40,DARKBLUE);

    DrawRectangle(820,880,275,75,GetColor(100));
    if((GetMouseX() > 820 && GetMouseX() < 1095) && (GetMouseY() > 880 && GetMouseY() < 955) ){
        DrawRectangleLinesEx((Rectangle){820,880,275,75},8,BLACK);
    }
    else{
        DrawRectangleLinesEx((Rectangle){820,880,275,75},8,RED); 
    }
    DrawText("Return to menu",840,900,30,RED);

    
}

void DrawPause(void)
{
    DrawRectangle(0,0,1920,1080,GetColor(200));
    DrawText("Game Paused",675,100,100,ORANGE);
    
    
    if((GetMouseX() > 875 && GetMouseX() < 1125) && (GetMouseY() > 375 && GetMouseY() < 475) ){
        DrawRectangleLinesEx((Rectangle){875,375,250,100},8,WHITE);
    }
    else{
        DrawRectangleLinesEx((Rectangle){875,375,250,100},8,DARKBLUE);
    }
    DrawText("Resume", 900, 400, 50, DARKBLUE);

   
    if((GetMouseX() > 925 && GetMouseX() < 1075) && (GetMouseY() > 575 && GetMouseY() < 675) ){
        DrawRectangleLinesEx((Rectangle){925,575,150,100},8,BLACK);
    }
    else{
        DrawRectangleLinesEx((Rectangle){925,575,150,100},8,RED);
    }
    DrawText("Exit", 950, 600, 50, RED);
}

void DrawMenu(Texture2D textures[25], int scoreArr[5])
{
    DrawTextureEx(textures[10],(Vector2){500,100},0,4,WHITE);
    DrawRectangle(170,300,200,350,GetColor(100));
    DrawText("Top 5",190,325,40,ORANGE);
    
    DrawText("1. ",210,400,30,ORANGE);
    DrawText("2. ",210,450,30,ORANGE);
    DrawText("3. ",210,500,30,ORANGE);
    DrawText("4. ",210,550,30,ORANGE);
    DrawText("5. ",210,600,30,ORANGE);

    char highScore1[10];
    sprintf(highScore1, "%d", scoreArr[4]);
    char highScore2[10];
    sprintf(highScore2, "%d", scoreArr[3]);
    char highScore3[10];
    sprintf(highScore3, "%d", scoreArr[2]);
    char highScore4[10];
    sprintf(highScore4, "%d", scoreArr[1]);
    char highScore5[10];
    sprintf(highScore5, "%d", scoreArr[0]);

    DrawText(highScore1,235,400,30,ORANGE);
    DrawText(highScore2,235,450,30,ORANGE);
    DrawText(highScore3,235,500,30,ORANGE);
    DrawText(highScore4,235,550,30,ORANGE);
    DrawText(highScore5,235,600,30,ORANGE);

    DrawRectangleLinesEx((Rectangle){170,300, 200,350},8,ORANGE);

    DrawRectangle(1375,700,400,100,GetColor(100));
    DrawText("Achievements", 1400,725,50,ORANGE);
    if((GetMouseX() > 1375 && GetMouseX() < 1775) && (GetMouseY() > 700 && GetMouseY() < 800) ){
        DrawRectangleLinesEx((Rectangle){1375,700,400,100},8,WHITE);
    }
    else{
        DrawRectangleLinesEx((Rectangle){1375,700,400,100},8,ORANGE);
    }



    DrawRectangle(875,575,190,100,GetColor(100));
    DrawText("Start", 900,600,50,ORANGE);
    if((GetMouseX() > 875 && GetMouseX() < 1065) && (GetMouseY() > 575 && GetMouseY() < 675) ){
        DrawRectangleLinesEx((Rectangle){875,575,190,100},8,WHITE);
    }
    else{
        DrawRectangleLinesEx((Rectangle){875,575,190,100},8,ORANGE);
    }

    DrawRectangle(850,700,255,100,GetColor(100));
    DrawText("Settings", 875,725,50,ORANGE);
    if((GetMouseX() > 850 && GetMouseX() < 1105) && (GetMouseY() > 700 && GetMouseY() < 800) ){
        DrawRectangleLinesEx((Rectangle){850,700,255,100},8,WHITE);
    }
    else{
        DrawRectangleLinesEx((Rectangle){850,700,255,100},8,ORANGE);
    }

    DrawRectangle(900,825,150,100,GetColor(100));
    DrawText("Exit", 925,850,50,RED);
    if((GetMouseX() > 900 && GetMouseX() < 1050) && (GetMouseY() > 825 && GetMouseY() < 925) ){
        DrawRectangleLinesEx((Rectangle){900,825,150,100},8,BLACK);
    }
    else{
        DrawRectangleLinesEx((Rectangle){900,825,150,100},8,RED);
    }
}

void DrawLevelMenu(Texture2D levelMenu[4])
{
    DrawText("Select Level",800,50,50,ORANGE);

    DrawTexture(levelMenu[0],300,150,WHITE);
    if((GetMouseX() > 300 && GetMouseX() < 850) && (GetMouseY() >150 && GetMouseY() < 450) ){
        DrawRectangleLinesEx((Rectangle){300,150,550,300},10,WHITE);
    }
    else{
        DrawRectangleLinesEx((Rectangle){300,150,550,300},10,ORANGE);
    }
    DrawText("Clouds",500,350,50,ORANGE);
    
    DrawTexture(levelMenu[1],1100,150,WHITE);
    if((GetMouseX() > 1100 && GetMouseX() < 1650) && (GetMouseY() > 150 && GetMouseY() < 450) ){
        DrawRectangleLinesEx((Rectangle){1100,150,550,300},10,WHITE);
    }
    else{
        DrawRectangleLinesEx((Rectangle){1100,150,550,300},10,ORANGE);
    }
    
    DrawText("Desert",1300,350,50,ORANGE);

    DrawTexture(levelMenu[2],700,500,WHITE);
    if((GetMouseX() > 700 && GetMouseX() < 1200) && (GetMouseY() > 500 && GetMouseY() < 800) ){
        DrawRectangleLinesEx((Rectangle){700,500,550,300},10,WHITE);
    }
    else{
        DrawRectangleLinesEx((Rectangle){700,500,550,300},10,ORANGE);
    }
    DrawText("Forest",900,700,50,ORANGE);

    
    DrawRectangle(915,335,135,125,GetColor(100));
    DrawTexture(levelMenu[3],935,350,WHITE);

    if((GetMouseX() > 915 && GetMouseX() < 1050) && (GetMouseY() > 335 && GetMouseY() < 460) ){
        DrawRectangleLinesEx((Rectangle){915,335,135,125},8,WHITE);
    }
    else{
        DrawRectangleLinesEx((Rectangle){915,335,135,125},8,DARKBLUE);
    }

    DrawRectangle(775,875,400,100,GetColor(100));
    if((GetMouseX() > 775 && GetMouseX() < 1175) && (GetMouseY() > 875 && GetMouseY() < 975) ){
        DrawRectangleLinesEx((Rectangle){775,875,400,100},8,BLACK);
    }
    else{
        DrawRectangleLinesEx((Rectangle){775,875,400,100},8,RED);
    }
    DrawText("Back to Menu", 800,900,50,RED);
}

void DrawSettings(Texture2D textures[25], float musicvol, float soundvol, Rectangle *onoff)
{
    
    
    char musicVolume[3];
    sprintf(musicVolume, "%.f", musicvol*10);
    char soundVolume[3];
    sprintf(soundVolume, "%.f", soundvol*10);
    DrawText("Settings",850,50,50,ORANGE);
    DrawText("Music volume", 200, 200, 50, DARKBLUE);
    DrawText("Sound volume", 200, 300, 50, DARKBLUE);
    DrawText("Toggle fullscreen", 200, 400, 50, DARKBLUE);
    DrawTexture(textures[14], 800, 200, WHITE);
    DrawTexture(textures[14], 800, 300, WHITE);
    if(IsMouseButtonPressed(0) && (GetMouseX() > 830 && GetMouseX() < 980) && (GetMouseY() > 400 && GetMouseY() < 450)){
        
        
        if(!IsWindowFullscreen()){
            *onoff = (Rectangle){0.0f, 0.0f, (float)textures[15].width/2, (float)textures[15].height};
            
        }
        else if (IsWindowFullscreen()){
            *onoff = (Rectangle){150.0f, 0.0f, (float)textures[15].width/2, (float)textures[15].height};
           
        }
        ToggleFullscreen();
    }
    DrawTextureRec(textures[15],*onoff,(Vector2){830,400},WHITE);

    DrawText(musicVolume, 885, 200, 50, WHITE);
    DrawText(soundVolume, 885, 300, 50, WHITE);

    DrawText("Controls", 750, 500, 50, DARKBLUE);
    DrawTexture(textures[16], 1000, 600,WHITE);
    DrawTexture(textures[17], 400, 750, WHITE);
    DrawText("Move", 1145, 550, 30, DARKBLUE);
    DrawText("Shoot", 500,700, 30, DARKBLUE);

    DrawRectangle(100,900,400,100,GetColor(100));
    if((GetMouseX() > 100 && GetMouseX() < 500) && (GetMouseY() > 900 && GetMouseY() < 1000) ){
        DrawRectangleLinesEx((Rectangle){100,900,400,100},8,BLACK);
    }
    else{
        DrawRectangleLinesEx((Rectangle){100,900,400,100},8,RED);
    }
    DrawText("Back to Menu", 125,925,50,RED);

    
    
}

void DrawAchievements(Texture2D textures[25],int achArr[20],int progArr[2]){

    DrawText("Achievements",650,25,100,ORANGE);
    DrawText("Kill alien", 200, 150, 50, WHITE);
    DrawText("Kill wizard", 200, 350, 50, WHITE);
    DrawText("Survive (sec)", 150, 550, 50, WHITE);
    DrawText("Score", 200, 750, 50, WHITE);

    //Alien medals 
    DrawText("50", 535, 250, 25, WHITE);
    DrawText("100", 735, 250, 25, WHITE);
    DrawText("500", 935, 250, 25, WHITE);
    DrawText("1000", 1135, 250, 25, WHITE);
    DrawText("5000", 1335, 250, 25, WHITE);

    //Wizard medals 
    DrawText("50", 535, 450, 25, WHITE);
    DrawText("100", 735, 450, 25, WHITE);
    DrawText("500", 935, 450, 25, WHITE);
    DrawText("1000", 1135, 450, 25, WHITE);
    DrawText("5000", 1335, 450, 25, WHITE);

    //Survive medals 
    DrawText("60", 535, 650, 25, WHITE);
    DrawText("120", 735, 650, 25, WHITE);
    DrawText("300", 935, 650, 25, WHITE);
    DrawText("600", 1135, 650, 25, WHITE);
    DrawText("3600", 1335, 650, 25, WHITE);

    //Score medals 
    DrawText("200", 535, 850, 25, WHITE);
    DrawText("500", 735, 850, 25, WHITE);
    DrawText("1000", 935, 850, 25, WHITE);
    DrawText("5000", 1135, 850, 25, WHITE);
    DrawText("10000", 1335, 850, 25, WHITE);

    int y = 150;
    for(int i = 0;i<20;i+=5){
        if(achArr[i]==1) DrawTexture(textures[19],500,y,WHITE);
        else DrawTexture(textures[23],500,y,WHITE);
        y+=200;
    }
    int y1 = 150;
    for(int i = 1;i<20;i+=5){
        if(achArr[i]==1) DrawTexture(textures[20],700,y1,WHITE);
        else DrawTexture(textures[23],700,y1,WHITE);
        y1+=200;
    }
    int y2 = 150;
    for(int i = 2;i<20;i+=5){
        if(achArr[i]==1) DrawTexture(textures[21],900,y2,WHITE);
        else DrawTexture(textures[23],900,y2,WHITE);
        y2+=200;
    }
    int y3 = 150;
    for(int i = 3;i<20;i+=5){
        if(achArr[i]==1) DrawTexture(textures[22],1100,y3,WHITE);
        else DrawTexture(textures[23],1100,y3,WHITE);
        y3+=200;
    }
    int y4 = 150;
    for(int i = 4;i<20;i+=5){
        if(achArr[i]==1) DrawTexture(textures[24],1300,y4,WHITE);
        else DrawTexture(textures[23],1300,y4,WHITE);
        y4+=200;
    }

    DrawText("Alien Kills:",1500,200,30,WHITE);
    DrawText("Wizard Kills:",1500,400,30,WHITE);

    char alienKills[10];
    sprintf(alienKills, "%d", progArr[0]);
    char wizardKills[10];
    sprintf(wizardKills, "%d", progArr[1]);
    DrawText(alienKills,1700,200,30,WHITE);
    DrawText(wizardKills,1700,400,30,WHITE);


    DrawRectangle(100,900,400,100,GetColor(100));
    if((GetMouseX() > 100 && GetMouseX() < 500) && (GetMouseY() > 900 && GetMouseY() < 1000) ){
        DrawRectangleLinesEx((Rectangle){100,900,400,100},8,BLACK);
    }
    else{
        DrawRectangleLinesEx((Rectangle){100,900,400,100},8,RED);
    }
    DrawText("Back to Menu", 125,925,50,RED);
}
