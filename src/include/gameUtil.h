#ifndef __GAMEUTIL_H__
#define __GAMEUTIL_H__

#include "game.h"
#include "gameDraw.h"

/**
 * @brief 
 * 
 * @param g 
 * @param spawner 
 * @param seconds 
 * @return GameStruct 
 */
void LoadSounds(void);

void SetVolume(Music music,Music game, Sound dead, float musicVol, float soundVol);

void AlienSpawning(GameStruct *g, int *spawner, int seconds);

void UfoSpawner(GameStruct *g, int *spawner, int seconds);

void CheckCollision(GameStruct *g, int *spawner, int *score, int progArr[2]);

void GetKeyPresses(GameStruct *g, Texture2D textures[]);

void WizardSpawning(GameStruct *g, int *wizardSpawner, int *portalcounter, int *scaleSize, Texture2D textures[]);

void WizardShooting(GameStruct *g, int *seconds);

void CameraFunc(GameStruct *g);

#endif