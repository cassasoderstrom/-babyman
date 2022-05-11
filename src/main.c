#include "raylib.h"
#include "raymath.h"
#include "utilities.h"
#include "collision.h"
#include "main.h"
#include "gameUtil.h"
#include <string.h>

void initGame(GameStruct *g, Texture2D textures[25], int firstTime)
{
    if(firstTime == 0){
        //Textures
        textures[0] = LoadTexture("pictures/babyman.png");
        textures[1] = LoadTexture("pictures/stars_level/stars.png");
        textures[6] = LoadTexture("pictures/hearts2.png");         
        textures[8] = LoadTexture("pictures/ufo.png");  
        textures[9] = LoadTexture("pictures/ufo-beam.png");
        textures[10] = LoadTexture("pictures/babymanlogo.png");
        textures[11] = LoadTexture("pictures/gameover.png");
        textures[12] = LoadTexture("pictures/portal.png");
        textures[14] = LoadTexture("pictures/volumeArrows.png");
        textures[15] = LoadTexture("pictures/onoff.png");
        textures[16] = LoadTexture("pictures/arrowkeys.png");
        textures[17] = LoadTexture("pictures/spacebar.png");
        textures[18] = LoadTexture("pictures/medkit.png");
        textures[19] = LoadTexture("pictures/bronzemedal.png");
        textures[20] = LoadTexture("pictures/silvermedal.png");
        textures[21] = LoadTexture("pictures/goldmedal.png");
        textures[22] = LoadTexture("pictures/diamondmedal.png");
        textures[23] = LoadTexture("pictures/blackmedal.png");
        textures[24] = LoadTexture("pictures/bloodmedal.png");
        
        LoadSounds();
    }
    

    g->scrollingBack = 0.0f;
    
    // Player init.
    g->player = initPlayer();
    g->frameRec = (Rectangle){ 0.0f, 0.0f, (float)textures[0].width/2, (float)textures[0].height };
    g->heartsFrameRec = (Rectangle){0.0f, 0.0f, (float)textures[6].width, (float)textures[6].height};
    
    //Bullet init.
    g->shootRate = 0;
    g->lookLeft = true;
    g->shoot[NUM_SHOOTS] = (Shoot){ 0 };
    for(int i = 0; i < NUM_SHOOTS; i++){
        g->shoot[i] = initShoot(g->player, i, g->shoot);
    }

    // Enemy init.
    g->enemy[MAX_ENEMY] = (Enemy){0};
    initEnemy(g->enemy);
    g->maxenemy = 0;
    g->frameRecEnemy = (Rectangle){ 0.0f, 0.0f, (float)textures[7].width/2, (float)textures[7].height};
    g->isSpawning = false;
    for(int i = 0; i<MAX_ENEMY; i++){
        g->enemy[i].id = 0;
    }

    //Medkit init.
    g->medkit[100] = (Enemy){0};
    for(int i = 0;i<100;i++){

        g->medkit[i].position = (Vector2){500,100};
        g->medkit[i].rec.x = g->medkit[i].position.x -30;
        g->medkit[i].rec.y = g->medkit[i].position.y -50;
        g->medkit[i].rec.width = 50;
        g->medkit[i].rec.height = 50;
        g->medkit[i].active = true;
    }

    // Portal init.
    g->portalRec = (Rectangle){ 858,177, (float)textures[12].width/7, (float)textures[12].height};    

    // Wizard init.
    g->wizard[MAX_WIZARD_ENEMY] = (Enemy){0};
    g->isSpawningWizard = false;
    initWizardEnemy(g->wizard);
    g->maxWizard = 0;
    g->frameRecWizard = (Rectangle){0.0f, 0.0f, (float)textures[13].width/2, (float)textures[13].height};
    for(int i = 0; i<MAX_ENEMY; i++){
        g->wizard[i].id = 1;
    }

    for(int i = 0; i < NUM_WIZARD_SHOOTS; i++){
        g->wizardShoot[i] = initWizardShoot(g->wizard, i, g->maxWizard, g->wizardShoot);
    }

    // Camera init.
    g->camera = initCamera(g->camera, g->player, 1920, 1080);
    
    // Ufo init.
    g->ufoLeft = initUfoLeft(g->ufoLeft, textures[8].width, textures[8].height);
    g->ufoRight = initUfoRight(g->ufoRight, textures[8].width, textures[8].height);
}

int main(void)
{
    const int screenWidth = 1920;
    const int screenHeight = 1030;
    InitWindow(screenWidth, screenHeight, "BabyMan Nightmares");
    Image icon = LoadImage("pictures/icon.png");
    SetWindowIcon(icon);
    InitAudioDevice();
    GameStruct g;
    Texture2D textures[25];

    initGame(&g,textures,0);

    
    SetTargetFPS(60);
    Game(g,textures);

    /*------------------------------------------*/

    for(int i = 0; i<25;i++){
        UnloadTexture(textures[i]);
    }
    CloseAudioDevice();
    return 0;
}



