#ifndef __MAIN_H__
#define __MAIN_H__

#include "game.h"

/**
 * @brief initializes the whole game struct
 * 
 * @param g Game struct with all the initialized values
 * @param textures Texture-array
 */
void initGame(GameStruct *g, Texture2D textures[25], int firstTime);

#endif