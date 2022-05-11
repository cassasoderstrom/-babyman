#ifndef __GAMEDRAW_H__
#define __GAMEDRAW_H__

#include "game.h"

typedef enum GameScreen{
    MENU,
    SETTINGS,
    LEVELMENU,
    ACHIEVEMENT,
    GAMEPLAY,
    PAUSE,
    GAMEOVER
}GameScreen;

/**
 * @brief Texture drawing for main game
 * 
 * @param g Game struct with all the initialized values
 * @param seconds Seconds since game started
 * @param textures Texture array
 */
void DrawGame(GameStruct g, int seconds, int score, Texture2D textures[25], float portalscale, int choice);

/**
 * @brief Texture drawing for main menu
 * 
 * @param textures Texture array
 */
void DrawMenu(Texture2D textures[25], int scoreArr[5]);

/**
 * @brief Texture drawing for level menu
 * 
 * @param textures 
 */
void DrawLevelMenu(Texture2D levelMenu[4]);

/**
 * @brief Texture drawing for game over screen
 * 
 * @param textures Texture array
 */
void DrawGameOver(Texture2D textures[25], int score);

void DrawPause(void);

/**
 * @brief Texture drawing for settings
 * 
 * @param textures 
 */
void DrawSettings(Texture2D textures[25], float musicvol, float soundvol, Rectangle *onoff);

void DrawAchievements(Texture2D textures[25], int achArr[20],int progArr[2]);

#endif

