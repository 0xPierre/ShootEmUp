#pragma once
#pragma once
#include "Settings.h"
#include "Math.h"

typedef struct Scene_s Scene;

/// @brief Enumération des types possibles pour un collectable.
typedef enum CollectableType_e
{
    /// @brief Ennemi simple.
    COLLECTABLE_HEALTH,
    COLLECTABLE_GUN_UPGRADE_1,
    COLLECTABLE_GUN_UPGRADE_2,
    COLLECTABLE_SPEED
} CollectableType;

/// @brief Structure représentant le menu du jeu.
typedef struct Collectable_s
{
    /// @brief Scène associée.
    Scene* scene;

   /// @brief Type de collectable
   CollectableType* type;

    /// @brief Texture utilisée pour le rendu.
    SDL_Texture* texture;

    /// @brief Position du collectable exprimée dans le référentiel monde.
    Vec2 position;

    /// @brief Vitesse du collectable exprimée dans le référentiel monde.
    Vec2 velocity;

    /// @brief Largeur de la texture du collectable
    /// exprimée dans le référentiel monde.
    float worldW;

    /// @brief Hauteur de la texture du collectable
    /// exprimée dans le référentiel monde.
    float worldH;

    /// @brief Rayon du collectable exprimé dans le référentiel monde.
    /// Il est utilisé dans le moteur physique pour tester les collisions.
    float radius;

    /// @brief Angle de rotation du la texture pour le rendu.
    float angle;
} Collectable;

/// @brief Créé le menu
/// @param scene la scene du monde
/// @return Le menu créé
Collectable* Collectable_New(Scene* scene, int type, Vec2 position);

/// @brief Détruit la scène principale.
/// @param self le menu
void Collectable_Delete(Collectable* self);

/// @brief Met à jour le menu
/// Cette fonction est appelée à chaque tour de la boucle de rendu.
/// @param self le menu
void Collectable_Update(Collectable* self);

/// @brief Dessine la scène dans le moteur de rendu.
/// @param self le menu
void Collectable_Render(Collectable* self);

/// @brief Créé un collectable positionné aléatoirement
void createRandomCollectable(Scene* scene);

/// @brief Gère le type de collectable lorsque il est pris par l'utilisateur
void manageCollectable(Collectable* collectable);