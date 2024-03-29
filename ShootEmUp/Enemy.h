#pragma once

#include "Settings.h"
#include "Math.h"

typedef struct Scene_s Scene;

/// @brief Enum�ration repr�sentant les �tats possibles d'un ennemi.
typedef enum EnemyState_e
{
    /// @brief Etat par d�faut d'un ennemi.
    ENEMY_FIRING,

    /// @brief Etat d'un ennemi quand il joue l'animation de destruction.
    ENEMY_DYING,

    /// @brief Etat d'un ennemi quand il est mort et que son animation de
    /// destruction est termin�e.
    ENEMY_DEAD
} EnemyState;

/// @brief Enum�ration des types possibles pour un ennemi.
typedef enum EnemyType_e
{
    /// @brief Ennemi simple.
    ENEMY_FIGHTER_1,
    ENEMY_FIGHTER_2,
    ENEMY_FIGHTER_3,
    ENEMY_FIGHTER_4,
    ENEMY_FIGHTER_5,
    ENEMY_FIGHTER_6,
    ENEMY_FIGHTER_7,
} EnemyType;

/// @brief Structure repr�sentant un ennemi.
typedef struct Enemy_s
{
    /// @brief Sc�ne associ�e.
    Scene *scene;

    /// @brief Texture utilis�e pour le rendu.
    SDL_Texture *texture;

    /// @brief Position de l'ennemi exprim�e dans le r�f�rentiel monde.
    Vec2 position;

    /// @brief Type de l'ennemi.
    /// Les valeurs possibles sont d�finies dans EnemyType.
    int type;

    /// @brief Etat de l'ennemi.
    /// Les valeurs possibles sont d�finies dans EnemyState.
    int state;

    /// @brief Largeur de la texture de l'ennemi
    /// exprim�e dans le r�f�rentiel monde.
    float worldW;

    /// @brief Hauteur de la texture de l'ennemi
    /// exprim�e dans le r�f�rentiel monde.
    float worldH;

    /// @brief largeur de la texture du shield
    /// exprim�e dans le r�f�rentiel monde.
    float shieldW;

    /// @brief Hauteur de la texture du shield
    /// exprim�e dans le r�f�rentiel monde.
    float shieldH;

    /// @brief Rayon de l'ennemi exprim� dans le r�f�rentiel monde.
    /// Il est utilis� dans le moteur physique pour tester les collisions.
    float radius;

    // rotation afin que l'ennem�is sois orient� avec sont tir
    float angleShoot;



    /// @brief Nombre de vie restant de l'ennemi.
    /// Utilis� lorsque l'ennemi se prends un projectil.
    int remainingLives;

    /// @brief Ecart de temps entre chaque projectil.
    /// Utilis� lorsque l'ennemi s'update.
    float timeBetweenBullets;

    //nombre de bullet
    int bulletnum;
    /// @brief Ecart de temps entre chaque projectil.
    /// Utilis� lorsque l'ennemi s'update.
    float lastBulletTime;

    /// quel type de balle on tire
    int lastTypeofBullet;

    /// bouclier
    int shield;
    bool IsShieldActivated;
    int shieldtime;

    /// @brief Valeur al�atoire de d�part de mouvement en X.
    /// Utilis� pour �viter que les mouvements se ressemblent trop.
    int randomStartingTickX;

    /// @brief Valeur al�atoire de d�part de mouvement en Y.
    /// Utilis� pour �viter que les mouvements se ressemblent trop.
    int randomStartingTickY;
} Enemy;

/// @brief Cr�e un nouvel ennemi.
/// @param scene la sc�ne.
/// @param type le type de l'ennemi.
/// @param position la position de d�part de l'ennemi exprim�e dans le r�f�rentiel monde.
/// @return L'ennemi cr��.
Enemy *Enemy_New(Scene *scene, int type, Vec2 position);

/// @brief D�truit un ennemi.
/// Cette m�thode est appel�e par la sc�ne.
/// @param self l'ennemi.
void Enemy_Delete(Enemy *self);

/// @brief Met � jour un ennemi.
/// @param self l'ennemi.
void Enemy_Update(Enemy *self);

/// @brief Dessine un ennemi dans le moteur de rendu.
/// @param self l'ennemi.
void Enemy_Render(Enemy *self);

/// @brief Inflige des dommages � un ennemi.
/// @param self l'ennemi.
/// @param damage la quantit� de dommages (nombre de points de vie � perdre).
void Enemy_Damage(Enemy *self, int damage);
