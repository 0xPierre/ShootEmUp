#pragma once
#include "Settings.h"

typedef struct Scene_s Scene;


/// @brief Structure représentant le menu du jeu.
typedef struct Menu_s
{
    /// @brief Scène associée.
    Scene* scene;
    /// @brief état du menu
    /// Utilisé pour afficher ou virer le menu
    int isOpen;

    /// @brief Stocke l'objet SDL du menu
    SDL_Rect MenuStart;
    SDL_Rect MenuQuit;

    ///@brief Stocke le curseur par défault du joueur
    SDL_Cursor* cursor_default;
    SDL_Cursor* cursor_pointer;
} Menu;

/// @brief Créé le menu
/// @param scene la scene du monde
/// @return Le menu créé
Menu* Menu_New(Scene* scene);

/// @brief Détruit la scène principale.
/// @param self le menu
void Menu_Delete(Menu* self);

/// @brief Met à jour le menu
/// Cette fonction est appelée à chaque tour de la boucle de rendu.
/// @param self le menu
void Menu_Update(Menu* self);

/// @brief Dessine la scène dans le moteur de rendu.
/// @param self le menu
void Menu_Render(Menu* self);

/// @brief Change le curseur en curseur main lorsqu'il se trouve sur la zone demandé.
/// @param self le menu.
void changeCursor(Menu* self);

/// @brief Regarde si mouseX,mouseY se trouve dans un rectangle.
/// @param x,y les coords du rectangle, mouseX,mouseY les coords de la souris.
int isInsideRect(int x, int y, int w, int h, int mouseX, int mouseY);

/// @brief Regarde si un bouton du menu a été cliqué et agis en conséquence.
/// @param mouseX,mouseY les coords de la souris, self le menu.
void mouseClickActionIntersectionMenu(int mouseX, int mouseY, Menu* self);