#include "Enemy.h"
#include "Common.h"
#include "Scene.h"
#include "Math.h"

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
    Permet de g�n�rer un mouvement qui ne ressemble pas aux autres objets.
    */
    self->randomStartingTickX = (rand() % 1000);
    self->randomStartingTickY = (rand() % 1000);

    Assets *assets = Scene_GetAssets(self->scene);
    switch (type)
    {
    case ENEMY_FIGHTER_1:
        self->worldW = 120 * PIX_TO_WORLD;
        self->worldH = 120 * PIX_TO_WORLD;
        self->radius = 0.4f;
        self->texture = assets->fighter1;
        self->remainingLives = 2; 
        self->timeBetweenBullets = 1.5;
        self->IsShieldActivated = true;
        self->shieldtime = 1;
        self->shieldW = 60 * PIX_TO_WORLD;
        self->shieldH = 60 * PIX_TO_WORLD;
        self->angleShoot = 90.0f;
        break;

    case ENEMY_FIGHTER_2:
        self->worldW = 120 * PIX_TO_WORLD;
        self->worldH = 120 * PIX_TO_WORLD;
        self->radius = 0.4f;
        self->texture = assets->fighter2;
        self->remainingLives = 2;
        self->timeBetweenBullets = 1.5;
        self->IsShieldActivated = true;
        self->shieldtime = 1;
        self->shieldW = 60 * PIX_TO_WORLD;
        self->shieldH = 60 * PIX_TO_WORLD; 
        self->angleShoot = 90.0f;
        break;

    case ENEMY_FIGHTER_3:
        self->worldW = 120 * PIX_TO_WORLD;
        self->worldH = 120 * PIX_TO_WORLD;
        self->radius = 0.4f;
        self->texture = assets->fighter3;
        self->remainingLives = 2;
        self->timeBetweenBullets = 1;
        self->IsShieldActivated = true;
        self->shieldtime = 1;
        self->shieldW = 60 * PIX_TO_WORLD;
        self->shieldH = 60 * PIX_TO_WORLD;
        self->angleShoot = 90.0f;
        break;

    case ENEMY_FIGHTER_4:
        self->worldW = 240 * PIX_TO_WORLD;
        self->worldH = 240 * PIX_TO_WORLD;
        self->radius = 1.2f;
        self->texture = assets->fighter4;
        self->remainingLives = 10;
        self->timeBetweenBullets = 0.15f;
        self->IsShieldActivated = true;
        self->shieldtime = 12;
        self->shieldW = 160 * PIX_TO_WORLD;
        self->shieldH = 160 * PIX_TO_WORLD;
        self->bulletnum = 0;
        self->angleShoot = 90.0f;
        break;

     case ENEMY_FIGHTER_5:
        self->worldW = 120 * PIX_TO_WORLD;
        self->worldH = 120 * PIX_TO_WORLD;
        self->radius = 0.4f;
        self->texture = assets->fighter5;
        self->remainingLives = 3;
        self->timeBetweenBullets = 0.5;
        self->IsShieldActivated = true;
        self->shieldtime = 3;
        self->shieldW = 60 * PIX_TO_WORLD;
        self->shieldH = 60 * PIX_TO_WORLD;
        self->angleShoot = 90.0f;
        break;

     case ENEMY_FIGHTER_6:
         self->worldW = 240 * PIX_TO_WORLD;
         self->worldH = 240 * PIX_TO_WORLD;
         self->radius = 1.2f;
         self->texture = assets->fighter6;
         self->remainingLives = 15;
         self->timeBetweenBullets = 1.0;
        self-> lastTypeofBullet = 0;
        self->shield = 5;
        self->shieldtime = 1;
        self->IsShieldActivated = false;
        self->shieldW = 220 * PIX_TO_WORLD;
        self->shieldH = 220 * PIX_TO_WORLD;
        self->angleShoot = 90.0f;
         break;

     case ENEMY_FIGHTER_7:
         self->worldW = 120 * PIX_TO_WORLD;
         self->worldH = 120 * PIX_TO_WORLD;
         self->radius = 0.4f;
         self->texture = assets->fighter7;
         self->remainingLives = 2;
         self->timeBetweenBullets = 1.0;
         self->lastTypeofBullet = 0;
         self->IsShieldActivated = true;
         self->shieldtime = 1;
         self->shieldW = 60 * PIX_TO_WORLD;
         self->shieldH = 60 * PIX_TO_WORLD;
         self->angleShoot = 0.0f;
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
    //Cr�� un projectil toutes les "timeBetweenBullets"
    
    if ((g_time->currentTime - self->lastBulletTime) >= self->timeBetweenBullets) {
        /*
        * G�re les projectiles des ennemis
        */
        //desactive le shield d'arriver
        if (self->shieldtime == 0 )
        {
            printf("shield off\n");
            self->IsShieldActivated = false;
         
        }
        else
        {
            self->shieldtime--;
            if (self->type != ENEMY_FIGHTER_6) return;
        }
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
            
          // Les projectiles partent de bas en haut en balayant l'�cran
         Vec2 velocity = Vec2_Set(-5.0, (float)((int) g_time->currentTime % 6) - 3);
         Bullet* bullet = Bullet_New( self->scene, self->position, velocity, BULLET_FIGHTER2, 90.0f);
         Scene_AppendBullet(self->scene, bullet);
         
             
         if (self->lastTypeofBullet ==0)
         {
             Vec2 velocity_1 = Vec2_Set(-6, (self->bulletnum % 12) - 6);
             Bullet* bullet_1 = Bullet_New(self->scene, self->position, velocity_1, BULLET_FIGHTER, 90.0f);
             Scene_AppendBullet(self->scene, bullet_1);
             self->bulletnum++;
             self->lastTypeofBullet++;
         }
         
         if (self->lastTypeofBullet == 1)
         {
             Vec2 velocity_2 = Vec2_Set(-6, -((self->bulletnum % 12) - 6));
             Bullet* bullet_2 = Bullet_New(self->scene, self->position, velocity_2, BULLET_FIGHTER, 90.0f);
             Scene_AppendBullet(self->scene, bullet_2);
             self->bulletnum++;
             self->lastTypeofBullet--;
         }


        }
        else if (self->type == ENEMY_FIGHTER_5)
        {
            // Le projectile part droit en haut
            Vec2 velocity_1 = Vec2_Set(-5.0, 0);
            Bullet* bullet_1 = Bullet_New(
                self->scene,
                Vec2_Add(Vec2_Set(0,0.4f), self->position),
                velocity_1, BULLET_FIGHTER, 90.0f);
            Scene_AppendBullet(self->scene, bullet_1);

            // Le projectile part droit en bas
            Vec2 velocity_2 = Vec2_Set(-5.0, 0);
            Bullet* bullet_2 = Bullet_New(
                self->scene,
                Vec2_Add(Vec2_Set(0, -0.4f), self->position),
                velocity_2, BULLET_FIGHTER, 90.0f);
            Scene_AppendBullet(self->scene, bullet_2);
        }
        else if (self->type == ENEMY_FIGHTER_6)
        {
            // le projectile pars et dessine un cercle autour de l'enemi
            if (self->lastTypeofBullet == 0)
            {
                for (float j = 0; j < 45; j++)
                {
                    Vec2 velocity_2 = Vec2_Set(3 * cosf(j), 3 * sinf(j));
                    Bullet* bullet_1 = Bullet_New(
                        self->scene,
                        Vec2_Add(Vec2_Set(-0.1f, 0), self->position),
                        velocity_2, BULLET_FIGHTER, 90.0f);
                    Scene_AppendBullet(self->scene, bullet_1);
                }
                self->lastTypeofBullet++;
                self->shield++;
            }
            else 
            {
                for (float k = 0.5; k < 45; k++)
                {
                    Vec2 velocity_2 = Vec2_Set(3 * cosf(k), 3 * sinf(k));
                    Bullet* bullet_2 = Bullet_New(
                        self->scene,
                        Vec2_Add(Vec2_Set(-0.f, 0), self->position),
                        velocity_2, BULLET_FIGHTER, 90.0f);
                    Scene_AppendBullet(self->scene, bullet_2);
                }
                for (int i = 0; i < 12; i++) 
                {
                    Vec2 velocity_3 = Vec2_Set(-6, sin((self->bulletnum) ));
                    Bullet* bullet_3 = Bullet_New(self->scene, self->position, velocity_3, BULLET_FIGHTER3, 90.0f);
                    Scene_AppendBullet(self->scene, bullet_3);
                    self->bulletnum++;

                }
                Vec2 velocity_3= Vec2_Set(-6, sin((self->bulletnum) - 6));
                Bullet* bullet_3= Bullet_New(self->scene, self->position, velocity_3, BULLET_FIGHTER3, 90.0f);
                Scene_AppendBullet(self->scene, bullet_3);
                self->bulletnum++;
                self->lastTypeofBullet++;
                self->lastTypeofBullet--;
                self->shield++;
            }
            // le shield s'active tous les 10 tirs et reste activ� 3 tirs. 
            if (self->shield == 10)
            {
                self->shield = 0;
                self->IsShieldActivated = true;
                printf("shield on\n");
                self->shieldtime = 5;
                
            }
            if (self->shieldtime > 0) self->shieldtime--;
            if (self->shieldtime == 0)
            {
                printf("shield off\n");
                self->IsShieldActivated = false;
                
            }
            
         
        }
        else if (self->type == ENEMY_FIGHTER_7)
        {
            // Les projectiles partent de bas en haut en balayant l'�cran

            Vec2 velocity = Vec2_Set(Vec2_Sub(self->scene->player->position, self->position).x, Vec2_Sub(self->scene->player->position, self->position).y);
            Bullet* bullet = Bullet_New(self->scene, self->position, velocity, BULLET_FIGHTER, 90.0f);
            Scene_AppendBullet(self->scene, bullet);


        }
        self->lastBulletTime = g_time->currentTime;

        Mix_PlayChannel(-1, self->scene->assets->EnemyBulletSound1, 0);
       }

    /*
    G�re le mouvements des ennemis
    */
    if (self->type == ENEMY_FIGHTER_1 || self->type == ENEMY_FIGHTER_2 || self->type == ENEMY_FIGHTER_5)
    {
        /*
        * Mouvement permettant de rester sur place mais de simuler un petit d�placement.
        */
        // Calcul de la v�locit� en utilisant cos et sin pour faire bouger l'ennemi.
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
        float sinPos = sinf(g_time->currentTime + self->randomStartingTickY) * 1.5f;

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
        float Posx = sinf(g_time->currentTime + self->randomStartingTickX) * 0.5f;
        Vec2 velocity = Vec2_Set( Posx, Posy);
        self->position = Vec2_Add( self->position, Vec2_Scale(velocity, Timer_GetDelta(g_time)));
    }
    else if (self->type == ENEMY_FIGHTER_7)
    {
        double distx = Vec2_Sub(self->scene->player->position, self->position).x;
        double disty = Vec2_Sub(self->scene->player->position, self->position).y;
        double angle = 90 - atan(disty / distx) * (180 / M_PI);
        self->angleShoot = angle;

    }
}

void Enemy_Render(Enemy *self)
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
        renderer, self->texture, NULL, &dst, self->angleShoot, NULL, 0);

    //Le shield des enemis
    SDL_FRect dst_shield = { 0 };
    // Changez 48 par une autre valeur pour grossir ou r�duire l'objet
    dst_shield.h = self->shieldW * scale;
    dst_shield.w = self->shieldH * scale;
    Camera_WorldToView(camera, self->position, &dst_shield.x, &dst_shield.y);
    // Le point de r�f�rence est le centre de l'objet
    dst_shield.x -= 0.50f * dst_shield.w;
    dst_shield.y -= 0.50f  * dst_shield.h;
    // On affiche en position dst (unit�s en pixels)
    if (self->IsShieldActivated == true)
    {
        SDL_RenderCopyExF(
            renderer, assets->ShieldEnnemy, NULL, &dst_shield, 90.0f, NULL, 0);    
    }
    
    
}

void Enemy_Damage(Enemy *self, int damage)
{
    if (self->IsShieldActivated == false)
    {
        self->remainingLives--;

        if (self->remainingLives == 0) {
            self->state = ENEMY_DEAD;
        }
    }
    
}
