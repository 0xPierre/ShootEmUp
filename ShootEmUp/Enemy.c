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
    self->randomStartingTickX = (rand() % 1000);
    self->randomStartingTickY = (rand() % 1000);
    printf("%d %d\n", self->randomStartingTickX, self->randomStartingTickY);

    Assets *assets = Scene_GetAssets(self->scene);
    switch (type)
    {
    case ENEMY_FIGHTER_1:
        self->worldW = 120 * PIX_TO_WORLD;
        self->worldH = 120 * PIX_TO_WORLD;
        self->radius = 0.4f;
        self->texture = assets->fighter1;
        self->remainingLives = 1; 
        self->timeBetweenBullets = 1.5;
        break;

    case ENEMY_FIGHTER_2:
        self->worldW = 120 * PIX_TO_WORLD;
        self->worldH = 120 * PIX_TO_WORLD;
        self->radius = 0.4f;
        self->texture = assets->fighter2;
        self->remainingLives = 1;
        self->timeBetweenBullets = 3;
        break;

    case ENEMY_FIGHTER_3:
        self->worldW = 120 * PIX_TO_WORLD;
        self->worldH = 120 * PIX_TO_WORLD;
        self->radius = 0.4f;
        self->texture = assets->fighter3;
        self->remainingLives = 1;
        self->timeBetweenBullets = 1;
        break;

    case ENEMY_FIGHTER_4:
        self->worldW = 240 * PIX_TO_WORLD;
        self->worldH = 240 * PIX_TO_WORLD;
        self->radius = 1.2f;
        self->texture = assets->fighter4;
        self->remainingLives = 2;
        self->timeBetweenBullets = 0.15f;
        break;

     case ENEMY_FIGHTER_5:
        self->worldW = 120 * PIX_TO_WORLD;
        self->worldH = 120 * PIX_TO_WORLD;
        self->radius = 0.4f;
        self->texture = assets->fighter5;
        self->remainingLives = 2;
        self->timeBetweenBullets = 0.5;
        break;

     case ENEMY_FIGHTER_6:
         self->worldW = 240 * PIX_TO_WORLD;
         self->worldH = 240 * PIX_TO_WORLD;
         self->radius = 1.2f;
         self->texture = assets->fighter6;
         self->remainingLives = 2;
         self->timeBetweenBullets = 1.0;
        self-> lastTypeofBullet = 0;
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
    //Créé un projectil toutes les "timeBetweenBullets"
    if ((g_time->currentTime - self->lastBulletTime) >= self->timeBetweenBullets) {
        /*
        * Gère les projectiles des ennemis
        */
        if (self->type == ENEMY_FIGHTER_1 || self->type == ENEMY_FIGHTER_3)
        {
            // Le projectile part tout droit
            Vec2 velocity = Vec2_Set(-4.0, 0.0f);
            Bullet* bullet = Bullet_New(
                self->scene, self->position, velocity, BULLET_FIGHTER, 90.0f);
            Scene_AppendBullet(self->scene, bullet);

        }
        else if (self->type == ENEMY_FIGHTER_2)
        {
            // Le projectile part en diagonale vers le haut
            Vec2 velocity_1 = Vec2_Set(-3.0, 0.5f);
            Bullet* bullet_1 = Bullet_New(
                self->scene, self->position, velocity_1, BULLET_FIGHTER, 90.0f);
            Scene_AppendBullet(self->scene, bullet_1);

            // Le projectile part en diagonale vers le bas
            Vec2 velocity_2 = Vec2_Set(-3.0, -0.5f);
            Bullet* bullet_2 = Bullet_New(
                self->scene, self->position, velocity_2, BULLET_FIGHTER, 90.0f);
            Scene_AppendBullet(self->scene, bullet_2);
        }
        else if (self->type == ENEMY_FIGHTER_4)
        {
            // Les projectiles partent de bas en haut en balayant l'écran
         Vec2 velocity = Vec2_Set(-9.0, ((int) g_time->currentTime % 6) - 3);
         Bullet* bullet = Bullet_New( self->scene, self->position, velocity, BULLET_FIGHTER, 90.0f);
         Scene_AppendBullet(self->scene, bullet);

        }
        else if (self->type == ENEMY_FIGHTER_5)
        {
            // Le projectile part droit en haut
            Vec2 velocity_1 = Vec2_Set(-5.0, 0);
            Bullet* bullet_1 = Bullet_New(
                self->scene,
                Vec2_Add(Vec2_Set(0,0.4), self->position),
                velocity_1, BULLET_FIGHTER, 90.0f);
            Scene_AppendBullet(self->scene, bullet_1);

            // Le projectile part droit en bas
            Vec2 velocity_2 = Vec2_Set(-5.0, 0);
            Bullet* bullet_2 = Bullet_New(
                self->scene,
                Vec2_Add(Vec2_Set(0, -0.4), self->position),
                velocity_2, BULLET_FIGHTER, 90.0f);
            Scene_AppendBullet(self->scene, bullet_2);
        }
        else if (self->type == ENEMY_FIGHTER_6)
        {
            // le projectile pars et dessine un cercle autour de l'enemi
            if (self->lastTypeofBullet == 0)
            {
                for (int j = 0; j < 45; j++)
                {
                    Vec2 velocity_2 = Vec2_Set(3 * cosf(j), 3 * sinf(j));
                    Bullet* bullet_1 = Bullet_New(
                        self->scene,
                        Vec2_Add(Vec2_Set(-0.1, 0), self->position),
                        velocity_2, BULLET_FIGHTER, 90.0f);
                    Scene_AppendBullet(self->scene, bullet_1);
                }
                self->lastTypeofBullet++;
            }
            else 
            {
                for (float k = 0.5; k < 45; k++)
                {
                    Vec2 velocity_2 = Vec2_Set(3 * cosf(k), 3 * sinf(k));
                    Bullet* bullet_2 = Bullet_New(
                        self->scene,
                        Vec2_Add(Vec2_Set(-0.1, 0), self->position),
                        velocity_2, BULLET_FIGHTER, 90.0f);
                    Scene_AppendBullet(self->scene, bullet_2);
                }
                self->lastTypeofBullet--;
            }
        

            
            
            
        }

        self->lastBulletTime = g_time->currentTime;

        Mix_PlayChannel(-1, self->scene->assets->EnemyBulletSound1, 0);
       }

    /*
    Gère le mouvements des ennemis
    */
    if (self->type == ENEMY_FIGHTER_1 || self->type == ENEMY_FIGHTER_2 || self->type == ENEMY_FIGHTER_5)
    {
        /*
        * Mouvement permettant de rester sur place mais de simuler un petit déplacement.
        */
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
    else if (self->type == ENEMY_FIGHTER_3)
    {
        /*
        * Mouvement de type sinusoidale ( sur l'axe Y).
        */
        float sinPos = sinf(g_time->currentTime + self->randomStartingTickY)*1.5;

        Vec2 velocity = Vec2_Set(
            0,
            sinPos
        );
        self->position = Vec2_Add(
            self->position,
            Vec2_Scale(velocity, Timer_GetDelta(g_time))
        );
    }
    else if (self->type == ENEMY_FIGHTER_4)
    {
        /*
        * Mouvement chelou
        */
        float Posy = sinf(g_time->currentTime + self->randomStartingTickY);
        float Posx = sinf(g_time->currentTime + self->randomStartingTickX)*0.5 ;
        Vec2 velocity = Vec2_Set( Posx, Posy);
        self->position = Vec2_Add( self->position, Vec2_Scale(velocity, Timer_GetDelta(g_time)));
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

void Enemy_Damage(Enemy *self, int damage)
{
    self->remainingLives--;

    if (self->remainingLives == 0) {
        self->state = ENEMY_DEAD;
    }
}
