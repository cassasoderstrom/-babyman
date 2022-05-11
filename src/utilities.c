#include "raylib.h"
#include "raymath.h"
#include "utilities.h"
#include "stdio.h"

bool soundload = true;
Sound jump;
Player initPlayer(void)
{
    Player player = { 0 };
    player.position = (Vector2){ 400, 280 };
    player.rec = (Rectangle){player.position.x - 30, player.position.y - 50,50,50};
    player.speed = 0;
    player.canJump = false;
    player.hearts = 3;
    player.collided = false;

    return player;
}

void initEnemy(Enemy enemy[])
{
    int count = 2;
    for(int i = 0;i<MAX_ENEMY;i++){    
    if(count % 2 == 0){
            enemy[i].position = (Vector2){GetRandomValue(880,980),GetRandomValue(60,100)};
        }
        else if(count % 2 != 0){
            enemy[i].position = (Vector2){GetRandomValue(30,130),GetRandomValue(60,100)};
        }
        count++;
        enemy[i].rec.x = enemy[i].position.x -20;
        enemy[i].rec.y = enemy[i].position.y -40;
        enemy[i].rec.width = 40;
        enemy[i].rec.height = 40;
        enemy[i].canJump = false;
        enemy[i].speed = 0;
        enemy[i].active = true;
    }
}

void initWizardEnemy(Enemy wizard[])
{
    for(int i = 0;i<MAX_WIZARD_ENEMY;i++){

        wizard[i].position = (Vector2){GetRandomValue(480,530),GetRandomValue(250,300)};
        wizard[i].rec.x = wizard[i].position.x -30;
        wizard[i].rec.y = wizard[i].position.y -50;
        wizard[i].rec.width = 40;
        wizard[i].rec.height = 40;
        wizard[i].speed = 0;
        wizard[i].active = true;
    }
}

Shoot initShoot(Player player, int i, Shoot shoot[])
{
    shoot[i].rec.x = player.position.x;
    shoot[i].rec.y = player.position.y;
    shoot[i].rec.width = 8;
    shoot[i].rec.height = 3;
    shoot[i].speed.x = 7;
    shoot[i].speed.y = 0;
    shoot[i].active = false;
    shoot[i].isLeft = true;
    shoot[i].color = (Color){250,237,39,255};

    return shoot[i];
}

WizardShoot initWizardShoot(Enemy wizard[], int i, int j, WizardShoot wizardShoot[])
{
    wizardShoot[i].rec.x = wizard[j].position.x;
    wizardShoot[i].rec.y = wizard[j].position.y;
    wizardShoot[i].rec.width = 20;
    wizardShoot[i].rec.height = 20;
    wizardShoot[i].speed.x = 5;
    wizardShoot[i].speed.y = 0;
    wizardShoot[i].active = false;
    wizardShoot[i].isLeft = true;
    wizardShoot[i].color = ORANGE;
    wizardShoot[i].position.x = 0;
    wizardShoot[i].position.y = 0;

    return wizardShoot[i];
}

void initEnvItems(EnvItem envItems[], int choice)
{
    
    int posArr[4];
    FILE* fileptr;
    if(choice == 0) fileptr = fopen("level1.position","r");
    if(choice == 1) fileptr = fopen("level2.position","r");
    if(choice == 2) fileptr = fopen("level3.position","r");
    int i = 0;
    int length = 0;
    if(fileptr){
        fscanf(fileptr, "%d", &length);
        while(i < length){
            fscanf(fileptr,"%d %d %d %d",&posArr[0],&posArr[1],&posArr[2],&posArr[3]);
            envItems[i] = (EnvItem){{ posArr[0],posArr[1],posArr[2],posArr[3] }, 1, GetColor(00) };
            i++;
        }   
    }
    fclose(fileptr);
    
}

Ufo initUfoLeft(Ufo ufoLeft, int width, int height)
{
    ufoLeft.position.x = -1500;
    ufoLeft.position.y = -100;
    ufoLeft.rec.x = 0;
    ufoLeft.rec.y = 0;
    ufoLeft.rec.width = width;
    ufoLeft.rec.height = height;
    ufoLeft.speed.x = 20;
    ufoLeft.speed.y = 0;

    return ufoLeft;
}

