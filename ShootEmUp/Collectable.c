#include "Collectable.h"
#include "Scene.h"
#include "Math.h"

Collectable* Collectable_New(Scene* scene, CollectableType type, Vec2 position)
{
    Collectable* self = (Collectable*)calloc(1, sizeof(Collectable));
    AssertNew(self);

    self->scene = scene;
    scene->lastCollectableTime = g_time->currentTime;
    self->position = position;
    self->radius = 0.4f;
    self->worldW = 30 * PIX_TO_WORLD;
    self->worldH = 30 * PIX_TO_WORLD;
    self->radius = 0.05f;
    self->velocity = Vec2_Set(-2, 0);
    self->type = (int)type;
   
    Assets* assets = Scene_GetAssets(self->scene);

    switch (type)
    {
    case COLLECTABLE_HEALTH:
        self->texture = assets->CollectableHealth;
        break;

    case COLLECTABLE_SPEED:
        self->texture = assets->CollectableSpeed;
        break;

    case COLLECTABLE_GUN_UPGRADE_1:
        self->texture = assets->CollectableBullet1;
        break;

    case COLLECTABLE_GUN_UPGRADE_2:
        self->texture = assets->CollectableBullet2;
        break;
    }

    return self;
}

void Collectable_Delete(Collectable* self)
{
    if (!self) return;
    free(self);
}

void Collectable_Update(Collectable* self)
{
    // On récupère des infos essentielles (communes à tout objet)
    Scene* scene = self->scene;
    Input* input = Scene_GetInput(scene);
    Vec2 velocity = self->velocity;
    // Mise à jour de la position
    self->position = Vec2_Add( // Nouvelle pos. = ancienne pos. +
        self->position, // (vitesse * temps écoulé)
        Vec2_Scale(velocity, Timer_GetDelta(g_time)));
}

void Collectable_Render(Collectable* self)
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
    // Changez 48 par une autre valeur pour grossir ou réduire l'objet
    dst.h = self->worldH * scale;
    dst.w = self->worldW * scale;
    Camera_WorldToView(camera, self->position, &dst.x, &dst.y);
    // Le point de référence est le centre de l'objet
    dst.x -= 0.50f * dst.w;
    dst.y -= 0.50f * dst.h;
    // On affiche en position dst (unités en pixels)
    SDL_RenderCopyExF(
        renderer, self->texture, NULL, &dst, 90.0f, NULL, 0);

}


void createRandomCollectable(Scene* scene)
{
    // Calcul du type de collectable
    int collectableRandType = rand() % 100;
    CollectableType collectableType = COLLECTABLE_GUN_UPGRADE_1;

    if (collectableRandType >= 75)
    {
        collectableType = COLLECTABLE_HEALTH;
    }
    else if (collectableRandType >= 50)
    {
        collectableType = COLLECTABLE_GUN_UPGRADE_1;
    }
    else if (collectableRandType >= 25)
    {
        collectableType = COLLECTABLE_GUN_UPGRADE_2;
    }
    else if (collectableRandType >= 0)
    {
        collectableType = COLLECTABLE_SPEED;
    }

    // Calcul de la position en Y
    int posY = rand() % ((8 + 1) - 1) + 1;
    Collectable* collectable = Collectable_New(scene, collectableType, Vec2_Set(17, (float)posY));
    
    scene->collectablesCount++;
    scene->collectables[scene->collectablesCount] = collectable;
}

void manageCollectable(Collectable* collectable)
{
    Scene* scene = collectable->scene;
    Assets* assets = Scene_GetAssets(scene);
    Player* player = scene->player;

    int type = collectable->type;
    switch ((int)type)
    {
    case COLLECTABLE_HEALTH:
        // La vie est ajouté seulement si le joueur n'est pas à son maximum de vie
        if (player->remainingLives < player->maximumLives)
            player->remainingLives++;
        break;

    case COLLECTABLE_SPEED:
        // Active le powerup vitesse
        player->isSpeedPowerUpActivated = true;
        player->speedPowerUpActivatedSince = g_time->currentTime;
        break;

    case COLLECTABLE_GUN_UPGRADE_1:
        // on active l'upgrade de Canon 1
        player->isGun1PowerUpActivated = true;
        // on désactive l'upgrade De Canon 2
        player->isGun2PowerUpActivated = false;
        player->gun1PowerUpActivatedSince = g_time->currentTime;
        player->texture = assets->player_gun_1;
        break;

    case COLLECTABLE_GUN_UPGRADE_2:
        // on active l'upgrade de Canon 2
        player->isGun2PowerUpActivated = true;
        // on désactive l'upgrade De Canon 1
        player->isGun1PowerUpActivated = false;
        player->gun2PowerUpActivatedSince = g_time->currentTime;
        player->texture = assets->player_gun_2;
        break;
    }

}