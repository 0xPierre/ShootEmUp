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

    self->defaultGameOverPosY = 200;
    self->gameOverPosY = self->defaultGameOverPosY;

    self->defaultWinPosY = 200.f;
    self->winPosY = self->defaultWinPosY;

    self->layer1PosX = 0;
    self->layer2PosX = 0;

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
    for (int i = 0; i < self->collectablesCount; i++)
    {
        Collectable_Delete(self->collectables[i]);
        self->collectables[i] = NULL;
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
    // Si la vague est 5 alors c'est win
    else if (self->waveIdx == 5)
    {
        self->isGameWin = true;
        return;
    }
    else if (self->waveIdx == 6)
    {
        Enemy* enemy_1 = Enemy_New(self, ENEMY_FIGHTER_5, Vec2_Set(13.0f, 5.0f));
        Scene_AppendEnemy(self, enemy_1);

        Enemy* enemy_2 = Enemy_New(self, ENEMY_FIGHTER_5, Vec2_Set(13.0f, 4.0f));
        Scene_AppendEnemy(self, enemy_2);

        Enemy* enemy_3 = Enemy_New(self, ENEMY_FIGHTER_7, Vec2_Set(14.5f, 2.25f));
        Scene_AppendEnemy(self, enemy_3);

        Enemy* enemy_4 = Enemy_New(self, ENEMY_FIGHTER_7, Vec2_Set(14.5f, 6.75f));
        Scene_AppendEnemy(self, enemy_4);

        self->waveIdx++;
    }
    else if (self->waveIdx == 7)
    {
        Enemy* enemy_1 = Enemy_New(self, ENEMY_FIGHTER_3, Vec2_Set(13.0f, 4.5f));
        Scene_AppendEnemy(self, enemy_1);

        Enemy* enemy_2 = Enemy_New(self, ENEMY_FIGHTER_3, Vec2_Set(11.5f, 4.5f));
        Scene_AppendEnemy(self, enemy_2);

        Enemy* enemy_3 = Enemy_New(self, ENEMY_FIGHTER_5, Vec2_Set(14.5f, 4.5f));
        Scene_AppendEnemy(self, enemy_3);

        Enemy* enemy_4 = Enemy_New(self, ENEMY_FIGHTER_7, Vec2_Set(14.5f, 6.75f));
        Scene_AppendEnemy(self, enemy_4);

        Enemy* enemy_5 = Enemy_New(self, ENEMY_FIGHTER_7, Vec2_Set(14.5f, 2.25f));
        Scene_AppendEnemy(self, enemy_5);

        self->waveIdx++;
    }
    else if (self->waveIdx == 8)
    {
        Enemy* enemy_1 = Enemy_New(self, ENEMY_FIGHTER_1, Vec2_Set(11.5f, 3.0f));
        Scene_AppendEnemy(self, enemy_1);

        Enemy* enemy_2 = Enemy_New(self, ENEMY_FIGHTER_1, Vec2_Set(11.5f, 6.0f));
        Scene_AppendEnemy(self, enemy_2);

        Enemy* enemy_3 = Enemy_New(self, ENEMY_FIGHTER_2, Vec2_Set(14.5f, 4.5f));
        Scene_AppendEnemy(self, enemy_3);

        Enemy* enemy_4 = Enemy_New(self, ENEMY_FIGHTER_7, Vec2_Set(14.5f, 6.75f));
        Scene_AppendEnemy(self, enemy_4);

        Enemy* enemy_5 = Enemy_New(self, ENEMY_FIGHTER_7, Vec2_Set(14.5f, 2.25f));
        Scene_AppendEnemy(self, enemy_5);

        Enemy* enemy_6 = Enemy_New(self, ENEMY_FIGHTER_3, Vec2_Set(13.0f, 4.5f));
        Scene_AppendEnemy(self, enemy_6);

        self->waveIdx++;
    }
    else if (self->waveIdx == 9)
    {
        Enemy* enemy_1 = Enemy_New(self, ENEMY_FIGHTER_5, Vec2_Set(11.5f, 3.0f));
        Scene_AppendEnemy(self, enemy_1);

        Enemy* enemy_2 = Enemy_New(self, ENEMY_FIGHTER_5, Vec2_Set(11.5f, 6.0f));
        Scene_AppendEnemy(self, enemy_2);

        Enemy* enemy_3 = Enemy_New(self, ENEMY_FIGHTER_2, Vec2_Set(14.5f, 5.5f));
        Scene_AppendEnemy(self, enemy_3);

        Enemy* enemy_4 = Enemy_New(self, ENEMY_FIGHTER_7, Vec2_Set(14.5f, 6.75f));
        Scene_AppendEnemy(self, enemy_4);

        Enemy* enemy_5 = Enemy_New(self, ENEMY_FIGHTER_7, Vec2_Set(14.5f, 2.25f));
        Scene_AppendEnemy(self, enemy_5);

        Enemy* enemy_6 = Enemy_New(self, ENEMY_FIGHTER_3, Vec2_Set(13.0f, 4.5f));
        Scene_AppendEnemy(self, enemy_6);

        Enemy* enemy_7 = Enemy_New(self, ENEMY_FIGHTER_2, Vec2_Set(14.5f, 3.5f));
        Scene_AppendEnemy(self, enemy_7);

        self->waveIdx++;
    }
    else if (self->waveIdx == 10)
    {
        Enemy* enemy_1 = Enemy_New(self, ENEMY_FIGHTER_6, Vec2_Set(13.0f, 4.5f));
        Scene_AppendEnemy(self, enemy_1);

        Enemy* enemy_4 = Enemy_New(self, ENEMY_FIGHTER_7, Vec2_Set(14.5f, 6.75f));
        Scene_AppendEnemy(self, enemy_4);

        Enemy* enemy_5 = Enemy_New(self, ENEMY_FIGHTER_7, Vec2_Set(14.5f, 2.25f));
        Scene_AppendEnemy(self, enemy_5);

        self->waveIdx++;
    }
    // Si la vague est 11 alors c'est win
    else if (self->waveIdx == 11)
    {
        self->isGameWin = true;
        return;
    }
}

