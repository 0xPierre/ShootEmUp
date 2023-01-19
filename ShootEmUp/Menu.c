#include "Menu.h"
#include "Input.h"
#include "Scene.h"

Menu* Menu_New(Scene *scene)
{
    Menu* self = (Menu*)calloc(1, sizeof(Menu));
    AssertNew(self);

    self->scene = scene;
    self->isOpen = 1;

    self->cursor_default = SDL_GetCursor();
    self->cursor_pointer = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);

    return self;
}

void Menu_Delete(Menu* self)
{
    if (!self) return;
    free(self);
}

void Menu_Update(Menu* self)
{
    // On récupère des infos essentielles (communes à tout objet)
    Scene* scene = self->scene;
    Input* input = Scene_GetInput(scene);
}

void Menu_Render(Menu* self)
{
    Scene* scene = self->scene;
    Input* input = Scene_GetInput(scene);
    // Permet de toggle le menu avec echap seulement quand la partie a débuté
    if (input->escPressed && scene->isGameStarted)
    {
        self->isOpen = !self->isOpen;

        SDL_SetCursor(self->cursor_default);
    }

    // Affichage du menu
    if (self->isOpen)
    {
        /*
        * Affichage du bouton Jouer
        */
        int MenuStartWidth = 175;
        int MenuStartHeight = 175;

        self->MenuStart.x =  WINDOW_WIDTH / 2 - MenuStartWidth / 2;
        self->MenuStart.y = WINDOW_HEIGHT / 5;
        self->MenuStart.w = MenuStartWidth;
        self->MenuStart.h = MenuStartHeight;
        SDL_RenderCopy(scene->renderer, scene->assets->MenuStart, NULL, &self->MenuStart);

        /*
        * Affichage du bouton Quitter
        */
        int MenuQuitWidth = 287;
        int menuQuitHeight = 150;

        self->MenuQuit.x = WINDOW_WIDTH / 2 - MenuQuitWidth / 2;
        self->MenuQuit.y = WINDOW_HEIGHT / 2 - 20;
        self->MenuQuit.w = MenuQuitWidth;
        self->MenuQuit.h = menuQuitHeight;
        SDL_RenderCopy(scene->renderer, scene->assets->MenuQuit, NULL, &self->MenuQuit);

    }
    changeCursor(self);
}

int isInsideRect(int x, int y, int w, int h, int mouseX, int mouseY)
{
    return (int)(
        mouseX >= x
        && mouseX <= x + w
        && mouseY >= y
        && mouseY <= y + h
    );
}

void changeCursor(Menu* self)
{
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    /*
     Lorsque que showCursorPointer est true
     le curseur de type pointer devient le curseur de l'utilisateur
    */
    bool showCursorPointer = false;

    
    // Regarde si le curseur pointe sur le bouton Jouer
    if (isInsideRect(
        self->MenuStart.x,
        self->MenuStart.y,
        self->MenuStart.w,
        self->MenuStart.h,
        mouseX,
        mouseY
    ))
        showCursorPointer = true;

    // Regarde si le curseur pointe sur le bouton Quitter
    else if (isInsideRect(
        self->MenuQuit.x,
        self->MenuQuit.y,
        self->MenuQuit.w,
        self->MenuQuit.h,
        mouseX,
        mouseY
    ))
        showCursorPointer = true;


   // Change le curseur
    if (showCursorPointer)
    {
        // Vérifie que le menu est bien ouvert
        if (self->isOpen)
            SDL_SetCursor(self->cursor_pointer);
    }
    else
    {
        SDL_SetCursor(self->cursor_default);
    }
}

void mouseClickActionIntersectionMenu(int mouseX, int mouseY, Menu *self)
{
    // Vérifie que le menu est bien ouvert
    if (self->isOpen)
    {
        // Regarde si le bouton joué a été cliqué
        if (isInsideRect(
            self->MenuStart.x,
            self->MenuStart.y,
            self->MenuStart.w,
            self->MenuStart.h,
            mouseX,
            mouseY
        )) {
            self->scene->menu->isOpen = false;
            self->scene->isGameStarted = true;
        }

        // Regarde si le bouton Quitter à été cliqué
        else if (isInsideRect(
            self->MenuQuit.x,
            self->MenuQuit.y,
            self->MenuQuit.w,
            self->MenuQuit.h,
            mouseX,
            mouseY
        )) {
            self->scene->input->quitPressed = true;
        }
    }
}