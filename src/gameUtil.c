#include "./include/gameUtil.h"
#include "./include/collision.h"
#include "./include/raylib.h"

bool shouldShrink = false;
Sound pew;
Sound damage;
Sound fireSound;

void SetVolume(Music music,Music game, Sound dead, float musicVol, float soundVol)
{
    SetSoundVolume(fireSound, soundVol);
    SetSoundVolume(damage, soundVol);
    SetSoundVolume(pew, soundVol);
    SetSoundVolume(dead, soundVol);
    SetMusicVolume(music, musicVol);
    SetMusicVolume(game, musicVol);
}

void LoadSounds(void)
{
    pew = LoadSound("music/pew.wav");
    fireSound = LoadSound("music/fireball.wav");
    damage = LoadSound("music/minecraftOof.wav");
    
}

void AlienSpawning(GameStruct *g, int *spawner, int seconds)
{
    if (*spawner > 290 || *spawner < 10){
        if (seconds / 60 > 4){
            g->isSpawning = true;
        }
    }
    else
    {
        g->isSpawning = false;
    }

    if (*spawner == 300){
        if (seconds / 60 < 20)
            g->maxenemy += 3;
        if (seconds / 60 >= 20 && seconds / 60 < 40)
            g->maxenemy += 4;
        if (seconds / 60 >= 40 && seconds / 60 < 60)
            g->maxenemy += 5;
        if (seconds / 60 >= 60)
            g->maxenemy += 6;
        *spawner = 0;
    }

    /* Collision detection between player and enemy */
    if (*spawner == 30 && g->player.collided){
        g->player.collided = false;
    }
}

void WizardSpawning(GameStruct *g, int *wizardSpawner, int *portalcounter, int *scaleSize, Texture2D textures[])
{
    if ((*wizardSpawner > 320 && *wizardSpawner < 420) && *portalcounter == 10){
        g->isSpawningWizard = true;
        if (!shouldShrink){
            g->portalRec = (Rectangle){*scaleSize, 177, (float)textures[12].width / 7, (float)textures[12].height};
            *scaleSize += 93;
            *portalcounter = 0;
            if (*scaleSize == 465){
                shouldShrink = true;
            }
        }
    }
    else if ((*wizardSpawner > 430 && *wizardSpawner < 530) && *portalcounter == 10){
        g->isSpawningWizard = true;
        if (shouldShrink){
            g->portalRec = (Rectangle){*scaleSize, 177, (float)textures[12].width / 7, (float)textures[12].height};
            *scaleSize -= 93;
            *portalcounter = 0;
            if (*scaleSize == -93){
                shouldShrink = false;
            }
        }
    }
    else if (*wizardSpawner == 425){
        g->maxWizard += 1;
    }
    if (*wizardSpawner == 530){

        *wizardSpawner = 0;
        g->isSpawningWizard = false;
        *scaleSize = 0;
    }
    if (*portalcounter == 10){
        *portalcounter = 0;
    }
}

void WizardShooting(GameStruct *g, int *seconds)
{
    
    if (*seconds % 60 == 0){
        
        for (int s = 0; s < g->maxWizard; s++){
            for (int fireball = 0; fireball < NUM_WIZARD_SHOOTS; fireball++){
                if (!g->wizardShoot[fireball].active && g->wizard[s].active){
                    g->wizardShoot[fireball].rec.y = g->wizard[s].position.y - 40;
                    g->wizardShoot[fireball].active = true;
                    
                    PlaySound(fireSound);
                    if (g->player.position.y < g->wizard[s].position.y){
                        g->wizardShoot[fireball].isUp = true;
                        g->wizardShoot[fireball].speed.x = 0;
                        g->wizardShoot[fireball].speed.y = 5;
                        g->wizardShoot[fireball].rec.x = g->wizard[s].position.x;
                    }
                    else if (g->player.position.x < g->wizard[s].position.x){
                        g->wizardShoot[fireball].speed.x = 5;
                        g->wizardShoot[fireball].speed.y = 0;
                        g->wizardShoot[fireball].isLeft = true;
                        g->wizardShoot[fireball].rec.x = g->wizard[s].position.x - 45;
                    }
                    else{
                        g->wizardShoot[fireball].speed.x = 5;
                        g->wizardShoot[fireball].speed.y = 0;
                        g->wizardShoot[fireball].isLeft = false;
                        g->wizardShoot[fireball].rec.x = g->wizard[s].position.x + 5;
                    }
                    break;
                }
            }
        }
    }

    for (int j = 0; j < NUM_WIZARD_SHOOTS; j++){
        if (g->wizardShoot[j].active){
            // Movement of fireball
            if (g->wizardShoot[j].isLeft){
                if (g->wizardShoot[j].isUp){
                    g->wizardShoot[j].rec.y -= g->wizardShoot[j].speed.y;
                }
                g->wizardShoot[j].rec.x -= g->wizardShoot[j].speed.x;
            }
            else{
                if (g->wizardShoot[j].isUp){
                    g->wizardShoot[j].rec.y -= g->wizardShoot[j].speed.y;
                }
                g->wizardShoot[j].rec.x += g->wizardShoot[j].speed.x;
            }
        }
    }
}