void startSceneAtLevel(Scene* self, Levels level)
{
    Assets* assets = Scene_GetAssets(self);
    // On supprime les anciennes instances
    Player_Delete(self->player);

    for (int i = 0; i < self->enemyCount; i++)
    {
        Scene_RemoveEnemy(self,  i);
        self->enemies[i] = NULL;
    }
    self->enemyCount = 0;

    for (int i = 0; i < self->bulletCount; i++)
    {
        Scene_RemoveBullet(self, i);
        self->bullets[i] = NULL;
    }
    self->bulletCount = 0;

    for (int i = 0; i < self->collectablesCount; i++)
    {
        Scene_RemoveCollectable(self, i);
        self->collectables[i] = NULL;
    }
    self->collectablesCount = 0;

    // On remets les position/vie/... par défault
    self->input = Input_New(self);
    self->player = Player_New(self);

    self->hasFirstCollectableBeenSent = false;
    self->timeBetweenCollectables = 5;
    self->lastCollectableTime = g_time->currentTime;
    self->collectablesCount = 0;
    self->gameOverPosY = self->defaultGameOverPosY;
    self->isGameWin = false;

    self->winPosY = self->defaultWinPosY;

    switch (level)
    {
    case LEVEL_1:
        self->waveIdx = 0;
        break;
    case LEVEL_2:
        self->waveIdx = 6;
        break;
    }
    
    self->menu->isOpen = false;
    self->isGameStarted = true;
}

