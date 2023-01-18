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
        { &self->layers[0],     "../Assets/Background/bg1.png"                  },
        { &self->layers[1],     "../Assets/Background/bg2.png"                  },
        { &self->layers[2],     "../Assets/Background/bg3.png"                  },
        { &self->playerBullet,  "../Assets/Bullet/bulletp.png"                  },
        { &self->playerBulletGun1,  "../Assets/Bullet/bullet_gun_1.png"         },
        { &self->playerBulletGun2,  "../Assets/Bullet/bullet_gun_2.png"         },
        { &self->fighter1,       "../Assets/Enemy/Enemy1.png"                   },
        { &self->fighter2,       "../Assets/Enemy/Enemy2.png"                   },
        { &self->fighter3,       "../Assets/Enemy/Enemy3.png"                   },
        { &self->fighter4,       "../Assets/Enemy/AndromedaRangerCaptain.png"   },
        { &self->fighter5,       "../Assets/Enemy/Enemy5.png"                   },
        { &self->fighter6,       "../Assets/Enemy/EnemyBoss2Gold.png"           },
        { &self->fighter7,       "../Assets/Enemy/Enemy7.png"                   },
        { &self->fighterBullet, "../Assets/Bullet/bullete.png"                  },
        { &self->player, "../Assets/Player/P-red-a.png"                         },
        { &self->player_gun_1, "../Assets/Player/P-red-d.png"                   },
        { &self->player_gun_2, "../Assets/Player/P-red-d2.png"                  },
        { &self->playerHeart, "../Assets/Player/heart.png"                      },
        { &self->MenuQuit, "../Assets/Menu/quit2.png"                           },
        { &self-> MenuStart, "../Assets/Menu/play.png"                          },
        { &self->CollectableHealth, "../Assets/Collectables/health.png"         },
        { &self->CollectableSpeed, "../Assets/Collectables/speed.png"           },
        { &self->CollectableBullet1, "../Assets/Collectables/bull.png"          },
        { &self->CollectableBullet2, "../Assets/Collectables/rocket.png"        },
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
    Mix_FreeMusic(self->backgroundMusic);
    self->backgroundMusic = NULL;

    // -------------------------------------------------------------------------
    // Libère les textures

    SDL_Texture **texPointers[] = {
        &self->layers[0],
        &self->layers[1],
        &self->layers[2],
        &self->playerBullet,
        &self->fighter1,
        & self->fighter2,
        & self->fighter3,
        & self->fighter4,
        & self->fighter5,
        & self->fighter6,
        & self->fighter7,
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