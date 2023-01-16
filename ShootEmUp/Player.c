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
    // Mise à jour de la vitesse en fonction de l'état des touches
    Vec2 velocity = Vec2_Set(input->hAxis, input->vAxis);
    // Mise à jour de la position
    self->position = Vec2_Add( // Nouvelle pos. = ancienne pos. +
        self->position, // (vitesse * temps écoulé)
        Vec2_Scale(velocity, Timer_GetDelta(g_time)));

    if (input->shootPressed) {
        Vec2 velocity = Vec2_Set(4.0f, 0.0f);
        Bullet* bullet = Bullet_New(
            self->scene, self->position, velocity, BULLET_PLAYER, 90.0f);
        Scene_AppendBullet(self->scene, bullet);
        printf("shoot\n");
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
    // Changez 48 par une autre valeur pour grossir ou réduire l'objet
    dst.h = 48 * PIX_TO_WORLD * scale;
    dst.w = 48 * PIX_TO_WORLD * scale;
    Camera_WorldToView(camera, self->position, &dst.x, &dst.y);
    // Le point de référence est le centre de l'objet
    dst.x -= 0.50f * dst.w;
    dst.y -= 0.50f * dst.h;
    // On affiche en position dst (unités en pixels)
    SDL_RenderCopyExF(
        renderer, self->texture, NULL, &dst, 90.0f, NULL, 0);
}

void Player_Damage(Player *self, int damage)
{
    printf("Le potooship a mal\n");
}