bool Scene_Update(Scene *self)
{
    Player *player = self->player;

    // Met à jour les entrées utilisateur
    Input_Update(self->input);

    // Mets à jours les éléments seulement quand le menu n'est pas fermé et que le joueur n'est pas mort
    if (self->menu->isOpen || self->player->state == PLAYER_DYING || self->player->state == PLAYER_DEAD)
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
    SDL_Renderer *renderer = Scene_GetRenderer(self);
    Assets *assets = Scene_GetAssets(self);

    // Affichage du fond
    BackGroundLayers_Render(self);

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

    // Affichage du GameOver
    if (self->player->state == PLAYER_DYING || self->player->state == PLAYER_DEAD && !self->isGameWin)
        GameOver(self);

    // Affichage du Win
    if (self->isGameWin)
    {
        Win(self);
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
    Scene_RemoveObject(index, (void **)(self->collectables), &(self->collectablesCount));
}

void BackGroundLayers_Render(Scene* self)
{

    SDL_Renderer* renderer = Scene_GetRenderer(self);
    Assets* assets = Scene_GetAssets(self);
    // Vérifie que le menu n'est pas ouvert. Pour que le fond s'anime seulement quand le jeu est joué
    if (!self->menu->isOpen && self->player->state != PLAYER_DEAD) {
        // On récupère la position du layer 1 par rapport au temps
        self->layer1PosX = (self->layer1PosX + Timer_GetDelta(g_time) * 60);
        if (self->layer1PosX >= 1280)
            self->layer1PosX = 0;

        // On récupère la position du layer 2 par rapport au temps
        self->layer2PosX = (self->layer2PosX + Timer_GetDelta(g_time) * 120);
        if (self->layer2PosX >= 1280) {
            self->layer2PosX = 0;
        }
    }
    SDL_Rect layer1 = { 0 };
    // négatif car on décale vers la gauche
    layer1.x = -(int)self->layer1PosX;
    layer1.y = 0;
    // Taille du layer
    layer1.w = 2560;
    layer1.h = 720;

    SDL_Rect layer2 = { 0 };
    // négatif car on décale vers la gauche
    layer2.x = -(int)self->layer2PosX;
    layer2.y = 0;
    layer2.w = 2560;
    layer2.h = 640;

    SDL_RenderCopy(renderer, assets->layer1, NULL, &layer1);
    SDL_RenderCopy(renderer, assets->layer2, NULL, &layer2);
}

void renderRetryMenu(Scene* self, SDL_Rect dst)
{
    Input* input = self->input;
    Menu* menu = self->menu;
    /*
    * Choix du menu avec les touches où à la manette
    */
    if (input->vAxis > 0)
    {
        if (menu->menuKeyIndex > 0 && input->isMenuKeyBLocked == false)
        {
            menu->menuKeyIndex--;
        }
        input->isMenuKeyBLocked = true;
    }
    else if (input->vAxis < 0)
    {
        if (menu->menuKeyIndex < 1 && input->isMenuKeyBLocked == false)
            menu->menuKeyIndex++;
        input->isMenuKeyBLocked = true;
    }

    /*
    * Affichage du bouton Play again
    */
    int MenuPlayAgainWidth = 320;
    int MenuPlayAgainHeight = 84;

    menu->MenuPlayAgain.x = WINDOW_WIDTH / 2 - 140;
    menu->MenuPlayAgain.y = dst.h - 50;
    menu->MenuPlayAgain.w = MenuPlayAgainWidth;
    menu->MenuPlayAgain.h = MenuPlayAgainHeight;
    SDL_RenderCopy(self->renderer, self->assets->MenuPlayAgain, NULL, &menu->MenuPlayAgain);

    /*
    * Affichage du bouton Quitter
    */
    int MenuQuitWidth = 287;
    int MenuQuitHeight = 150;

    menu->MenuQuit.x = WINDOW_WIDTH / 2 - MenuQuitWidth / 2 - 10;
    menu->MenuQuit.y = menu->MenuPlayAgain.y + menu->MenuPlayAgain.h + 20;
    menu->MenuQuit.w = MenuQuitWidth;
    menu->MenuQuit.h = MenuQuitHeight;
    SDL_RenderCopy(self->renderer, self->assets->MenuQuit, NULL, &menu->MenuQuit);

    /*
    * Affichage du sélecteur
    */
    int MenuSelectorWidth = 40;
    int MenuSelectorHeight = 48;

    menu->MenuSelector.w = MenuSelectorWidth;
    menu->MenuSelector.h = MenuSelectorHeight;

    if (menu->menuKeyIndex == 0)
    {

        menu->MenuSelector.x = menu->MenuPlayAgain.x - 80;
        menu->MenuSelector.y = menu->MenuPlayAgain.y + 15;

        if (input->shootPressed)
        {
            MenuClickOnGameOverRestart(menu);
        }
    }
    else {
        menu->MenuSelector.x = menu->MenuQuit.x - 65;
        menu->MenuSelector.y = menu->MenuQuit.y + 35;

        if (input->shootPressed)
        {
            MenuClickOnQuit(menu);
        }
    }

    SDL_RenderCopyEx(self->renderer, self->assets->MenuSelector, NULL, &menu->MenuSelector, 0, NULL, 0);
}

void GameOver(Scene* self)
{
    SDL_Renderer* renderer = Scene_GetRenderer(self);
    Assets* assets = Scene_GetAssets(self);
    SDL_Rect gameOver = { 0 };
    // Taille du GameOver
    gameOver.w = 800;
    gameOver.h = 475;

    gameOver.x = WINDOW_WIDTH / 2 - gameOver.w / 2;


    // Si le joueur n'est pas mort ( il est mort mais il y a une petite animation ).
    if (self->player->state != PLAYER_DEAD)
    {
        self->gameOverPosY = self->gameOverPosY - Timer_GetDelta(g_time) * 400.f;

        if ((int)self->gameOverPosY > 0)
            gameOver.y = (int)self->gameOverPosY;
        else
            self->player->state = PLAYER_DEAD;
    }
    else {
        renderRetryMenu(self, gameOver);
    }


    SDL_RenderCopy(renderer, assets->GameOver, NULL, &gameOver);
}


void Win(Scene* self)
{
    SDL_Renderer* renderer = Scene_GetRenderer(self);
    Assets* assets = Scene_GetAssets(self);
    SDL_Rect winRect = { 0 };
    // Taille du GameOver
    winRect.w = 612;
    winRect.h = 344;

    winRect.x = WINDOW_WIDTH / 2 - winRect.w / 2;
    
    // Pour me simplifier la tâche ( je le fais bcp ça depuis que j'ai passé les 1h du matin ce vendredi ). Lorsque le player gagne il est passé en mort comment ça je peux réutiliser mon code.
    if (self->player->state != PLAYER_DEAD)
    {
        self->winPosY = self->winPosY - Timer_GetDelta(g_time) * 400.f;

        if ((int)self->winPosY > 0)
            winRect.y = (int)self->winPosY;
        else
            self->player->state = PLAYER_DEAD;
    }
    else {
        renderRetryMenu(self, winRect);
    }

    SDL_RenderCopy(renderer, assets->Win, NULL, &winRect);
}