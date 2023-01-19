#include "Input.h"
#include "Common.h"
#include "Scene.h"

int const JOYSTICK_DEAD_ZONE = 8000;


Input *Input_New(Scene *scene)
{
    Input *self = (Input *)calloc(1, sizeof(Input));
    AssertNew(self);

    self->scene = scene;
    self->gameController = NULL;

    // Regarde si il existe un joystick
    if (SDL_NumJoysticks() < 1)
    {
        printf("No joystick connected\n");
    }
    else
    {
        printf("Joystick connected\n");
        self->gameController = SDL_JoystickOpen(0);
        if (self->gameController == NULL)
        {
            printf("Aie erreur, impossible de se co au joystick");
        }
    }

    return self;
}

void Input_Delete(Input *self)
{
    if (!self) return;

    // On libère le joystick
    SDL_JoystickClose(self->gameController);
    self->gameController = NULL;
    free(self);
}

void Input_Update(Input *self)
{
    self->escPressed = false;
    self->quitPressed = false;
    self->shootPressed = false;

    SDL_Event evt;
    while (SDL_PollEvent(&evt))
    {
        switch (evt.type)
        {
        case SDL_QUIT:
            self->quitPressed = true;
            break;

        case SDL_KEYDOWN:
            if (evt.key.repeat)
                break;

            switch (evt.key.keysym.scancode)
            {
            case SDL_SCANCODE_ESCAPE:
                self->escPressed = true;
                break;

            case SDL_SCANCODE_RIGHT:
                // Deplacement à droite
                self->hAxis = 4.f;
                break;

            case SDL_SCANCODE_LEFT:
                // Deplacement à gauche
                self->hAxis = -4.f;
                break;

            case SDL_SCANCODE_UP:
                // Deplacement en haut
                self->vAxis = 4.f;
                break;

            case SDL_SCANCODE_DOWN:
                // Deplacement en bas
                self->vAxis = -4.f;
                break;

            case SDL_SCANCODE_SPACE:
                // Tir du joueur 
                self->shootPressed = true;
                break;

            default:
                break;
            }
            break;

        case SDL_KEYUP:
            if (evt.key.repeat)
                break;

            switch (evt.key.keysym.scancode)
            {
            case SDL_SCANCODE_RIGHT:
                // Deplacement à droite
                if (self->hAxis > 0.f)
                    self->hAxis = 0.f;
                break;

            case SDL_SCANCODE_LEFT:
                // Deplacement à gauche
                if (self->hAxis < 0.f)
                    self->hAxis = 0.f;
                break;

            case SDL_SCANCODE_UP:
                // Deplacement en haut
                if (self->vAxis > 0.f)
                    self->vAxis = 0.f;
                break;

            case SDL_SCANCODE_DOWN:
                // Deplacement en bas
                if (self->vAxis < 0.f)
                    self->vAxis = 0.f;
                break;

            default:
                break;
            }
            break;

        case SDL_MOUSEBUTTONUP: {
            int mouseX = evt.button.x;
            int mouseY = evt.button.y;
            mouseClickActionIntersectionMenu(mouseX, mouseY, self->scene->menu);
            break;
        }

        case SDL_JOYAXISMOTION:
            if (evt.jaxis.which == 0)
            {
                if (evt.jaxis.axis == 0)
                {
                    if (evt.jaxis.value < -JOYSTICK_DEAD_ZONE)
                    {
                        self->hAxis = -4.f;
                    }
                    else if (evt.jaxis.value > JOYSTICK_DEAD_ZONE)
                    {
                        self->hAxis = 4.f;
                    }
                    else {
                        self->hAxis = 0.f;
                    }
                }
                if (evt.jaxis.axis == 1)
                {
                    if (evt.jaxis.value < -JOYSTICK_DEAD_ZONE)
                    {
                        self->vAxis = 4.f;
                    }
                    else if (evt.jaxis.value > JOYSTICK_DEAD_ZONE)
                    {
                        self->vAxis = -4.f;
                    }
                    else {
                        self->vAxis = 0.f;
                    }
                }
            }

            break;
        case SDL_JOYBUTTONDOWN:
            switch (evt.jbutton.button)
            {
            case 2:
                self->shootPressed = true;
                break;
            case 7:
                self->shootPressed = true;
                break;
            case 9:
                self->escPressed = true;
                break;
            }
            break;
        }
    }
}