#pragma once

#include "Settings.h"

/// @brief Structure contenant l'ensemble des assets du jeu.
/// Cela correspond aux ressources utilis�es (textures, musiques, sons...)
typedef struct Assets_s
{
    /// @brief Tableau des diff�rents calques de fond.
    SDL_Texture *layers[3];

    /// @brief Texture du vaisseau du joueur.
    SDL_Texture* player;
    SDL_Texture* player_gun_1;
    SDL_Texture* player_gun_2;

    SDL_Texture* playerHeart;

    /// @brief Texture du tir du joueur.
    SDL_Texture* playerBullet;
    SDL_Texture* playerBulletGun1;
    SDL_Texture* playerBulletGun2;

    /// @brief Texture du vaisseau ennemi.
    SDL_Texture* fighter1;
    SDL_Texture* fighter2;
    SDL_Texture* fighter3;
    SDL_Texture* fighter4;
    SDL_Texture* fighter5;
    SDL_Texture* fighter6;
    SDL_Texture* fighter7;


    /// @brief Texture du tir d'un ennemi.
    SDL_Texture *fighterBullet;

    /// @brief 
    Mix_Music *backgroundMusic;

    Mix_Chunk* PlayerBulletSound;
    Mix_Chunk* EnemyBulletSound1;

    SDL_Texture* MenuRestart;
    SDL_Texture* MenuStart;
    SDL_Texture* MenuQuit;

    SDL_Texture* CollectableHealth;
    SDL_Texture* CollectableSpeed;
    SDL_Texture* CollectableBullet1;
    SDL_Texture* CollectableBullet2;
} Assets;

/// @brief Cr�e la structure contenant les assets du jeu.
/// @param renderer le moteur de rendu.
/// @return La structure contenant les assets du jeu.
Assets *Assets_New(SDL_Renderer *renderer);

/// @brief D�truit la structure contenant les assets du jeu.
/// @param self les assets.
void Assets_Delete(Assets *self);
