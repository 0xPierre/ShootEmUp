#pragma once
#include "Settings.h"

typedef struct Scene_s Scene;


/// @brief Structure repr�sentant le menu du jeu.
typedef struct Menu_s
{
    /// @brief Sc�ne associ�e.
    Scene* scene;
    /// @brief �tat du menu
    /// Utilis� pour afficher ou virer le menu
    int isOpen;

    /// @brief Stocke l'objet SDL du menu
    SDL_Rect MenuStart;
    SDL_Rect MenuQuit;

    ///@brief Stocke le curseur par d�fault du joueur
    SDL_Cursor* cursor_default;
    SDL_Cursor* cursor_pointer;
} Menu;

/// @brief Cr�� le menu
/// @param scene la scene du monde
/// @return Le menu cr��
Menu* Menu_New(Scene* scene);

/// @brief D�truit la sc�ne principale.
/// @param self le menu
void Menu_Delete(Menu* self);

/// @brief Met � jour le menu
/// Cette fonction est appel�e � chaque tour de la boucle de rendu.
/// @param self le menu
void Menu_Update(Menu* self);

/// @brief Dessine la sc�ne dans le moteur de rendu.
/// @param self le menu
void Menu_Render(Menu* self);

/// @brief Change le curseur en curseur main lorsqu'il se trouve sur la zone demand�.
/// @param self le menu.
void changeCursor(Menu* self);

/// @brief Regarde si mouseX,mouseY se trouve dans un rectangle.
/// @param x,y les coords du rectangle, mouseX,mouseY les coords de la souris.
int isInsideRect(int x, int y, int w, int h, int mouseX, int mouseY);

/// @brief Regarde si un bouton du menu a �t� cliqu� et agis en cons�quence.
/// @param mouseX,mouseY les coords de la souris, self le menu.
void mouseClickActionIntersectionMenu(int mouseX, int mouseY, Menu* self);