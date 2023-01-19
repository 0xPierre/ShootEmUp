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
    // La durée du powerup vitesse est de 8 secondes
    self->speedPowerUpDuration = 8;
    // La durée du powerup gun 1 est de 8 secondes
    self->gun1PowerUpDuration = 8;
    // La durée du powerup gun 2 est de 8 secondes
    self->gun2PowerUpDuration = 8;

    self->isGun1PowerUpActivated = false;
    self->isGun2PowerUpActivated = false;

    self->isShieldActivated = false;
    self->shieldDuration = 2.5;

    return self;
}

void Player_Delete(Player *self)
{
    if (!self) return;
    free(self);
}

void Player_Update(Player *self)
{
    // On récupère des infos essentielles (communes à tout objet)
    Scene* scene = self->scene;
    Input* input = Scene_GetInput(scene);

    if (input->invincibilityPressed)
    {
        self->isInvincible = !self->isInvincible;
    }

    // Lorsque que PowerUp est activé, on double la vitesse
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

        // On regarde si on doit le désactiver
        if (g_time->currentTime - self->speedPowerUpActivatedSince > self->speedPowerUpDuration)
        {
            self->isSpeedPowerUpActivated = false;
        }
    }
    Vec2 velocity = Vec2_Set(input->hAxis, input->vAxis);

    // Mise à jour de la position
    Vec2 possiblePosition = Vec2_Add( // Nouvelle pos. = ancienne pos. +
    self->position, // (vitesse * temps écoulé)
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
    
    
    // On attends que l'animation de mort du joueur soit passé pour passé son état en PLAYER_DEAD
    if (self->state == PLAYER_DYING)
    {
        if (g_time->currentTime - self->isDyingSince >= 1)
        {
            self->state = PLAYER_DEAD;
            printf("Player is DEAD\n");
        }
    }

    // Gère le tir du joueur
    if (input->shootPressed) {
        // Lorsque que le Canon 1 est activé, on tire 2 projectile
        if (scene->player->isGun1PowerUpActivated || scene->player->isGun2PowerUpActivated) {
            Vec2 velocity = Vec2_Set(7.0f, 0.0f);

            Bullet* bullet_1 = Bullet_New(
                self->scene,
                // Le + 0.8 permet de déplacer la position de départ du projectile pour éviter qu'il apparaissent en dessous du player.
                Vec2_Set(self->position.x + 0.8f, self->position.y + 0.4f),
                velocity, BULLET_PLAYER, 90.0f);

            Bullet* bullet_2 = Bullet_New(
                self->scene,
                Vec2_Set(self->position.x + 0.8f, self->position.y - 0.4f),
                velocity, BULLET_PLAYER, 90.0f);

            Scene_AppendBullet(self->scene, bullet_1);
            Scene_AppendBullet(self->scene, bullet_2);

            Mix_PlayChannel(-1, self->scene->assets->PlayerBulletSound, 0);
        }
        else {
            Vec2 velocity = Vec2_Set(7.0f, 0.0f);
            Bullet* bullet = Bullet_New(
                self->scene, self->position, velocity, BULLET_PLAYER, 90.0f);
            Scene_AppendBullet(self->scene, bullet);
            Mix_PlayChannel(-1, self->scene->assets->PlayerBulletSound, 0);
        }
    }

    // Gère les PowerUp de canon

    if (self->isGun1PowerUpActivated)
    {
        // On regarde si on doit désactiver le canon 1
        if (g_time->currentTime - self->gun1PowerUpActivatedSince > self->gun1PowerUpDuration)
        {
            self->isGun1PowerUpActivated = false;
            Assets* assets = Scene_GetAssets(scene);
            self->texture = assets->player;
        }
    }
    else if (self->isGun2PowerUpActivated)
    {
        // On regarde si on doit désactiver le canon 2
        if (g_time->currentTime - self->gun2PowerUpActivatedSince > self->gun2PowerUpDuration)
        {
            self->isGun2PowerUpActivated = false;
            Assets* assets = Scene_GetAssets(scene);
            self->texture = assets->player;
        }
    }

    // On regarde si on doit désactiver le bouclier
    if (self->isShieldActivated)
    {
        if (g_time->currentTime - self->shieldActivatedSince > self->shieldDuration)
        {
            self->isShieldActivated = false;
        }
    }
}

