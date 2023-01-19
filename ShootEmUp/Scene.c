#include "Scene.h"

Scene *Scene_New(SDL_Renderer *renderer)
{
    Scene *self = (Scene *)calloc(1, sizeof(Scene));
    AssertNew(self);

    self->renderer = renderer;

    self->assets = Assets_New(renderer);
    self->camera = Camera_New(LOGICAL_WIDTH, LOGICAL_HEIGHT);
    self->input = Input_New(self);
    self->player = Player_New(self);
    self->waveIdx = 0;
    self->isGameStarted = 0;
    self->menu = Menu_New(self);

    self->hasFirstCollectableBeenSent = false;
    self->timeBetweenCollectables = 5;
    self->lastCollectableTime = g_time->currentTime;
    self->collectablesCount = 0;

    return self;
}

void Scene_Delete(Scene *self)
{
    if (!self) return;

    Assets_Delete(self->assets);
    Camera_Delete(self->camera);
    Input_Delete(self->input);
    Player_Delete(self->player);
    Menu_Delete(self->menu);

    for (int i = 0; i < self->enemyCount; i++)
    {
        Enemy_Delete(self->enemies[i]);
        self->enemies[i] = NULL;
    }
    for (int i = 0; i < self->bulletCount; i++)
    {
        Bullet_Delete(self->bullets[i]);
        self->bullets[i] = NULL;
    }

    free(self);
}

void Scene_UpdateLevel(Scene *self)
{
    if (self->enemyCount > 0)
        return;

    if (self->waveIdx == 0)
    {
        Enemy *enemy_1 = Enemy_New(self, ENEMY_FIGHTER_1, Vec2_Set(14.0f, 6.75f));
        Scene_AppendEnemy(self, enemy_1);

        Enemy* enemy_2 = Enemy_New(self, ENEMY_FIGHTER_1, Vec2_Set(14.0f, 4.5f));
        Scene_AppendEnemy(self, enemy_2);

        Enemy* enemy_3 = Enemy_New(self, ENEMY_FIGHTER_1, Vec2_Set(14.0f, 2.25f));
        Scene_AppendEnemy(self, enemy_3);
        self->waveIdx++;
    }
    else if (self->waveIdx == 1)
    {
        Enemy* enemy_1 = Enemy_New(self, ENEMY_FIGHTER_2, Vec2_Set(14.0f, 5.5f));
        Scene_AppendEnemy(self, enemy_1);

        Enemy* enemy_2 = Enemy_New(self, ENEMY_FIGHTER_2, Vec2_Set(14.0f, 3.5f));
        Scene_AppendEnemy(self, enemy_2);

        Enemy* enemy_3 = Enemy_New(self, ENEMY_FIGHTER_1, Vec2_Set(12.0f, 7.5f));
        Scene_AppendEnemy(self, enemy_3);

        Enemy* enemy_4 = Enemy_New(self, ENEMY_FIGHTER_1, Vec2_Set(12.0f, 2.5f));
        Scene_AppendEnemy(self, enemy_4);

        self->waveIdx++;
    }
    else if (self->waveIdx == 2)
    {
        Enemy* enemy_1 = Enemy_New(self, ENEMY_FIGHTER_3, Vec2_Set(11.5f, 4.5f));
        Scene_AppendEnemy(self, enemy_1);

        Enemy* enemy_2 = Enemy_New(self, ENEMY_FIGHTER_3, Vec2_Set(13.0f, 4.5f));
        Scene_AppendEnemy(self, enemy_2);

        Enemy* enemy_3 = Enemy_New(self, ENEMY_FIGHTER_7, Vec2_Set(14.5f, 4.5f));
        Scene_AppendEnemy(self, enemy_3);

        self->waveIdx++;
    }
    else if (self->waveIdx == 3)
    {
   
        Enemy* enemy_1 = Enemy_New(self, ENEMY_FIGHTER_3, Vec2_Set(13.0f, 4.5f));
        Scene_AppendEnemy(self, enemy_1);

        Enemy* enemy_2 = Enemy_New(self, ENEMY_FIGHTER_2, Vec2_Set(11.5f, 7.5f));
        Scene_AppendEnemy(self, enemy_2);

        Enemy* enemy_3 = Enemy_New(self, ENEMY_FIGHTER_2, Vec2_Set(11.5f, 2.5f));
        Scene_AppendEnemy(self, enemy_3);

        Enemy* enemy_4 = Enemy_New(self, ENEMY_FIGHTER_7, Vec2_Set(14.5f, 6.75f));
        Scene_AppendEnemy(self, enemy_4);

        Enemy* enemy_5 = Enemy_New(self, ENEMY_FIGHTER_1, Vec2_Set(14.5f, 4.5f));
        Scene_AppendEnemy(self, enemy_5);

        Enemy* enemy_6 = Enemy_New(self, ENEMY_FIGHTER_7, Vec2_Set(14.5f, 2.25f));
        Scene_AppendEnemy(self, enemy_6);

        self->waveIdx++;
    }
    else if (self->waveIdx == 4)
    {
        Enemy* enemy_1 = Enemy_New(self, ENEMY_FIGHTER_4, Vec2_Set(13.0f, 4.5f));
        Scene_AppendEnemy(self, enemy_1);

        Enemy* enemy_2 = Enemy_New(self, ENEMY_FIGHTER_1, Vec2_Set(11.5f, 3.5f));
        Scene_AppendEnemy(self, enemy_2);

        Enemy* enemy_3 = Enemy_New(self, ENEMY_FIGHTER_1, Vec2_Set(11.5f, 5.5f));
        Scene_AppendEnemy(self, enemy_3);

        Enemy* enemy_4 = Enemy_New(self, ENEMY_FIGHTER_2, Vec2_Set(14.5f, 6.75f));
        Scene_AppendEnemy(self, enemy_4);

        Enemy* enemy_5 = Enemy_New(self, ENEMY_FIGHTER_2, Vec2_Set(14.5f, 2.25f));
        Scene_AppendEnemy(self, enemy_5);

        self->waveIdx++;
    }
}

