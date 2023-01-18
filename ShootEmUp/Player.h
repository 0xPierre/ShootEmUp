#pragma once

#include "Settings.h"
#include "Math.h"

typedef struct Scene_s Scene;

/// @brief Enum�ration repr�sentant les �tats possibles du joueur.
typedef enum PlayerState_e
{
    /// @brief Etat par d�faut du joueur.
    PLAYER_FLYING,

    /// @brief Etat du joueur quand il joue l'animation de destruction.
    PLAYER_DYING,

    /// @brief Etat du joueur quand il est mort et que son animation de
    /// destruction est termin�e.
    PLAYER_DEAD,
} PlayerState;

/// @brief Structure repr�sentant le joueur.
typedef struct Player_s
{
    /// @brief Sc�ne associ�e.
    Scene *scene;

    /// @brief Texture utilis�e pour le rendu.
    SDL_Texture *texture;

    /// @brief Position du joueur exprim�e dans le r�f�rentiel monde.
    Vec2 position;

    /// @brief Etat du joueur.
    /// Les valeurs possibles sont d�finies dans PlayerState.
    int state;

    /// @brief Rayon du joueur exprim� dans le r�f�rentiel monde.
    /// Il est utilis� dans le moteur physique pour tester les collisions.
    float radius;

    /// @brief Nombre de vies restantes du joueur
    int remainingLives;

    /// @brief Nombre de vie maximal du joueur
    int maximumLives;

    /// @brief Nombre de temps depuis le d�but de l'animation de mort
    float isDyingSince;

    /// @brief Etat du power up vitesse
    bool isSpeedPowerUpActivated;

    /// @brief Temps auquel le powerup a �t� activ� pour la derni�re fois
    float speedPowerUpActivatedSince;

    /// @brief Dur�e d'activation du powerup vitesse
    float speedPowerUpDuration;

    /// @brief Etat du power up gun upgrade 1
    bool isGun1PowerUpActivated;

    /// @brief Temps auquel le powerup a �t� activ� pour la derni�re fois
    float gun1PowerUpActivatedSince;

    /// @brief Dur�e d'activation du powerup vitesse
    float gun1PowerUpDuration;

    /// @brief Etat du power up gun upgrade 1
    bool isGun2PowerUpActivated;

    /// @brief Temps auquel le powerup a �t� activ� pour la derni�re fois
    float gun2PowerUpActivatedSince;

    /// @brief Dur�e d'activation du powerup vitesse
    float gun2PowerUpDuration;
} Player;

/// @brief Cr�e un nouveau joueur.
/// @param scene la sc�ne.
/// @return Le joueur cr��.
Player *Player_New(Scene *scene);

/// @brief D�truit un joueur.
/// @param self le joueur.
void Player_Delete(Player *self);

/// @brief Met � jour le joueur.
/// @param self le joueur.
void Player_Update(Player *self);

/// @brief Dessine le joueur dans le moteur de rendu.
/// @param self le joueur.
void Player_Render(Player *self);

/// @brief Inflige des dommages au joueur.
/// @param self le joueur.
/// @param damage la quantit� de dommages (nombre de points de vie � perdre).
void Player_Damage(Player *self, int damage);
