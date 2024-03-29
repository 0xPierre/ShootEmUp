#include "Bullet.h"
#include "Common.h"
#include "Scene.h"

Bullet *Bullet_New(Scene *scene, Vec2 position, Vec2 velocity, int type, float angle)
{
    Bullet *self = (Bullet *)calloc(1, sizeof(Bullet));
    AssertNew(self);

    self->position = position;
    self->velocity = velocity;
    self->type = type;
    self->angle = angle;
    self->scene = scene;
    self->fromPlayer = false;

    Assets *assets = Scene_GetAssets(scene);
    switch (type)
    {
    case BULLET_FIGHTER:
        self->worldW = 8 * PIX_TO_WORLD;
        self->worldH = 16 * PIX_TO_WORLD;
        self->radius = 0.05f;
        self->fromPlayer = false;
        self->texture = assets->fighterBullet;
        break;
    case BULLET_FIGHTER2:
        self->worldW = 20 * PIX_TO_WORLD;
        self->worldH = 40 * PIX_TO_WORLD;
        self->radius = 0.15f;
        self->fromPlayer = false;
        self->texture = assets->fighterBullet2;
        break;
    case BULLET_FIGHTER3:
        self->worldW = 18 * PIX_TO_WORLD;
        self->worldH = 16 * PIX_TO_WORLD;
        self->radius = 0.1f;
        self->fromPlayer = false;
        self->texture = assets->fighterBullet3;
        break;
    default:
    case BULLET_PLAYER:
        self->texture = assets->playerBullet;
        // Changement de texture en fonction des powerup
        if (scene->player->isGun1PowerUpActivated)
        {
            self->worldW = 15 * PIX_TO_WORLD;
            self->worldH = 15 * PIX_TO_WORLD;
            self->texture = assets->playerBulletGun1;
            self->radius = 0.08f;
        }
        else if (scene->player->isGun2PowerUpActivated)
        {
            self->worldW = 20 * PIX_TO_WORLD;
            self->worldH = 26 * PIX_TO_WORLD;
            self->texture = assets->playerBulletGun2;
            self->angle = 90;
            self->radius = 0.1f;
        }
        else
        {
            self->worldW = 8 * PIX_TO_WORLD;
            self->worldH = 16 * PIX_TO_WORLD;
            self->texture = assets->playerBullet;
            self->radius = 0.05f;
        }
        self->fromPlayer = true;
        break;
    }

    return self;
}

void Bullet_Delete(Bullet *self)
{
    if (!self) return;
    free(self);
}

void Bullet_Update(Bullet *self)
{
    // On r�cup�re des infos essentielles (communes � tout objet)
    Scene* scene = self->scene;
    Input* input = Scene_GetInput(scene);
    // Mise � jour de la vitesse en fonction de l'�tat des touches
    Vec2 velocity = self->velocity;
    // Mise � jour de la position
    self->position = Vec2_Add( // Nouvelle pos. = ancienne pos. +
        self->position, // (vitesse * temps �coul�)
        Vec2_Scale(velocity, Timer_GetDelta(g_time)));
}

void Bullet_Render(Bullet *self)
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
    dst.h = self->worldH * scale;
    dst.w = self->worldW * scale;
    Camera_WorldToView(camera, self->position, &dst.x, &dst.y);
    // Le point de r�f�rence est le centre de l'objet
    dst.x -= 0.50f * dst.w;
    dst.y -= 0.50f * dst.h;
    // On affiche en position dst (unit�s en pixels)
    SDL_RenderCopyExF(
        renderer, self->texture, NULL, &dst, 90.0f, NULL, 0);
}