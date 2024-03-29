#pragma once

#include "Settings.h"

/// @brief Structure contenant l'ensemble des assets du jeu.
/// Cela correspond aux ressources utilis�es (textures, musiques, sons...)
typedef struct Assets_s
{
    /// @brief Tableau des diff�rents calques de fond.
    SDL_Texture* layer1;
    SDL_Texture* layer2;

    /// @brief Texture du vaisseau du joueur.
    SDL_Texture* player;
    SDL_Texture* player_gun_1;
    SDL_Texture* player_gun_2;

    // Texture de GameOver
    SDL_Texture* GameOver;

    //Texture de Win
    SDL_Texture* Win;

    //texture des coeurs
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

    /// @brief texture des shields.
    SDL_Texture* ShieldEnnemy;
    SDL_Texture* ShieldPlayer;


    /// @brief Texture du tir d'un ennemi.
    SDL_Texture *fighterBullet;
    SDL_Texture* fighterBullet2;
    SDL_Texture* fighterBullet3;

    // musique du jeu
    Mix_Music *backgroundMusic;

    // son des tir alli� et ennemis
    Mix_Chunk* PlayerBulletSound;
    Mix_Chunk* EnemyBulletSound1;

    // son des mort alli� et ennemis
    Mix_Chunk* EnemyDeath;
    Mix_Chunk* PlayerDeath;

    // son du menu
    Mix_Chunk* MenuClickSound1;

    //texture du menu
    SDL_Texture* MenuRestart;
    SDL_Texture* MenuStart;
    SDL_Texture* MenuQuit;
    SDL_Texture* MenuSoundOn;
    SDL_Texture* MenuSoundOff;
    SDL_Texture* MenuLevel1;
    SDL_Texture* MenuLevel2;
    SDL_Texture* MenuPlayAgain;
    SDL_Texture* MenuSelector;

    //texture des collectables
    SDL_Texture* CollectableHealth;
    SDL_Texture* CollectableSpeed;
    SDL_Texture* CollectableBullet1;
    SDL_Texture* CollectableBullet2;

    //texture de la barre de dur�e du power-up d'attaque
    SDL_Texture* Gun100PowerUpBar;
    SDL_Texture* Gun80PowerUpBar;
    SDL_Texture* Gun60PowerUpBar;
    SDL_Texture* Gun40PowerUpBar;
    SDL_Texture* Gun20PowerUpBar;
    SDL_Texture* Gun00PowerUpBar;

    //texture de la barre de dur�e du power-up de vitesse
    SDL_Texture* Speed100PowerUpBar;
    SDL_Texture* Speed80PowerUpBar;
    SDL_Texture* Speed60PowerUpBar;
    SDL_Texture* Speed40PowerUpBar;
    SDL_Texture* Speed20PowerUpBar;
    SDL_Texture* Speed00PowerUpBar;
} Assets;

/// @brief Cr�e la structure contenant les assets du jeu.
/// @param renderer le moteur de rendu.
/// @return La structure contenant les assets du jeu.
Assets *Assets_New(SDL_Renderer *renderer);

/// @brief D�truit la structure contenant les assets du jeu.
/// @param self les assets.
void Assets_Delete(Assets *self);