void Player_Render(Player *self)
{
    // On récupère des infos essentielles (communes à tout objet)
    Scene* scene = self->scene;
    SDL_Renderer* renderer = Scene_GetRenderer(scene);
    Assets* assets = Scene_GetAssets(scene);
    Camera* camera = Scene_GetCamera(scene);
    // On calcule la position en pixels en fonction de la position
    // en tuiles, la taille de la fenêtre et la taille des textures.
    float scale = Camera_GetWorldToViewScale(camera);
    SDL_FRect dst = { 0 };
    dst.h = 120 * PIX_TO_WORLD * scale;
    dst.w = 120 * PIX_TO_WORLD * scale;
    Camera_WorldToView(camera, self->position, &dst.x, &dst.y);
    // Le point de référence est le centre de l'objet
    dst.x -= 0.50f * dst.w;
    dst.y -= 0.50f * dst.h;
    // On affiche en position dst (unités en pixels)
    SDL_RenderCopyExF(
        renderer, self->texture, NULL, &dst, 90.0f, NULL, 0);
    
    // Affiche le bouclier lorsqu'il est actif 
    if (self->isShieldActivated)
    {
        SDL_FRect dst_shield = { 0 };

        // La taille du shield est mise en fonction de la texture du player.
        if (self->isGun1PowerUpActivated || self->isGun2PowerUpActivated)
        {
            dst_shield.h = 100 * PIX_TO_WORLD * scale;
            dst_shield.w = 100 * PIX_TO_WORLD * scale;
        }
        else {
            dst_shield.h = 70 * PIX_TO_WORLD * scale;
            dst_shield.w = 70 * PIX_TO_WORLD * scale;
        }
        Camera_WorldToView(camera, self->position, &dst_shield.x, &dst_shield.y);
        // Le point de référence est le centre de l'objet
        dst_shield.x -= 0.50f * dst_shield.w;
        dst_shield.y -= 0.50f * dst_shield.h;

        SDL_RenderCopyExF(
            renderer, assets->ShieldPlayer, NULL, &dst_shield, 90.0f, NULL, 0);
    }
}

void Player_Damage(Player *self, int damage)
{
    if (self->remainingLives > 0) {
        // Le joueur perds de la vie seulement quand il n'est pas invicible ( logique non ? ) et qu'il n'a pas de shield
        if (!self->isInvincible && !self->isShieldActivated)
            self->remainingLives--;

        // Le joueur meurt si il n'a plus de vie.
        if (self->remainingLives == 0)
        {
            self->state = PLAYER_DYING;
            self->isDyingSince = g_time->currentTime;
        }
        // Le joueur reçoit un bouclier seulement si il n'est pas déjà sous bouclier
        else if (!self->isShieldActivated)
        {
            self->shieldActivatedSince = g_time->currentTime;
            self->isShieldActivated = true;
        }
    }
}

void Heart_Render(Player* self)
{
    // On récupère des infos essentielles (communes à tout objet)
    Scene* scene = self->scene;
    SDL_Renderer* renderer = Scene_GetRenderer(scene);
    Assets* assets = Scene_GetAssets(scene);
    Camera* camera = Scene_GetCamera(scene);
    // On calcule la position en pixels en fonction de la position
    // en tuiles, la taille de la fenêtre et la taille des textures.
    float scale = Camera_GetWorldToViewScale(camera);

    for (int i = 0; i < self->remainingLives; i++)
    {
        SDL_FRect dst = { 0 };
        dst.h = 0.5f * scale;
        dst.w = 0.5f * scale;
        Camera_WorldToView(camera, Vec2_Set(.5f+i*0.6f, 0.5f), &dst.x, &dst.y);
        // Le point de référence est le centre de l'objet
        dst.x -= 0.50f * dst.w;
        dst.y -= 0.50f * dst.h;
        // On affiche en position dst (unités en pixels)
        SDL_RenderCopyExF(
            renderer, assets->playerHeart, NULL, &dst, 0.0f, NULL, 0);
    }
}

