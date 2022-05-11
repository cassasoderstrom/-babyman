#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#include "raylib.h"
#include "raymath.h"

#define NUM_SHOOTS 500  //number of shots
#define NUM_WIZARD_SHOOTS 500
#define G 600   //gravity
#define PLAYER_JUMP_SPD 350.0f //player jump speed
#define PLAYER_HOR_SPD 200.0f //player speed
#define ENEMY_HOR_SPD 50.0f // enemy speed
#define MAX_ENEMY 1000 // number of enemies
#define MAX_WIZARD_ENEMY 1000

typedef struct Player {
    Rectangle rec;
    Vector2 position;
    float speed;
    bool canJump;
    int hearts;
    bool collided;
} Player;

typedef struct Enemy {
    Rectangle rec;
    Vector2 position;
    bool canJump;
    float speed;
    bool active;
    bool isdead;
    int id;
} Enemy;

typedef struct WizardShoot {
    Rectangle rec;
    Vector2 position;
    Vector2 speed;
    bool active;
    Color color;
    bool isLeft;
    bool isUp;
}WizardShoot;

typedef struct Shoot{
    Rectangle rec;
    Vector2 speed;
    bool active;
    Color color;
    bool isLeft;
} Shoot;

typedef struct EnvItem {
    Rectangle rect;
    int blocking;
    Color color;
} EnvItem;

typedef struct Ufo{
    Vector2 position;
    Vector2 speed;
    Rectangle rec;
} Ufo;


/**
 * @brief Initializes player
 * 
 * @return Player 
 */
Player initPlayer(void);

/**
 * @brief Initializes alien enemy
 * 
 * @param enemy 
 */
void initEnemy(Enemy enemy[]);

/**
 * @brief Initializes wizard enemy
 * 
 * @param wizard 
 */
void initWizardEnemy(Enemy wizard[]);

/**
 * @brief Initializes environment items
 * 
 * @param envItems Environment items to be initialized
 */
void initEnvItems(EnvItem envItems[], int choice);

/**
 * @brief Initializes left-side ufo
 * 
 * @param ufoLeft ufo struct to be init.
 * @param width width of the texture
 * @param height height of the texture
 * @return Ufo init-ed ufo
 */
Ufo initUfoLeft(Ufo ufoLeft, int width, int height);

/**
 * @brief Initializes right-side ufo
 * 
 * @param ufoRight ufo struct to be init.
 * @param width width of the texture
 * @param height height of the texture
 * @return Ufo init-ed ufo
 */
Ufo initUfoRight(Ufo ufoRight, int width, int height);


/**
 * @brief Initializes shots to the right
 * 
 * @param player player struct to get position 
 * @param i bullet number
 * @param shoot shots-array to be initialized
 * @return Shoot 
 */
Shoot initShoot(Player player, int i, Shoot shoot[]);

/**
 * @brief 
 * 
 * @param wizard 
 * @param i 
 * @param j 
 * @param wizardShoot 
 * @return WizardShoot 
 */
WizardShoot initWizardShoot(Enemy wizard[], int i, int j, WizardShoot wizardShoot[]);

/**
 * @brief Initializes camera
 * 
 * @param camera camera struct to be initialized
 * @param player player struct needed to center camera on player
 * @param width screen width
 * @param height screen height
 * @return Camera2D 
 */
Camera2D initCamera(Camera2D camera, Player player, int width, int height);

/**
 * @brief Updates player position every frame
 * 
 * @param player 
 * @param envItems 
 * @param envItemsLength 
 * @param delta 
 */
void UpdatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float delta, float soundvol);

/**
 * @brief Updates enemy position every frame
 * 
 * @param enemy 
 * @param player 
 * @param envItems 
 * @param envItemsLength 
 * @param delta 
 */
void UpdateEnemy(Enemy *enemy,Player player, EnvItem *envItems, int envItemsLength, float delta, int identifier);

#endif