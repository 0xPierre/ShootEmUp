#pragma once

#include "Settings.h"
typedef struct Scene_s Scene;

/// @brief Structure repr�sentant un gestionnaire des entr�es utilisateur.
typedef struct Input_s
{
    Scene* scene;
    /// @brief Bool�en indiquant si le bouton "quitter" (croix en haut � droite) vient d'�tre press�.
    bool quitPressed;

    /// @brief Boolean indiquant si la touche echap a �t� press�
    bool escPressed;

    /// @brief Bool�en indiquant si la touche de tir vient d'�tre press�e.
    bool shootPressed;

    /// @brief Bool�en indiquant si la touche toggelant l'invicibilit� vient d'�tre press�e.
    bool invincibilityPressed;

    /// @brief Nombre indiquant le d�placement horizontal du joueur.
    /// Les valeurs pour un clavier ou un joystick sont dans l'intervalle
    /// [-1.0f, 1.0f].
    /// La valeur 0.0f d�signe la position par d�faut.
    /// Une valeur n�gative d�signe un d�placement vers la gauche.
    /// Une valeur positive d�signe un d�placement vers la droite.
    float hAxis;

    /// @brief Nombre indiquant le d�placement vertical du joueur.
    /// Les valeurs pour un clavier ou un joystick sont dans l'intervalle
    /// [-1.0f, 1.0f].
    /// La valeur 0.0f d�signe la position par d�faut.
    /// Une valeur n�gative d�signe un d�placement vers le bas.
    /// Une valeur positive d�signe un d�placement vers le haut.
    float vAxis;

    /// @brief Si l'�tat est true, alors il faut que la touche repasse en keyup ou en 0 ( manette ) pour pouvoir etre renvoy�, vzy je sais c pas clair mais il est 1h du mat et c'est � rendre tout � l'heure, je veux aller dormir et plus s�r on va avoir eval surprise d'analyse jvais avoir 3
    bool isMenuKeyBLocked;

    SDL_Joystick* gameController;
} Input;

/// @brief Cr�e un nouveau gestionnaire des entr�es utilisateur.
/// @return Le gestionnaire cr��.
Input *Input_New(Scene* scene);

/// @brief D�truit un gestionnaire des entr�es utilisateur.
/// @param self le gestionnaire.
void Input_Delete(Input *self);

/// @brief Met � jour le gestionnaire des entr�es utilisateur.
/// Cette fonction effectue la boucle des �v�nement SDL.
/// @param self le gestionnaire.
void Input_Update(Input *self);
