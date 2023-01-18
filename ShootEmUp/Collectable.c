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
   
    Assets* assets = Scene_GetAssets(self->scene);

    printf("Collectable Spawned\n");

    switch (type)
    {
    case COLLECTABLE_HEALTH:
        self->texture = assets->CollectibleHealth;
        self->radius = 0.4f;
        self->worldW = 30 * PIX_TO_WORLD;
        self->worldH = 30 * PIX_TO_WORLD;
        self->radius = 0.05f;
        self->velocity = Vec2_Set(-2, 0);
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
    // Calcul du type de collectabl
    int collectableRandType = rand() % 100;
    CollectableType collectableType = COLLECTABLE_HEALTH;

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
    Collectable* collectable = Collectable_New(scene, collectableType, Vec2_Set(17, posY));
    
    scene->collectablesCount++;
    scene->collectables[scene->collectablesCount] = collectable;
}

void manageCollectable(Collectable* collectable)
{
    if (collectable->type == COLLECTABLE_HEALTH)
    {
        collectable->scene->player->remainingLives++;
    }
}