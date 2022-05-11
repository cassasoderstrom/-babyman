#include "raylib.h"
#include "collision.h"


bool isPlayerCollided(Player player, Enemy enemy)
{
    if(enemy.position.x-20 < player.position.x-30 + player.rec.width &&
        enemy.position.x-20 + enemy.rec.width > player.position.x-30 &&
        enemy.position.y-40 < player.position.y-50 + player.rec.height &&
        enemy.rec.height + enemy.position.y-40 > player.position.y-50)
    {
        return true;
    }  
    return false;
}

bool isBulletCollided(Shoot shoot, Enemy enemy)
{
    if(enemy.position.x-20 < shoot.rec.x + shoot.rec.width &&
       enemy.position.x-20 + enemy.rec.width > shoot.rec.x &&
       enemy.position.y-40 < shoot.rec.y + shoot.rec.height &&
       enemy.rec.height + enemy.position.y-40 > shoot.rec.y)
    {
        
        return true;
    }
    return false;
}

bool isWizFireballCollided(WizardShoot wizShoot, Player player)
{
    if(player.position.x-30 < wizShoot.rec.x + wizShoot.rec.width &&
       player.position.x-30 + player.rec.width > wizShoot.rec.x &&
       player.position.y-50 < wizShoot.rec.y + wizShoot.rec.height &&
       player.rec.height + player.position.y-50 > wizShoot.rec.y){
        return true;
    }
    return false;
}