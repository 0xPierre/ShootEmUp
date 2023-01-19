#pragma once

#include "Settings.h"
#include "Math.h"

#define MAX_PLAYER_LIVES 5;

typedef struct Scene_s Scene;

/// @brief Enumération représentant les états possibles du joueur.
typedef enum PlayerState_e
{
    /// @brief Etat par défaut du joueur.
    PLAYER_FLYING,

    /// @brief Etat du joueur quand il joue l'animation de destruction.
    PLAYER_DYING,

    /// @brief Etat du joueur quand il est mort et que son animation de
    /// destruction est terminée.
    PLAYER_DEAD,
} PlayerState;

/// @brief Structure représentant le joueur.
typedef struct Player_s
{
    /// @brief Scène associée.
    Scene *scene;

    /// @brief Texture utilisée pour le rendu.
    SDL_Texture *texture;

    /// @brief Position du joueur exprimée dans le référentiel monde.
    Vec2 position;

    /// @brief Etat du joueur.
    /// Les valeurs possibles sont définies dans PlayerState.
    int state;

    /// @brief Rayon du joueur exprimé dans le référentiel monde.
    /// Il est utilisé dans le moteur physique pour tester les collisions.
    float radius;

    /// @brief Nombre de vies restantes du joueur
    int remainingLives;

    /// @brief Nombre de vie maximal du joueur
    int maximumLives;

    /// @brief Nombre de temps depuis le début de l'animation de mort
    float isDyingSince;

    /// @brief Stocke l'objet SDL des coeurs
    SDL_Rect hearts[5];

    /// @brief Etat du power up vitesse
    bool isSpeedPowerUpActivated;

    /// @brief Temps auquel le powerup a été activé pour la dernière fois
    float speedPowerUpActivatedSince;

    /// @brief Durée d'activation du powerup vitesse
    float speedPowerUpDuration;

    /// @brief Etat du power up gun upgrade 1
    bool isGun1PowerUpActivated;

    /// @brief Temps auquel le powerup a été activé pour la dernière fois
    float gun1PowerUpActivatedSince;

    /// @brief Durée d'activation du powerup vitesse
    float gun1PowerUpDuration;

    /// @brief Etat du power up gun upgrade 1
    bool isGun2PowerUpActivated;

    /// @brief Temps auquel le powerup a été activé pour la dernière fois
    float gun2PowerUpActivatedSince;

    /// @brief Durée d'activation du powerup vitesse
    float gun2PowerUpDuration;

    /// @brief Si le joueur est invicible ou non
    bool isInvincible;
} Player;

/// @brief Crée un nouveau joueur.
/// @param scene la scène.
/// @return Le joueur créé.
Player *Player_New(Scene *scene);

/// @brief Détruit un joueur.
/// @param self le joueur.
void Player_Delete(Player *self);

/// @brief Met à jour le joueur.
/// @param self le joueur.
void Player_Update(Player *self);

/// @brief Dessine le joueur dans le moteur de rendu.
/// @param self le joueur.
void Player_Render(Player *self);

/// @brief Inflige des dommages au joueur.
/// @param self le joueur.
/// @param damage la quantité de dommages (nombre de points de vie à perdre).
void Player_Damage(Player *self, int damage);

/// @brief Dessine les coeurs du joueur dans le moteur de rendu
/// @param self le joueur
void Heart_Render(Player* self);

/// @brief Dessine les bar des collectables du joueur dans le temps, dans le moteur de rendu ( vie, gun... )
/// @param self le joueur
void Collectables_Bar_Render(Player* self);