bool Scene_Update(Scene *self)
{
    Player *player = self->player;

    // Met à jour le background;
    //self->layer1-

    // Met à jour les entrées utilisateur
    Input_Update(self->input);

    // Mets à jours les éléments seulement quand le menu n'est pas fermé
    if (self->menu->isOpen)
    {
        return self->input->quitPressed;
    }
    // -------------------------------------------------------------------------
    // Met à jour les tirs
    int i = 0;
    while (i < self->bulletCount)
    {
        Bullet *bullet = self->bullets[i];
        bool removed = false;

        Bullet_Update(bullet);

        bool outOfBounds =
            (bullet->position.x < -1.0f) ||
            (bullet->position.x > 17.0f) ||
            (bullet->position.y < -1.0f) ||
            (bullet->position.y > 10.0f);

        if (outOfBounds)
        {
            // Supprime le tir
            Scene_RemoveBullet(self, i);
            removed = true;
            continue;
        }

        if (bullet->fromPlayer)
        {
            // Teste les collisions avec les ennemis
            for (int j = 0; j < self->enemyCount; j++)
            {
                Enemy *enemy = self->enemies[j];
                float dist = Vec2_Distance(bullet->position, enemy->position);
                if (dist < bullet->radius + enemy->radius)
                {
                    // Inflige des dommages à l'ennemi
                    Enemy_Damage(enemy, 1);

                    // Supprime le tir
                    Scene_RemoveBullet(self, i);
                    removed = true;
                    break;
                }
            }
        }
        else
        {
            // Teste la collision avec le joueur
            float dist = Vec2_Distance(bullet->position, self->player->position);
            if (dist < bullet->radius + player->radius)
            {
                // Inflige des dommages au joueur
                Player_Damage(player, 1);

                // Supprime le tir
                Scene_RemoveBullet(self, i);
                removed = true;
            }
        }

        // Passe au prochain tir
        if (removed == false)
        {
            i++;
        }
    }

    // -------------------------------------------------------------------------
    // Met à jour les ennemis

    i = 0;
    while (i < self->enemyCount)
    {
        Enemy* enemy = self->enemies[i];
        bool removed = false;

        Enemy_Update(enemy);

        if (enemy->state == ENEMY_DEAD)
        {
            // Supprime l'ennemi
            Scene_RemoveEnemy(self, i);
            removed = true;
        }

        // Passe au prochain ennemi
        if (removed == false)
        {
            i++;
        }
    }

    // -------------------------------------------------------------------------
    // Met à jour les collectable
    i = 0;
    while (i < self->collectablesCount)
    {
        Collectable* collectable = self->collectables[i];
        bool removed = false;
        
        if (collectable) {
            Collectable_Update(collectable);

            // Regarde si le collectable se trouve en dehors des limites
            bool outOfBounds =
                (collectable->position.x < -1.0f) ||
                (collectable->position.x > 20.0f) ||
                (collectable->position.y < -1.0f) ||
                (collectable->position.y > 10.0f);

            if (outOfBounds)
            {
                // Supprime le collectable
                Scene_RemoveCollectable(self, i);
                removed = true;
                continue;
            }

            // Teste la collision avec le joueur
            float dist = Vec2_Distance(collectable->position, self->player->position);
            if (dist < collectable->radius + player->radius)
            {
                manageCollectable(collectable);
                // Supprime le collectable
                Scene_RemoveCollectable(self, i);
                removed = true;
            }
        }

        // Passe au prochain collectable
        if (removed == false)
        {
            i++;
        }
    }

    // Créé un collectable lorsque le temps entre chaque collectable a été dépassé
    if (g_time->currentTime - self->lastCollectableTime >= self->timeBetweenCollectables)
    {
        createRandomCollectable(self);

        if (!self->hasFirstCollectableBeenSent) {
            self->hasFirstCollectableBeenSent = true;
            //self->timeBetweenCollectables = 10;
        }
    }

    // -------------------------------------------------------------------------
    // Met à jour le joueur

    Player_Update(self->player);

    // -------------------------------------------------------------------------
    // Met à jour le niveau

    Scene_UpdateLevel(self);

    return self->input->quitPressed;
}

