#include "Assets.h"

typedef struct TextureSpec_s
{
    SDL_Texture **ptr;
    char *path;
} TextureSpec;

Assets *Assets_New(SDL_Renderer *renderer)
{
    Assets *self = (Assets *)calloc(1, sizeof(Assets));
    AssertNew(self);

    // -------------------------------------------------------------------------
    // Chargement des audios/musics
    self->backgroundMusic = NULL;
    self->backgroundMusic = Mix_LoadMUS("../Assets/Audio/Shoot Em Up EXPERIENCE - GAME SOUNDTRACK.mp3");
    if (self->backgroundMusic == NULL)
    {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        assert(false);
        abort();
    } 
    else
    {
        Mix_PlayMusic(self->backgroundMusic, -1);
    }
    self->PlayerBulletSound = NULL;
    self->PlayerBulletSound = Mix_LoadWAV("../Assets/Audio/PlayerShoot.wav");

    self->EnemyBulletSound1 = NULL;
    self->EnemyBulletSound1 = Mix_LoadWAV("../Assets/Audio/EnergyGun_Shoot1A.wav");

    // -------------------------------------------------------------------------
    // Chargement des textures

    TextureSpec texSpecs[] = {
        { &self->layers[0],     "../Assets/Background/layer_01.png"   },
        { &self->layers[1],     "../Assets/Background/layer_02.png"   },
        { &self->playerBullet,  "../Assets/Player/bullet_default.png" },
        { &self->fighter1,       "../Assets/Enemy/Enemy1.png"         },
        { &self->fighter2,       "../Assets/Enemy/Enemy2.png"         },
        { &self->fighter3,       "../Assets/Enemy/Enemy3.png"         },
        { &self->fighterBullet, "../Assets/Enemy/fighter_bullet.png"  },
        { &self->player, "../Assets/Player/P-red-a.png"               },
        { &self->MenuQuit, "../Assets/Menu/quit2.png"                 },
        { &self-> MenuStart, "../Assets/Menu/play.png"                }
    };
    int texSpecCount = sizeof(texSpecs) / sizeof(TextureSpec);

    for (int i = 0; i < texSpecCount; i++)
    {
        SDL_Texture **texPtr = texSpecs[i].ptr;
        char *path = texSpecs[i].path;

        *texPtr = IMG_LoadTexture(renderer, path);
        if (*texPtr == NULL)
        {
            printf("ERROR - Loading texture %s\n", path);
            printf("      - %s\n", SDL_GetError());
            assert(false);
            abort();
        }
    }

    // -------------------------------------------------------------------------
    // Chargement des textures du menu


    return self;
}

void Assets_Delete(Assets *self)
{
    if (!self) return;

    // -------------------------------------------------------------------------
    // Libère les audios/musics
    Mix_FreeChunk(self->backgroundMusic);
    self->backgroundMusic = NULL;

    // -------------------------------------------------------------------------
    // Libère les textures

    SDL_Texture **texPointers[] = {
        &self->layers[0],
        &self->layers[1],
        &self->playerBullet,
        &self->fighter1,
        & self->fighter2,
        & self->fighter3,
        &self->fighterBullet,
        &self->player,
    };
    int count = sizeof(texPointers) / sizeof(SDL_Texture **);

    for (int i = 0; i < count; i++)
    {
        if (*texPointers[i])
            SDL_DestroyTexture(*(texPointers[i]));
    }



    free(self);
}