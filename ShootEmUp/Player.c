#include "Player.h"
#include "Scene.h"
#include "Common.h"

Player *Player_New(Scene *scene)
{
    Player *self = (Player *)calloc(1, sizeof(Player));
    AssertNew(self);

    Assets *assets = Scene_GetAssets(scene);

    self->scene = scene;
    self->position = Vec2_Set(1.0f, 4.5f);
    self->radius = 0.25f;
    self->texture = assets->player;
    self->remainingLives = 5;
    self->maximumLives = 5;

    self->isSpeedPowerUpActivated = false;
    // La dur�e du powerup vitesse est de 8 secondes
    self->speedPowerUpDuration = 8;
    // La dur�e du powerup gun 1 est de 8 secondes
    self->gun1PowerUpDuration = 8;
    // La dur�e du powerup gun 2 est de 8 secondes
    self->gun2PowerUpDuration = 8;


    return self;
}

void Player_Delete(Player *self)
{
    if (!self) return;
    free(self);
}

void Player_Update(Player *self)
{
    // On r�cup�re des infos essentielles (communes � tout objet)
    Scene* scene = self->scene;
    Input* input = Scene_GetInput(scene);
    // Mise � jour de la vitesse en fonction de l'�tat des touches
  
    // Lorsque que PowerUp est activ�, on double la vitesse
    if (self->isSpeedPowerUpActivated)
    {
        if (input->hAxis > 0)
            input->hAxis = 6;
        else if (input->hAxis < 0)
           input->hAxis = -6;

        if (input->vAxis > 0)
            input->vAxis = 6;
        else if (input->vAxis < 0)
            input->vAxis = -6;

        // On regarde si on doit le d�sactiver
        if (g_time->currentTime - self->speedPowerUpActivatedSince > self->speedPowerUpDuration)
        {
            self->isSpeedPowerUpActivated = false;
        }
    }
    Vec2 velocity = Vec2_Set(input->hAxis, input->vAxis);

    // Mise � jour de la position
    Vec2 possiblePosition = Vec2_Add( // Nouvelle pos. = ancienne pos. +
    self->position, // (vitesse * temps �coul�)
    Vec2_Scale(velocity, Timer_GetDelta(g_time)));


    // on fait attention a ne pas sortir du jeu.
    if (possiblePosition.x > 15.25)
        possiblePosition.x = self->position.x;
    if (possiblePosition.x < 0.5)
        possiblePosition.x = self->position.x;
    if (possiblePosition.y > 8.30)
        possiblePosition.y = self->position.y;
    if (possiblePosition.y < 0.70)
        possiblePosition.y = self->position.y;

    self->position = possiblePosition;
    
    
    // On attends que l'animation de mort du joueur soit pass� pour pass� son �tat en PLAYER_DEAD
    if (self->state == PLAYER_DYING)
    {
        if (g_time->currentTime - self->isDyingSince >= 1)
        {
            self->state = PLAYER_DEAD;
            printf("Player is DEAD\n");
        }
    }

    // G�re le tir du joueur
    if (input->shootPressed) {
        Vec2 velocity = Vec2_Set(7.0f, 0.0f);
        Bullet* bullet = Bullet_New(
            self->scene, self->position, velocity, BULLET_PLAYER, 90.0f);
        Scene_AppendBullet(self->scene, bullet);
        Mix_PlayChannel(-1, self->scene->assets->PlayerBulletSound, 0);
    }

    // G�re les PowerUp de canon

    if (self->isGun1PowerUpActivated)
    {
        // On regarde si on doit d�sactiver le canon 1
        if (g_time->currentTime - self->gun1PowerUpActivatedSince > self->gun1PowerUpDuration)
        {
            self->isGun1PowerUpActivated = false;
            Assets* assets = Scene_GetAssets(scene);
            self->texture = assets->player;
        }
    }
    else if (self->isGun2PowerUpActivated)
    {
        // On regarde si on doit d�sactiver le canon 2
        if (g_time->currentTime - self->gun2PowerUpActivatedSince > self->gun2PowerUpDuration)
        {
            self->isGun2PowerUpActivated = false;
            Assets* assets = Scene_GetAssets(scene);
            self->texture = assets->player;
        }
    }
}

void Player_Render(Player *self)
{
    // On r�cup�re des infos essentielles (communes � tout objet)
    Scene* scene = self->scene;
    SDL_Renderer* renderer = Scene_GetRenderer(scene);
    Assets* assets = Scene_GetAssets(scene);
    Camera* camera = Scene_GetCamera(scene);
    // On calcule la position en pixels en fonction de la position
    // en tuiles, la taille de la fen�tre et la taille des textures.
    float scale = Camera_GetWorldToViewScale(camera);
    SDL_FRect dst = { 0 };
    // Changez 48 par une autre valeur pour grossir ou r�duire l'objet
    dst.h = 120 * PIX_TO_WORLD * scale;
    dst.w = 120 * PIX_TO_WORLD * scale;
    Camera_WorldToView(camera, self->position, &dst.x, &dst.y);
    // Le point de r�f�rence est le centre de l'objet
    dst.x -= 0.50f * dst.w;
    dst.y -= 0.50f * dst.h;
    // On affiche en position dst (unit�s en pixels)
    SDL_RenderCopyExF(
        renderer, self->texture, NULL, &dst, 90.0f, NULL, 0);
}

void Player_Damage(Player *self, int damage)
{
    self->remainingLives--;
    if (self->remainingLives == 0)
    {
        self->state = PLAYER_DYING;
        self->isDyingSince = g_time->currentTime;
    }
}