void Scene_Render(Scene *self)
{
    // Affichage du fond
    SDL_Renderer *renderer = Scene_GetRenderer(self);
    Assets *assets = Scene_GetAssets(self);
    SDL_RenderCopy(renderer, assets->layers[0], NULL, NULL);
    SDL_RenderCopy(renderer, assets->layers[1], NULL, NULL);
    SDL_RenderCopy(renderer, assets->layers[2], NULL, NULL);

    // On affiche le jeu seulement quand la partie a commencé
    if (self->isGameStarted)
    {
        // Affichage des bullets
        int bulletCount = self->bulletCount;
        for (int i = 0; i < bulletCount; i++)
        {
            Bullet_Render(self->bullets[i]);
        }

        // Affichage des ennemis
        int enemyCount = self->enemyCount;
        for (int i = 0; i < enemyCount; i++)
        {
            Enemy_Render(self->enemies[i]);
        }

        // Affichage des collectables
        int collectablesCount = self->collectablesCount;
        for (int i = 0; i < collectablesCount; i++)
        {
            if (self->collectables[i])
            {
                Collectable_Render(self->collectables[i]);
            }
        }

        // Affichage du joueur
        Player_Render(self->player);

        // Affichage des coeurs
        Heart_Render(self->player);

        // Affichage des bar de powerup
        Collectables_Bar_Render(self->player);
    }

    Menu_Render(self->menu);
}

void Scene_AppendObject(void *object, void **objectArray, int *count, int capacity)
{
    int index = *count;
    if (index >= capacity)
        return;

    if (objectArray[index] != NULL)
    {
        assert(false);
        abort();
    }

    objectArray[index] = object;
    (*count)++;
}

void Scene_AppendEnemy(Scene *self, Enemy *enemy)
{
    Scene_AppendObject(
        enemy,
        (void **)(self->enemies),
        &(self->enemyCount),
        ENEMY_CAPACITY
    );
}

void Scene_AppendBullet(Scene *self, Bullet *bullet)
{
    Scene_AppendObject(
        bullet,
        (void **)(self->bullets),
        &(self->bulletCount),
        BULLET_CAPACITY
    );
}

void Scene_RemoveObject(int index, void **objectArray, int *count)
{
    int lastIndex = *count - 1;
    assert(0 <= index && index < *count);

    if (objectArray[index] == NULL)
    {
        assert(false);
        abort();
    }

    if (index == lastIndex)
    {
        // Supprime le pointeur
        objectArray[index] = NULL;
    }
    else
    {
        // Remplace le pointeur par le dernier du tableau
        objectArray[index] = objectArray[lastIndex];
        objectArray[lastIndex] = NULL;
    }
    (*count)--;
}

void Scene_RemoveEnemy(Scene *self, int index)
{
    Enemy_Delete(self->enemies[index]);
    Scene_RemoveObject(index, (void **)(self->enemies), &(self->enemyCount));
}

void Scene_RemoveBullet(Scene *self, int index)
{
    Bullet_Delete(self->bullets[index]);
    Scene_RemoveObject(index, (void **)(self->bullets), &(self->bulletCount));
}

void Scene_RemoveCollectable(Scene* self, int index)
{
    Collectable_Delete(self->collectables[index]);
    Scene_RemoveObject(index, (void**)(self->collectables), &(self->collectablesCount));
}