#pragma once
#pragma once
#include "Settings.h"
#include "Math.h"

typedef struct Scene_s Scene;

/// @brief Enum�ration des types possibles pour un collectable.
typedef enum CollectableType_e
{
    /// @brief Ennemi simple.
    COLLECTABLE_HEALTH,
    COLLECTABLE_GUN_UPGRADE_1,
    COLLECTABLE_GUN_UPGRADE_2,
    COLLECTABLE_SPEED
} CollectableType;

/// @brief Structure repr�sentant le menu du jeu.
typedef struct Collectable_s
{
    /// @brief Sc�ne associ�e.
    Scene* scene;

   /// @brief Type de collectable
   CollectableType* type;

    /// @brief Texture utilis�e pour le rendu.
    SDL_Texture* texture;

    /// @brief Position du collectable exprim�e dans le r�f�rentiel monde.
    Vec2 position;

    /// @brief Vitesse du collectable exprim�e dans le r�f�rentiel monde.
    Vec2 velocity;

    /// @brief Largeur de la texture du collectable
    /// exprim�e dans le r�f�rentiel monde.
    float worldW;

    /// @brief Hauteur de la texture du collectable
    /// exprim�e dans le r�f�rentiel monde.
    float worldH;

    /// @brief Rayon du collectable exprim� dans le r�f�rentiel monde.
    /// Il est utilis� dans le moteur physique pour tester les collisions.
    float radius;

    /// @brief Angle de rotation du la texture pour le rendu.
    float angle;
} Collectable;

/// @brief Cr�� le menu
/// @param scene la scene du monde
/// @return Le menu cr��
Collectable* Collectable_New(Scene* scene, int type, Vec2 position);

/// @brief D�truit la sc�ne principale.
/// @param self le menu
void Collectable_Delete(Collectable* self);

/// @brief Met � jour le menu
/// Cette fonction est appel�e � chaque tour de la boucle de rendu.
/// @param self le menu
void Collectable_Update(Collectable* self);

/// @brief Dessine la sc�ne dans le moteur de rendu.
/// @param self le menu
void Collectable_Render(Collectable* self);

/// @brief Cr�� un collectable positionn� al�atoirement
void createRandomCollectable(Scene* scene);

/// @brief G�re le type de collectable lorsque il est pris par l'utilisateur
void manageCollectable(Collectable* collectable);