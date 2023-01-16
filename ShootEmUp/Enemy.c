#include "Enemy.h"
#include "Common.h"
#include "Scene.h"

Enemy *Enemy_New(Scene *scene, int type, Vec2 position)
{
    Enemy *self = (Enemy *)calloc(1, sizeof(Enemy));
    AssertNew(self);

    self->scene = scene;
    self->position = position;
    self->type = type;
    self->state = ENEMY_FIRING;
    self->lastBulletTime = g_time->currentTime;

    /*
    Permet de générer un mouvement qui ne ressemble pas aux autres objets.
    */
    self->randomStartingTickX = rand() % 1000;
    self->randomStartingTickY = rand() % 1000;

    Assets *assets = Scene_GetAssets(self->scene);
    switch (type)
    {
    case ENEMY_FIGHTER_1:
        self->worldW = 64 * PIX_TO_WORLD;
        self->worldH = 64 * PIX_TO_WORLD;
        self->radius = 0.4f;
        self->texture = assets->fighter;
        self->remainingLives = 1; 
        self->timeBetweenBullets = 1.5;
        break;

    case ENEMY_FIGHTER_2:
        self->worldW = 64 * PIX_TO_WORLD;
        self->worldH = 64 * PIX_TO_WORLD;
        self->radius = 0.4f;
        self->texture = assets->fighter;
        self->remainingLives = 1;
        self->timeBetweenBullets = 1.5;
        break;

    default:
        assert(false);
        break;
    }

    return self;
}

void Enemy_Delete(Enemy *self)
{
    if (!self) return;
    free(self);
}

void Enemy_Update(Enemy *self)
{
    // Créé un projectil toutes les "timeBetweenBullets"   
    if ((g_time->currentTime - self->lastBulletTime) >= self->timeBetweenBullets) {
        Vec2 velocity = Vec2_Set(-4.0, 0.0f);
        Bullet* bullet = Bullet_New(
            self->scene, self->position, velocity, BULLET_FIGHTER, 90.0f);
        Scene_AppendBullet(self->scene, bullet);

        self->lastBulletTime = g_time->currentTime;
    }

    // Gère le mouvements des ennemis
    if (self->type == ENEMY_FIGHTER_1 || self->type == ENEMY_FIGHTER_2)
    {
        // Calcul de la vélocité en utilisant cos et sin pour faire bouger l'ennemi.
        float Xvelocity = sinf(g_time->currentTime + self->randomStartingTickX) / 3;
        float YVelocity = cosf(g_time->currentTime + self->randomStartingTickY) / 2;

        Vec2 velocity = Vec2_Set(
            Xvelocity,
            YVelocity
        );
        self->position = Vec2_Add(
            self->position,
            Vec2_Scale(velocity, Timer_GetDelta(g_time))
        );
    }
}

void Enemy_Render(Enemy *self)
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

void Enemy_Damage(Enemy *self, int damage)
{
    self->remainingLives--;

    if (self->remainingLives == 0) {
        self->state = ENEMY_DEAD;
    }
}