void GetKeyPresses(GameStruct *g, Texture2D textures[])
{
    
    
    if (IsKeyDown(KEY_LEFT)){
        g->scrollingBack += 0.1f;
        g->frameRec = (Rectangle){0.0f, 0.0f, (float)textures[0].width / 2, (float)textures[0].height};
        g->lookLeft = true;
    }

    if (IsKeyDown(KEY_RIGHT)){
        g->scrollingBack -= 0.1f;
        g->frameRec = (Rectangle){50.0f, 0.0f, (float)textures[0].width / 2, (float)textures[0].height};
        g->lookLeft = false;
    }
    
    if (IsKeyDown(KEY_SPACE)){
        
        g->shootRate += 19;
        for (int i = 0; i < NUM_SHOOTS; i++){
            if (!g->shoot[i].active && g->shootRate % 20 == 0){
                g->shoot[i].rec.y = g->player.position.y - 16;
                g->shoot[i].active = true;
                PlaySound(pew);
                if (g->lookLeft){
                    g->shoot[i].isLeft = true;
                    g->shoot[i].rec.x = g->player.position.x - 20;
                }
                else{
                    g->shoot[i].isLeft = false;
                    g->shoot[i].rec.x = g->player.position.x + 10;
                }
                break;
            
            }
        }
    }

    
}

void UfoSpawner(GameStruct *g, int *spawner, int seconds)
{
    if (g->ufoRight.position.x > 803 && ((*spawner < 299 && *spawner > 130) || seconds / 60 < 5)){
        g->ufoRight.position.x += g->ufoRight.speed.x;
    }
    else if ((*spawner > 10 && *spawner < 129) && seconds / 60 > 4){
        g->ufoRight.position.x -= g->ufoRight.speed.x;
    }

    if (g->ufoLeft.position.x < -5 && ((*spawner < 299 && *spawner > 130) || seconds / 60 < 5)){
        g->ufoLeft.position.x += g->ufoLeft.speed.x;
    }
    else if ((*spawner > 10 && *spawner < 129) && seconds / 60 > 4){
        g->ufoLeft.position.x -= g->ufoLeft.speed.x;
    }
}


void CheckCollision(GameStruct *g, int *spawner, int *score, int progArr[2])
{   
    if (*spawner == 30 && g->player.collided){
        g->player.collided = false;
    }

    if (!g->player.collided){
        for (int j = 0; j < g->maxenemy; j++){
            if (isPlayerCollided(g->player, g->enemy[j])){
                g->player.hearts--;
                if(g->player.hearts > 0) PlaySound(damage);
                g->player.collided = true;
                g->enemy[j].active = false;
                g->enemy[j].position.x = -1000;
                g->enemy[j].position.y = -1000;
            }
        }
        for (int l = 0; l < g->maxWizard; l++){
            if (isPlayerCollided(g->player, g->wizard[l])){
                g->player.hearts--;
                if(g->player.hearts > 0) PlaySound(damage);
                g->player.collided = true;
                g->wizard[l].active = false;
                g->wizard[l].position.x = -1000;
                g->wizard[l].position.y = -1000;
            }
        }
        for (int m = 0; m < g->maxmedkit; m++){
            if (isPlayerCollided(g->player, g->medkit[m])){
                if(g->player.hearts < 3){
                    g->player.hearts++;
                }
                else{
                    g->player.hearts = 3;
                }

                g->player.collided = true;
                g->medkit[m].active = false;
                g->medkit[m].position.x = -1000;
                g->medkit[m].position.y = -1000;
            }
        }
    }

    /* Collision detection between bullet and enemy */
    for (int i = 0; i < NUM_SHOOTS; i++){
        if (g->shoot[i].active){
            for (int j = 0; j < g->maxenemy; j++){
                if (isBulletCollided(g->shoot[i], g->enemy[j])){
                    *score += 300;
                    progArr[0]++;
                    g->shoot[i].active = false;
                    g->enemy[j].active = false;
                    g->enemy[j].position.x = -1000;
                    g->enemy[j].position.y = -1000;
                }
            }
            for (int l = 0; l < g->maxWizard; l++){
                if (isBulletCollided(g->shoot[i], g->wizard[l])){
                    *score += 600;
                    progArr[1]++;
                    g->shoot[i].active = false;
                    g->wizard[l].active = false;
                    g->wizard[l].position.x = -1000;
                    g->wizard[l].position.y = -1000;
                }
            }
        }
    }

    // Collision between wizard fireball and player
    for (int i = 0; i < NUM_WIZARD_SHOOTS; i++){
        if (g->wizardShoot[i].active){
            for (int j = 0; j < g->maxWizard; j++){
                if (isWizFireballCollided(g->wizardShoot[i], g->player)){
                    g->player.hearts-= 3;
                    if(g->player.hearts > 0) PlaySound(damage);
                    g->player.collided = true;
                    g->wizardShoot[i].active = false;
                }
            }
        }
    }
}

void CameraFunc(GameStruct *g)
{
    g->camera.zoom += ((float)GetMouseWheelMove()*0.05f);

    if (g->camera.zoom > 3.0f)
        g->camera.zoom = 3.0f;
    else if (g->camera.zoom < 0.25f)
        g->camera.zoom = 0.25f;

    if (g->player.position.y < 525.0f){
        g->camera.target = (Vector2){g->player.position.x + 20, g->player.position.y + 20};
    }

    if (g->player.position.y > 900.0f){
        g->player.hearts = 0;
    }
}