Ufo initUfoRight(Ufo ufoRight, int width, int height)
{
    ufoRight.position.x = 2420;
    ufoRight.position.y = -100;
    ufoRight.rec.x = 0;
    ufoRight.rec.y = 0;
    ufoRight.rec.width = width;
    ufoRight.rec.height = height;
    ufoRight.speed.x = -20;
    ufoRight.speed.y = 0;

    return ufoRight;
}

Camera2D initCamera(Camera2D camera, Player player, int width, int height)
{
    camera.target = player.position;
    camera.offset = (Vector2){ width/2.0f, height/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.5f;

    return camera;
}

void UpdatePlayer(Player *player, EnvItem *envItems, int envItemsLength, float delta,float soundvol)
{
    if(soundload){
        jump = LoadSound("music/jump.wav");
        
        soundload = false;
    }
    if (IsKeyDown(KEY_LEFT)) player->position.x -= PLAYER_HOR_SPD*delta;
    if (IsKeyDown(KEY_RIGHT)) player->position.x += PLAYER_HOR_SPD*delta;
    SetSoundVolume(jump,soundvol);
    if (IsKeyDown(KEY_UP) && player->canJump)   
    {
        PlaySound(jump);
        player->speed = -PLAYER_JUMP_SPD;
        player->canJump = false;
    }
    
    int hitObstacle = 0;
    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem *ei = envItems + i;
        Vector2 *p = &(player->position);
        if (ei->blocking &&
            ei->rect.x <= p->x &&
            ei->rect.x + ei->rect.width >= p->x &&
            ei->rect.y >= p->y &&
            ei->rect.y < p->y + player->speed*delta)
        {
            hitObstacle = 1;
            player->speed = 0.0f;
            p->y = ei->rect.y;
        }
    }

    if (!hitObstacle)
    {
        player->position.y += player->speed*delta;
        player->speed += G*delta;
        player->canJump = false;
    }
    else player->canJump = true;
}
void UpdateEnemy(Enemy *enemy, Player player, EnvItem *envItems, int envItemsLength, float delta,int identifier)
{
    if(enemy->position.x<player.position.x){
        enemy->position.x += ENEMY_HOR_SPD*delta;
        
    }
    else{
        enemy->position.x -= ENEMY_HOR_SPD*delta;
        
    }
    if(identifier == 0){
        if (enemy->canJump && enemy->position.y > player.position.y)
        {
            enemy->speed = -PLAYER_JUMP_SPD;
            enemy->canJump = false;
        }
    }

    int hitObstacle = 0;
    for (int i = 0; i < envItemsLength; i++)
    {
        EnvItem *ei = envItems + i;
        Vector2 *p = &(enemy->position);
        if (ei->blocking &&
            ei->rect.x <= p->x &&
            ei->rect.x + ei->rect.width >= p->x &&
            ei->rect.y >= p->y &&
            ei->rect.y < p->y + enemy->speed*delta)
        {
            hitObstacle = 1;
            enemy->speed = 0.0f;
            p->y = ei->rect.y;
        }
    }

    
    if (!hitObstacle)
    {
        enemy->position.y += enemy->speed*delta;
        enemy->speed += G*delta;
        enemy->canJump = false;
    }
    else if(identifier == 0) enemy->canJump = true;
    
    if(enemy->position.y > 800){
        enemy->active = false;
    }
    
    if(enemy->position.x  > envItems[1].rect.x + 200 && enemy->position.y > 400 && !hitObstacle){
            enemy->canJump = true;
    }
    if(enemy->position.x > envItems[2].rect.x && enemy->position.y > 400 && !hitObstacle){
            enemy->canJump = true;
    }
    if((enemy->position.x < 245 && enemy->position.x > 155) || (enemy->position.x < 845 && enemy->position.x > 755)){
        enemy->canJump = false;
    }
}
