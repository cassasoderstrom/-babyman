#include "collision.h"
#include "game.h"
#include "raylib.h"
#include "gameDraw.h"
#include "main.h"
#include "./include/score.h"
#include "./include/gameUtil.h"
#include <stdlib.h>
#include "achievements.h"


void Game(GameStruct g, Texture2D textures[25])
{
    GameScreen currentScreen = MENU;
    int spawner = 0;
    int seconds = 0;
    int portalcounter = 0;
    int wizardSpawner = 0;
    int score = 0;
    int choice;
    int scoreArr[5] = {0};
    int achArr[20] = {0};
    int progArr[2] = {0};
    float musicvol;
    float soundvol;
    Rectangle onoff = (Rectangle){150.0f, 0.0f, (float)textures[15].width/2, (float)textures[15].height};
    
    FILE * settingsRead = fopen("options.settings","r");
    if(settingsRead){
        fscanf(settingsRead,"%f,%f",&musicvol,&soundvol);
    }
    fclose(settingsRead);
    ReadFromFile(scoreArr);

    LoadAchievements(achArr);
    LoadProgress(progArr);
    
    if(achArr[4] == 1){
        textures[0] = LoadTexture("pictures/babymanGlass.png");
    }
    if(achArr[9] == 1){
        textures[0] = LoadTexture("pictures/babymanGlasses.png");
    }
    if(achArr[14] == 1 && achArr[19] == 1){
        textures[0] = LoadTexture("pictures/babymanGlassesAndGun.png");
    }

    Texture2D levelMenu[4];
    levelMenu[0] = LoadTexture("pictures/stars_level/levelstars.png");
    levelMenu[1] = LoadTexture("pictures/desert_level/leveldesert.png");
    levelMenu[2] = LoadTexture("pictures/forest_level/levelforest.png");
    levelMenu[3] = LoadTexture("pictures/shuffle.png");
    
    Music menuMusic = LoadMusicStream("music/menutheme.wav");
    Music gameMusic = LoadMusicStream("music/gametheme.wav");
    Sound dead = LoadSound("music/oof.wav");
    
    int scaleSize = 0;

    float portalscale = 0.35; //FIX
    
    while (!WindowShouldClose())
    {
        
        switch(currentScreen){

            case MENU:{
                PlayMusicStream(menuMusic);
                UpdateMusicStream(menuMusic);
                SetVolume(menuMusic,gameMusic,dead,musicvol,soundvol);
                seconds = 0;
                qsort(scoreArr, 5, sizeof(int), sortScore);
                if(IsMouseButtonPressed(0) && ((GetMouseX()>875 && GetMouseX()<1065) && (GetMouseY() > 575 && GetMouseY() < 675))){
                    currentScreen = LEVELMENU;
                }
                if(IsMouseButtonPressed(0) && ((GetMouseX()>850 && GetMouseX()<1105) && (GetMouseY() > 700 && GetMouseY() < 800))){
                    currentScreen = SETTINGS;
                }
                if(IsMouseButtonPressed(0) && ((GetMouseX()>1375 && GetMouseX()<1775 && (GetMouseY() > 700 && GetMouseY() < 800)))){
                    currentScreen = ACHIEVEMENT;
                }
                if(IsMouseButtonPressed(0) && ((GetMouseX()>900 && GetMouseX()<1050 && (GetMouseY() > 825 && GetMouseY() < 925)))){
                    return;
                }

                
                
            }break;

            case SETTINGS:{
                PlayMusicStream(menuMusic);
                UpdateMusicStream(menuMusic);

                // Reduce music volume
                if(IsMouseButtonPressed(0) && ((GetMouseX()>800 && GetMouseX()<850) && (GetMouseY() > 200 && GetMouseY() < 250))){
                    musicvol-=0.1;
                    if(musicvol < 0) musicvol = 0;
                }
                // Reduce sound volume
                if(IsMouseButtonPressed(0) && ((GetMouseX()>800 && GetMouseX()<850) && (GetMouseY() > 300 && GetMouseY() < 350))){
                    soundvol-=0.1;
                    if(soundvol < 0) soundvol = 0;
                }
                // Increase music volume
                if(IsMouseButtonPressed(0) && ((GetMouseX()>950 && GetMouseX()<1000) && (GetMouseY() > 200 && GetMouseY() < 250))){
                    musicvol+=0.1;
                    if(musicvol > 1.0) musicvol = 1.0;
                }
                // Increase sound volume
                if(IsMouseButtonPressed(0) && ((GetMouseX()>950 && GetMouseX()<1000) && (GetMouseY() > 300 && GetMouseY() < 350))){
                    soundvol+=0.1;
                    if(soundvol > 1.0) soundvol = 1.0;
                }
                // Toggle fullscreen
                

                SetVolume(menuMusic,gameMusic,dead,musicvol,soundvol);

                FILE *settingsPtr = fopen("options.settings", "w");

                if(settingsPtr){
                    fprintf(settingsPtr, "%f,%f", musicvol, soundvol);
                    
                    fclose(settingsPtr);
                }

                if(IsMouseButtonPressed(0) && ((GetMouseX()>100 && GetMouseX()<500) && (GetMouseY() > 900 && GetMouseY() < 1000))){
                    currentScreen = MENU;
                }
            }break;
            
            case ACHIEVEMENT:{
                PlayMusicStream(menuMusic);
                UpdateMusicStream(menuMusic);
                if(IsMouseButtonPressed(0) && ((GetMouseX()>100 && GetMouseX()<500) && (GetMouseY() > 900 && GetMouseY() < 1000))){
                    currentScreen = MENU;
                }
                
            }break;

            case LEVELMENU:{
                
                PlayMusicStream(menuMusic);
                UpdateMusicStream(menuMusic);

                if(IsMouseButtonPressed(0) && ((GetMouseX()>300 && GetMouseX()<850) && (GetMouseY() > 100 && GetMouseY() < 400))){
                    choice = 0;
                }
                if(IsMouseButtonPressed(0) && ((GetMouseX()>1100 && GetMouseX()<1650) && (GetMouseY() > 100 && GetMouseY() < 400))){
                    choice = 1;
                }
                
                if(IsMouseButtonPressed(0) && (GetMouseX() > 700 && GetMouseX() < 1200) && (GetMouseY() > 500 && GetMouseY() < 800) ){
                    choice = 2;
                }   
                if(IsMouseButtonPressed(0) && ((GetMouseX()>775 && GetMouseX()<1175) && (GetMouseY() > 875 && GetMouseY() < 975))){
                    currentScreen = MENU;
                }
                if(IsMouseButtonPressed(0) && ((GetMouseX() > 915 && GetMouseX() < 1050) && (GetMouseY() > 335 && GetMouseY() < 460))){
                    choice = GetRandomValue(0,2);
                }

                switch(choice){
                    case 0:{
                        initEnvItems(g.envItems,0);
                        g.envItemsLength = sizeof(g.envItems)/sizeof(g.envItems[0]);
                        textures[1] = LoadTexture("pictures/stars_level/stars.png");
                        textures[2] = LoadTexture("pictures/stars_level/moln.png");
                        textures[3] = LoadTexture("pictures/stars_level/moln200.png");
                        textures[4] = LoadTexture("pictures/stars_level/moln300.png");
                        textures[5] = LoadTexture("pictures/stars_level/moln100.png");
                        textures[7] = LoadTexture("pictures/stars_level/alien.png");
                        textures[13] = LoadTexture("pictures/stars_level/wizard.png");
                        currentScreen = GAMEPLAY;
                    }break;

                    case 1:{
                        initEnvItems(g.envItems,1);
                        g.envItemsLength = sizeof(g.envItems)/sizeof(g.envItems[0]);
                        textures[1] = LoadTexture("pictures/desert_level/desert.png");
                        textures[2] = LoadTexture("pictures/desert_level/woodbotten.png");
                        textures[3] = LoadTexture("pictures/desert_level/woodsida.png");
                        textures[4] = LoadTexture("pictures/desert_level/woodtopp.png");
                        textures[5] = LoadTexture("pictures/desert_level/woodmellan.png");
                        textures[7] = LoadTexture("pictures/desert_level/desertAlien.png");
                        textures[13] = LoadTexture("pictures/desert_level/desertWizard.png");
                        currentScreen = GAMEPLAY;
                    }break;

                    case 2:{
                        initEnvItems(g.envItems,2);
                        g.envItemsLength = sizeof(g.envItems)/sizeof(g.envItems[0]);
                        textures[1] = LoadTexture("pictures/forest_level/forest.png");
                        textures[2] = LoadTexture("pictures/forest_level/leaves750.png");
                        textures[3] = LoadTexture("pictures/forest_level/leaves200.png"); 
                        textures[4] = LoadTexture("pictures/forest_level/leaves300.png");
                        textures[5] = LoadTexture("pictures/forest_level/leaves100.png");
                        textures[7] = LoadTexture("pictures/forest_level/forestAlien.png");
                        textures[13] = LoadTexture("pictures/forest_level/forestWizard.png");
                        currentScreen = GAMEPLAY;
                    }break;

                   
                }
                
            }break;
            
            case GAMEPLAY:{
                StopMusicStream(menuMusic);
                PlayMusicStream(gameMusic);
                UpdateMusicStream(gameMusic);
                seconds++;
                score++;
                spawner++;
                wizardSpawner++;
                portalcounter++;
                CheckAchievements(achArr,progArr,seconds,score);
                float deltaTime = GetFrameTime();
                UpdatePlayer(&g.player, g.envItems, g.envItemsLength, deltaTime,soundvol);
                for(int i = 0;i<g.maxenemy;i++){
                    if(g.enemy[i].active){
                        UpdateEnemy(&g.enemy[i], g.player, g.envItems, g.envItemsLength, deltaTime, g.enemy[i].id);
                    }
                }

                for(int i = 0;i<g.maxWizard;i++){
                    if(g.wizard[i].active){
                        UpdateEnemy(&g.wizard[i], g.player, g.envItems, g.envItemsLength, deltaTime, g.wizard[i].id);
                    }
                }

                CameraFunc(&g);
                
                // Input handler
                GetKeyPresses(&g, textures);

                for(int j = 0; j < NUM_SHOOTS; j++){
                    if (g.shoot[j].active)
                    {
                        // Movement of bullet
                        if(g.shoot[j].isLeft){
                            g.shoot[j].rec.x -= g.shoot[j].speed.x;   
                        }
                        else{
                            g.shoot[j].rec.x += g.shoot[j].speed.x;
                        }
                    }    
                }

                // Alien spawning
                AlienSpawning(&g, &spawner, seconds);

                if(seconds%600 == 0){
                    g.maxmedkit++;
                    
                }

                // Collision checker
                CheckCollision(&g, &spawner, &score,progArr);
                SaveProgress(progArr);
                SaveAchievements(achArr);

                // Wizard spawning
                WizardSpawning(&g, &wizardSpawner, &portalcounter, &scaleSize, textures);

                // Wizard shooting
                WizardShooting(&g, &seconds);
                  
                //Ufo movement
                UfoSpawner(&g, &spawner, seconds);

                if(g.player.hearts < 1){
                    PlaySound(dead);
                    currentScreen = GAMEOVER;
                }

                
                if(IsKeyPressed(KEY_P)){
                    currentScreen = PAUSE;
                }
            }break;
            
            case PAUSE:{

                if(IsMouseButtonPressed(0) && GetMouseX() > 875 && GetMouseX() < 1125 && GetMouseY() >375 && GetMouseY() < 475){
                    currentScreen = GAMEPLAY;
                }
                if(IsMouseButtonPressed(0) && GetMouseX() > 925 && GetMouseX() < 1075 && GetMouseY() >575 && GetMouseY() < 675){
                    choice = 3;
                    currentScreen = LEVELMENU;
                }

            }break;

            case GAMEOVER:{
                seconds = 0;
                StopMusicStream(gameMusic);
                PlayMusicStream(menuMusic);
                UpdateMusicStream(menuMusic);
                AddScore(scoreArr, score/60);
                SaveToFile(scoreArr);

                if(IsMouseButtonPressed(0) && GetMouseX() > 825 && GetMouseX() < 1075 && GetMouseY() > 740 && GetMouseY() < 840){
                    currentScreen = GAMEPLAY;
                    initGame(&g,textures, 1);
                    portalcounter = 0;
                    score = 0;
                    spawner = 0;
                    wizardSpawner = 0;
                }

                if(IsMouseButtonPressed(0) && GetMouseX() > 820 && GetMouseX() < 1095 && GetMouseY() > 880 && GetMouseY() < 955){
                    currentScreen = MENU;
                    initGame(&g,textures, 1);
                    portalcounter = 0;
                    score = 0;
                    spawner = 0;
                    wizardSpawner = 0;
                    choice = 3;
                }
            }break;
        }
            
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTextureEx(textures[1], (Vector2){ g.scrollingBack, 0 }, 0.0f, 1.0f, WHITE);

            switch(currentScreen){
                case MENU:{
                    DrawMenu(textures, scoreArr);
                }break;

                case SETTINGS:{
                    DrawSettings(textures,musicvol,soundvol,&onoff);
                }break;

                case LEVELMENU:{
                    DrawLevelMenu(levelMenu);
                }break;

                case ACHIEVEMENT:{
                    DrawAchievements(textures, achArr,progArr);
                }break;

                case GAMEPLAY:{
                    DrawGame(g, seconds, score, textures,portalscale, choice);
                }break;

                case PAUSE:{
                    DrawGame(g, seconds, score, textures,portalscale, choice);
                    DrawPause();
                }break;

                case GAMEOVER:{
                    DrawGameOver(textures, score);
                }break;
            }
            
        EndDrawing();

    }
    UnloadMusicStream(menuMusic);
    UnloadSound(dead);
}