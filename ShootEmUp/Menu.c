#include "Menu.h"
#include "Input.h"
#include "Scene.h"

Menu* Menu_New(Scene *scene)
{
    Menu* self = (Menu*)calloc(1, sizeof(Menu));
    AssertNew(self);

    self->scene = scene;
    self->isOpen = 1;
    self->isAudioPlaying = true;

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
        * Affichage du bouton Jouer seulement si la partie a déjà commencé
        */
        if (self->scene->isGameStarted)
        {
            int MenuStartWidth = 175;
            int MenuStartHeight = 175;

            self->MenuStart.x =  WINDOW_WIDTH / 2 - MenuStartWidth / 2;
            self->MenuStart.y = WINDOW_HEIGHT / 10;
            self->MenuStart.w = MenuStartWidth;
            self->MenuStart.h = MenuStartHeight;

            SDL_RenderCopy(scene->renderer, scene->assets->MenuStart, NULL, &self->MenuStart);
        }

        /*
        * Affichage du bouton Level 1
        */
        int MenuLevel1Width = 320;
        int MenuLevel1Height = 84;

        self->MenuLevel1.x = WINDOW_WIDTH / 2 - 140;
        self->MenuLevel1.y = self->scene->isGameStarted ? 
            self->MenuStart.y + self->MenuStart.h + 20 : 
            // Si la partie n'a pas commencé alors le menuLevel1 est situé differement
            WINDOW_HEIGHT / 10 + 50;
        self->MenuLevel1.w = MenuLevel1Width;
        self->MenuLevel1.h = MenuLevel1Height;
        SDL_RenderCopy(scene->renderer, scene->assets->MenuLevel1, NULL, &self->MenuLevel1);

        /*
        * Affichage du bouton Level 2
        */
        int MenuLevel2Width = 320;
        int MenuLevel2Height = 84;

        self->MenuLevel2.x = WINDOW_WIDTH / 2 - 140;
        self->MenuLevel2.y = self->MenuLevel1.y + self->MenuLevel1.h + 10;
        self->MenuLevel2.w = MenuLevel2Width;
        self->MenuLevel2.h = MenuLevel2Height;
        SDL_RenderCopy(scene->renderer, scene->assets->MenuLevel2, NULL, &self->MenuLevel2);


        /*
        * Affichage du bouton Quitter
        */
        int MenuQuitWidth = 287;
        int MenuQuitHeight = 150;

        self->MenuQuit.x = WINDOW_WIDTH / 2 - MenuQuitWidth / 2 - 10;
        self->MenuQuit.y = self->MenuLevel2.y + self->MenuLevel2.h + 20;
        self->MenuQuit.w = MenuQuitWidth;
        self->MenuQuit.h = MenuQuitHeight;
        SDL_RenderCopy(scene->renderer, scene->assets->MenuQuit, NULL, &self->MenuQuit);

        /*
        * Affichage du bouton pour gérer le son
        */
        int MenuAudioWidth = 80;
        int MenuAudioHeight = 80;

        self->MenuAudio.x = 20;
        self->MenuAudio.y = 15;
        self->MenuAudio.w = MenuAudioWidth;
        self->MenuAudio.h = MenuAudioHeight;
        SDL_RenderCopy(
            scene->renderer,
            self->isAudioPlaying ? scene->assets->MenuSoundOn : scene->assets->MenuSoundOff,
            NULL, &self->MenuAudio
       );
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

    // Vérifie que le menu est bien ouvert
    if (self->isOpen)
    {
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

        // Regarde si le curseur pointe sur le bouton Level 1
        if (isInsideRect(
            self->MenuLevel1.x,
            self->MenuLevel1.y,
            self->MenuLevel1.w,
            self->MenuLevel1.h,
            mouseX,
            mouseY
        ))
            showCursorPointer = true;

        // Regarde si le curseur pointe sur le bouton Level 2
        if (isInsideRect(
            self->MenuLevel2.x,
            self->MenuLevel2.y,
            self->MenuLevel2.w,
            self->MenuLevel2.h,
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

        // Regarde si le curseur pointe sur le bouton Audio
        else if (isInsideRect(
            self->MenuAudio.x,
            self->MenuAudio.y,
            self->MenuAudio.w,
            self->MenuAudio.h,
            mouseX,
            mouseY
        ))
            showCursorPointer = true;
    }
    // Lorsque le joueur est mort, le bouton rejoué est visible
    else if (self->scene->player->state == PLAYER_DEAD)
    {
        // Regarde si le curseur pointe sur le bouton Play Again
        if (isInsideRect(
            self->MenuPlayAgain.x,
            self->MenuPlayAgain.y,
            self->MenuPlayAgain.w,
            self->MenuPlayAgain.h,
            mouseX,
            mouseY
        ))
            showCursorPointer = true;

        // Regarde si le curseur pointe sur le bouton Quitter du Game Over
        else if (isInsideRect(
            self->MenuQuit.x,
            self->MenuQuit.y,
            self->MenuQuit.w,
            self->MenuQuit.h,
            mouseX,
            mouseY
        ))
            showCursorPointer = true;
    }


   // Change le curseur
    if (showCursorPointer)
        SDL_SetCursor(self->cursor_pointer);
    else
        SDL_SetCursor(self->cursor_default);
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
            self->isOpen = false;
            self->scene->isGameStarted = true;
            Mix_PlayChannel(-1, self->scene->assets->MenuClickSound1, 0);
        }

        // Regarde si le bouton level 1 a été cliqué
        if (isInsideRect(
            self->MenuLevel1.x,
            self->MenuLevel1.y,
            self->MenuLevel1.w,
            self->MenuLevel1.h,
            mouseX,
            mouseY
        )) {
            Mix_PlayChannel(-1, self->scene->assets->MenuClickSound1, 0);
            startSceneAtLevel(self->scene, LEVEL_1);
        }

        // Regarde si le bouton level 1 a été cliqué
        if (isInsideRect(
            self->MenuLevel2.x,
            self->MenuLevel2.y,
            self->MenuLevel2.w,
            self->MenuLevel2.h,
            mouseX,
            mouseY
        )) {
            Mix_PlayChannel(-1, self->scene->assets->MenuClickSound1, 0);
            startSceneAtLevel(self->scene, LEVEL_2);
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
            Mix_PlayChannel(-1, self->scene->assets->MenuClickSound1, 0);
        }

        // Regarde si le bouton Audio à été cliqué
        else if (isInsideRect(
            self->MenuAudio.x,
            self->MenuAudio.y,
            self->MenuAudio.w,
            self->MenuAudio.h,
            mouseX,
            mouseY
        )) {
            // Si il a été cliqué alors on désactive ou active l'audio
            self->isAudioPlaying = !self->isAudioPlaying;

            if (!self->isAudioPlaying)
            {
                Mix_Volume(-1, 0);
                Mix_VolumeMusic(0);
            }
            else {
                Mix_Volume(-1, SOUND_VOLUME);
                Mix_VolumeMusic(MUSIC_VOLUME);
            }
            Mix_PlayChannel(-1, self->scene->assets->MenuClickSound1, 0);
        }
    }

    else if (self->scene->player->state == PLAYER_DEAD)
    {
        // Regarde si le bouton Play again a été cliqué
        if (isInsideRect(
            self->MenuPlayAgain.x,
            self->MenuPlayAgain.y,
            self->MenuPlayAgain.w,
            self->MenuPlayAgain.h,
            mouseX,
            mouseY
        )) {
            self->scene->player->state = PLAYER_FLYING;
            self->scene->isGameStarted = false;
            self->isOpen = true;

            Mix_PlayChannel(-1, self->scene->assets->MenuClickSound1, 0);
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
            Mix_PlayChannel(-1, self->scene->assets->MenuClickSound1, 0);
        }
    }
}