void Collectables_Bar_Render(Player* self)
{
    // On récupère des infos essentielles (communes à tout objet)
    Scene* scene = self->scene;
    SDL_Renderer* renderer = Scene_GetRenderer(scene);
    Assets* assets = Scene_GetAssets(scene);
    Camera* camera = Scene_GetCamera(scene);
    // On calcule la position en pixels en fonction de la position
    // en tuiles, la taille de la fenêtre et la taille des textures.
    float scale = Camera_GetWorldToViewScale(camera);

    if (self->isGun1PowerUpActivated || self->isGun2PowerUpActivated) {
        SDL_Texture* gun1Texture;
        int percentage;
        // Récupère le pourcentage d'utilisation en fonction du power up utilisé ( gun 1 ou gun 2 )
        if (self->isGun1PowerUpActivated)
            percentage = 100.f-(g_time->currentTime - self->gun1PowerUpActivatedSince) * 100 / self->gun1PowerUpDuration;
        else
            percentage = 100.f - (g_time->currentTime - self->gun2PowerUpActivatedSince) * 100 / self->gun2PowerUpDuration;
        /// Choix de la texture de la bar
        if (percentage > 80)
        {
            gun1Texture = assets->Gun100PowerUpBar;
        }
        else if (percentage > 60)
        {
            gun1Texture = assets->Gun80PowerUpBar;
        }
        else if (percentage > 40)
        {
            gun1Texture = assets->Gun60PowerUpBar;
        }
        else if (percentage > 20)
        {
            gun1Texture = assets->Gun40PowerUpBar;
        }
        else if (percentage > 5)
        {
            gun1Texture = assets->Gun20PowerUpBar;
        }
        else
        {
            gun1Texture = assets->Gun00PowerUpBar;
        }

        SDL_FRect dst = { 0 };
        dst.h = 35 * PIX_TO_WORLD * scale;
        dst.w = 100 * PIX_TO_WORLD * scale;
        Camera_WorldToView(camera, Vec2_Set(.5, 1), &dst.x, &dst.y);
        // Le point de référence est le centre de l'objet
        dst.x = 0.10f * dst.w;
        dst.y -= .95f * dst.h;
        // On affiche en position dst (unités en pixels)
        SDL_RenderCopyExF(renderer, gun1Texture, NULL, &dst, 0.0f, NULL, 0);
    }
    
    if (self->isSpeedPowerUpActivated)
    {
        SDL_Texture* speedTexture;
        // Récupère le pourcentage d'utilisation du powerup vitesse
        int percentage = 100.f - (
            g_time->currentTime - self->speedPowerUpActivatedSince
           ) * 100 / self->speedPowerUpDuration;

        /// Choix de la texture de la bar
        if (percentage > 80)
        {
            speedTexture = assets->Speed100PowerUpBar;
        }
        else if (percentage > 60)
        {
            speedTexture = assets->Speed80PowerUpBar;
        }
        else if (percentage > 40)
        {
            speedTexture = assets->Speed60PowerUpBar;
        }
        else if (percentage > 20)
        {
            speedTexture = assets->Speed40PowerUpBar;
        }
        else if (percentage > 5)
        {
            speedTexture = assets->Speed20PowerUpBar;
        }
        else
        {
            speedTexture = assets->Speed00PowerUpBar;
        }

        SDL_FRect dst = { 0 };
        dst.h = 35 * PIX_TO_WORLD * scale;
        dst.w = 100 * PIX_TO_WORLD * scale;
        Camera_WorldToView(camera, Vec2_Set(.5, 1), &dst.x, &dst.y);
        // Le point de référence est le centre de l'objet
        dst.x = 0.10f * dst.w;
        dst.y -= 0.95f * dst.h;
        // Si le powerup gun 1 ou gun 2 est déjà activé, alors la hauteur de la bar est plus élevé ( là c négatif psk voilà )
        if (self->isGun1PowerUpActivated || self->isGun2PowerUpActivated)
            dst.y -= 1.f * dst.h;

        // On affiche en position dst (unités en pixels)
        SDL_RenderCopyExF(renderer, speedTexture, NULL, &dst, 0.0f, NULL, 0);
    }
}