#ifndef __GAMESCREEN_H__
#define __GAMESCREEN_H__

#include "utilities.h"
#include <stdio.h>

typedef struct GameStruct{
    Player player;
    EnvItem envItems[10];
    Rectangle frameRec;
    Rectangle frameRecEnemy;
    Rectangle frameRecWizard;
    Rectangle heartsFrameRec;
    Rectangle portalRec;
    Camera2D camera;
    Enemy enemy[MAX_ENEMY];
    Enemy wizard[MAX_WIZARD_ENEMY];
    WizardShoot wizardShoot[NUM_WIZARD_SHOOTS];
    Enemy medkit[100];
    int maxmedkit;
    Shoot shoot[NUM_SHOOTS];
    Ufo ufoRight;
    Ufo ufoLeft;
    float scrollingBack;
    int envItemsLength;
    int shootRate;
    int maxenemy;
    int maxWizard;
    bool lookLeft;
    bool isSpawning;
    bool isSpawningWizard;
}GameStruct;

/**
 * @brief Whole logic part of game
 * 
 * @param g Game struct with all the initialized values
 * @param textures Texture-array
 */
void Game(GameStruct g, Texture2D textures[25]);

#endif