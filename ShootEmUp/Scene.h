#pragma once

#include "Settings.h"
#include "Common.h"

#include "Assets.h"
#include "Camera.h"
#include "Input.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "Menu.h"
#include "Collectable.h"

// Nombre maximal d'ennemis actifs dans un niveau.
#define ENEMY_CAPACITY 32

// Nombre maximal de projectiles actifs dans un niveau.
#define BULLET_CAPACITY 256

#define COLLECTABLE_CAPACITY 50

typedef enum Levels_s
{
    LEVEL_1,
    LEVEL_2
} Levels;

/// @brief Structure repr�sentant la sc�ne principale du jeu (niveau).
typedef struct Scene_s
{
    /// @brief Moteur de rendu.
    SDL_Renderer *renderer;

    /// @brief Assets de la sc�ne (textures, musiques, sons...)
    Assets *assets;

    /// @brief Cam�ra par laquelle est vue la sc�ne.
    Camera *camera;

    /// @brief Entr�e utilisateur.
    Input *input;

    /// @brief Joueur principal.
    Player *player;

    /// @brief Tableau contenant les ennemis courrants.
    Enemy *enemies[ENEMY_CAPACITY];

    /// @brief Nombre d'ennemis courrants.
    int enemyCount;

    /// @brief Tableau contenant les projectiles courrants.
    Bullet *bullets[BULLET_CAPACITY];

    /// @brief Nombre de projectiles courrants.
    int bulletCount;

    /// @brief Indice de la vague d'ennemis courrante.
    /// Utilis� pour impl�menter un niveau complet.
    int waveIdx;
    /// @brief Permet de savoir si il a fait une vague avant
    int oldWaveIdx;

    /// @brief Permet de savoir si le joueur �tait en jeu
    /// Utilis� pour savoir si afficher Jouer ou Reprendre
    int isGameStarted;

    /// @brief Permet de savoir si le joueur a gagn�
    bool isGameWin;
    
    /// @brief Menu principal
    Menu* menu;

    /// @brief Liste des collectables
    Collectable* collectables[COLLECTABLE_CAPACITY];

    /// @brief Nombre de collectables
    int collectablesCount;
    
    /// @brief Temps depuis le dernier collectable
    float lastCollectableTime;
    
    /// @brief Temps entre chaque collectables
    float timeBetweenCollectables;

    /// @brief Pose pas dquestion
    bool hasFirstCollectableBeenSent;

    /// @brief Position X des couches du bg
    float layer1PosX;
    float layer2PosX;

    /// @brief Position Y du GameOver label permettant son animation vers Y = 0
    float gameOverPosY;
    /// @brief Position par d�fault Y du GameOver label
    float defaultGameOverPosY;

    /// @brief Position Y du GameOver label permettant son animation vers Y = 0
    float winPosY;
    /// @brief Position par d�fault Y du GameOver label
    float defaultWinPosY;

} Scene;

/// @brief Cr�e la sc�ne principale du jeu.
/// @param renderer moteur de rendu.
/// @return La sc�ne cr��e.
Scene *Scene_New(SDL_Renderer *renderer);

/// @brief D�truit la sc�ne principale.
/// @param self la sc�ne.
void Scene_Delete(Scene *self);

/// @brief Met � jour la sc�ne.
/// Cette fonction est appel�e � chaque tour de la boucle de rendu.
/// @param self la sc�ne.
/// @return true s'il faut quitter la boucle de rendu, false sinon.
bool Scene_Update(Scene *self);

/// @brief Dessine la sc�ne dans le moteur de rendu.
/// @param self la sc�ne.
void Scene_Render(Scene *self);

/// @brief Ajoute un nouveau projectile � la sc�ne.
/// @param self la sc�ne.
/// @param bullet le projectile � ajouter (correctement initialis�).
void Scene_AppendBullet(Scene *self, Bullet *bullet);

/// @brief Supprime un projectile de la sc�ne.
/// @param self la sc�ne.
/// @param index l'indice du projectile � supprimer dans le tableau self->bullets.
void Scene_RemoveBullet(Scene *self, int index);

/// @brief Ajoute un nouvel ennemi � la sc�ne.
/// @param self la sc�ne.
/// @param enemy l'ennemi � ajouter (correctement initialis�).
void Scene_AppendEnemy(Scene *self, Enemy *enemy);

/// @brief Supprime un ennemi de la sc�ne.
/// @param self la sc�ne.
/// @param index l'indice du l'ennemi � supprimer dans le tableau self->enemies.
void Scene_RemoveEnemy(Scene *self, int index);

/// @brief Supprime un collectable de la sc�ne.
/// @param self la sc�ne.
/// @param index l'indice du collectable � supprimer dans le tableau self->collectables.
void Scene_RemoveCollectable(Scene* self, int index);

/// @brief Affiche les layers � l'�cran.
/// @param self la sc�ne.
void BackGroundLayers_Render(Scene* self);

/// @brief D�marre un Level en r�initialisant tout.
/// @param self la sc�ne,
/// @param level le niveau choisit pour d�marrer
void startSceneAtLevel(Scene* self, Levels level);

/// @brief G�re le Game Over d'un niveau.
/// @param self la sc�ne.
void GameOver(Scene* self);

/// @brief G�re l'�cran de Win d'un niveau
/// @param self la sc�ne
void Win(Scene* self);

/// @brief Renvoie le moteur de rendu de la sc�ne.
/// @param self la sc�ne.
/// @return Le moteur de rendu de la sc�ne.
INLINE SDL_Renderer *Scene_GetRenderer(Scene *self)
{
    return self->renderer;
}

/// @brief Renvoie les assets de la sc�ne.
/// @param self la sc�ne.
/// @return Les assets de la sc�ne.
INLINE Assets *Scene_GetAssets(Scene *self)
{
    return self->assets;
}

/// @brief Renvoie la cam�ra de la sc�ne.
/// @param self la sc�ne.
/// @return La cam�ra de la sc�ne.
INLINE Camera *Scene_GetCamera(Scene *self)
{
    return self->camera;
}

/// @brief Renvoie les entr�e utilisateur de la sc�ne.
/// @param self la sc�ne.
/// @return Les entr�e utilisateur de la sc�ne.
INLINE Input *Scene_GetInput(Scene *self)
{
    return self->input;
}
