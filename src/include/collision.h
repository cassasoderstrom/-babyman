#ifndef __collision_h__
#define __collision_h__

#include "utilities.h"

/**
 * @brief Check if player collides with enemy
 * 
 * @param player Player struct
 * @param enemy Enemy struct
 * @return true if collided
 * @return false if not collided
 */
bool isPlayerCollided(Player player, Enemy enemy);

/**
 * @brief Check if bullet collides with enemy
 * 
 * @param shoot Bullet struct
 * @param enemy Enemy struct
 * @return true if collided
 * @return false if not collided
 */
bool isBulletCollided(Shoot shoot, Enemy enemy);

/**
 * @brief Check if fireball collides with player
 * 
 * @param wizShoot Wizard fireball struct
 * @param player Player struct
 * @return true if collided
 * @return false if not collided
 */
bool isWizFireballCollided(WizardShoot wizShoot, Player player);

#endif