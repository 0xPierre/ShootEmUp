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
    self->remainingLives = 2;

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
    // Mise à jour de la position, on fait attention a ne pas sortir du jeu.
    if ( self->position.x+input->hAxis   < 19.5 && self->position.x+input->hAxis > -3.67 && self->position.y+input->vAxis < 12.5 && self->position.y+input->vAxis > -3.5 )
    { 
            self->position = Vec2_Add( // Nouvelle pos. = ancienne pos. +
            self->position, // (vitesse * temps écoulé)
            Vec2_Scale(velocity, Timer_GetDelta(g_time)));

            
    }
    
      
    // On attends que l'animation de mort du joueur soit passé pour passé son état en PLAYER_DEAD
    if (self->state == PLAYER_DYING)
    {
        if (g_time->currentTime - self->isDyingSince >= 1)
        {
            self->state = PLAYER_DEAD;
            printf("Player is DEAD\n");
        }
    }

    if (input->shootPressed) {
        Vec2 velocity = Vec2_Set(7.0f, 0.0f);
        Bullet* bullet = Bullet_New(
            self->scene, self->position, velocity, BULLET_PLAYER, 90.0f);
        Scene_AppendBullet(self->scene, bullet);
        Mix_PlayChannel(-1, self->scene->assets->PlayerBulletSound, 0);
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
    dst.h = 120 * PIX_TO_WORLD * scale;
    dst.w = 120 * PIX_TO_WORLD * scale;
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
    self->remainingLives--;
    if (self->remainingLives == 0)
    {
        self->state = PLAYER_DYING;
        self->isDyingSince = g_time->currentTime;
    }
}