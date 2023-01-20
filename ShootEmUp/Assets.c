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

    self->MenuClickSound1 = NULL;
    self->MenuClickSound1 = Mix_LoadWAV("../Assets/Audio/Menu2_SelectA.wav");

    self->EnemyDeath = NULL;
    self->EnemyDeath = Mix_LoadWAV("../Assets/Audio/enemydeath.mp3");

    self->PlayerDeath = NULL;
    self->PlayerDeath = Mix_LoadWAV("../Assets/Audio/playerdeath.mp3");

    // Gère le volume de la musique et des sons
    Mix_Volume(-1, SOUND_VOLUME);
    Mix_VolumeMusic(MUSIC_VOLUME);


    // -------------------------------------------------------------------------
    // Chargement des textures

    TextureSpec texSpecs[] = {
        { &self->layer1,     "../Assets/Background/bg11.png"                    },
        { &self->layer2,     "../Assets/Background/bg12.png"                    },
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
        { &self->fighterBullet2, "../Assets/Bullet/bullete2.png"                },
        { &self->fighterBullet3, "../Assets/Bullet/bullete3.png"                },
        { &self->player, "../Assets/Player/P-red-a.png"                         },
        { &self->player_gun_1, "../Assets/Player/P-red-d.png"                   },
        { &self->player_gun_2, "../Assets/Player/P-red-d2.png"                  },
        { &self->playerHeart, "../Assets/Player/heart.png"                      },
        { &self->MenuQuit, "../Assets/Menu/quit2.png"                           },
        { &self->MenuStart, "../Assets/Menu/play.png"                           },
        { &self->MenuSoundOn, "../Assets/Menu/sound on.png"                     },
        { &self->MenuSoundOff, "../Assets/Menu/sound off.png"                   },
        { &self->MenuLevel1, "../Assets/Menu/lv1.png"                           },
        { &self->MenuLevel2, "../Assets/Menu/lv2.png"                           },
        { &self->MenuPlayAgain, "../Assets/Menu/rejouer.png"                    },
        { &self->MenuSelector, "../Assets/Menu/selector.png"                    },
        { &self->CollectableHealth, "../Assets/Collectables/health.png"         },
        { &self->CollectableSpeed, "../Assets/Collectables/speed.png"           },
        { &self->CollectableBullet1, "../Assets/Collectables/bull.png"          },
        { &self->CollectableBullet2, "../Assets/Collectables/rocket.png"        },
        { &self->Gun100PowerUpBar, "../Assets/bars/gun100.png"                  },
        { &self->Gun80PowerUpBar, "../Assets/bars/gun80.png"                    },
        { &self->Gun60PowerUpBar, "../Assets/bars/gun60.png"                    },
        { &self->Gun40PowerUpBar, "../Assets/bars/gun40.png"                    },
        { &self->Gun20PowerUpBar, "../Assets/bars/gun20.png"                    },
        { &self->Gun00PowerUpBar, "../Assets/bars/gun00.png"                    },
        { &self->Speed100PowerUpBar, "../Assets/bars/speed100.png"              },
        { &self->Speed80PowerUpBar, "../Assets/bars/speed80.png"                },
        { &self->Speed60PowerUpBar, "../Assets/bars/speed60.png"                },
        { &self->Speed40PowerUpBar, "../Assets/bars/speed40.png"                },
        { &self->Speed40PowerUpBar, "../Assets/bars/speed20.png"                },
        { &self->Speed00PowerUpBar, "../Assets/bars/speed00.png"                },
        { &self->ShieldEnnemy, "../Assets/Enemy/SHIELDE.png"                    },
        { &self->ShieldPlayer, "../Assets/Player/SHIELDP.png"                   },
        { &self->GameOver, "../Assets/Background/GameOver.png"                  },
        { &self->Win, "../Assets/Background/win.png"                            },
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

    SDL_Texture** texPointers[] = {
        &self->layer1,
        &self->layer2,
        &self->playerBullet,
        &self->playerBulletGun1,
        &self->playerBulletGun2,
        &self->fighter1,
        &self->fighter2,
        &self->fighter3,
        &self->fighter4,
        &self->fighter5,
        &self->fighter6,
        &self->fighter7,
        &self->fighterBullet,
        &self->fighterBullet2,
        &self->fighterBullet3,
        &self->player,
        &self->player_gun_1,
        &self->player_gun_2,
        &self->playerHeart,
        &self->MenuQuit,
        &self->MenuStart,
        &self->MenuLevel1,
        &self->MenuLevel2,
        &self->MenuSoundOff,
        &self->MenuSoundOn,
        &self->MenuSelector,
        &self->CollectableHealth,
        &self->CollectableSpeed,
        &self->CollectableBullet1,
        &self->CollectableBullet2,
        &self->Gun100PowerUpBar,
        &self->Gun80PowerUpBar,
        &self->Gun60PowerUpBar,
        &self->Gun40PowerUpBar,
        &self->Gun20PowerUpBar,
        &self->Gun00PowerUpBar,
        &self->Speed100PowerUpBar,
        &self->Speed80PowerUpBar,
        &self->Speed60PowerUpBar,
        &self->Speed40PowerUpBar,
        &self->Speed20PowerUpBar,
        &self->Speed00PowerUpBar,
        &self->ShieldEnnemy,
        &self->ShieldPlayer,
        &self->GameOver,
        &self->Win,
    };
    int count = sizeof(texPointers) / sizeof(SDL_Texture **);

    for (int i = 0; i < count; i++)
    {
        if (*texPointers[i])
            SDL_DestroyTexture(*(texPointers[i]));
    }



    free(self);
}