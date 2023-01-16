#pragma once

#include "Settings.h"

/// @brief Structure repr�sentant un chronom�tre.
typedef struct Timer_s
{
    /// @brief Temps de d�part.
    float startTime;

    /// @brief Temps du dernier appel � Timer_Update().
    float currentTime;

    /// @brief Temps de l'avant dernier appel � Timer_Update().
    float previousTime;

    /// @brief Echelle de temps appliqu�e.
    /// Si ce membre vaut 0.5f, le temps s'�coule deux fois moins rapidement.
    float scale;

    /// @brief Ecart entre les deux derniers appels � Timer_Update().
    float delta;

    /// @brief Ecart entre les deux derniers appels � Timer_Update()
    /// sans prendre en compte le facteur d'�chelle de temps.
    float unscaledDelta;

    /// @brief Ecart de temps maximal du timer.
    float maxDelta;

    /// @brief Temps �coul� entre le lancement du timer et le dernier appel �
    /// Timer_Update().
    float elapsed;

    /// @brief Temps �coul� entre le lancement du timer et le dernier appel �
    /// Timer_Update() sans prendre en compte le facteur d'�chelle de temps.
    float unscaledElapsed;
} Timer;

/// @brief Cr�e un nouveau timer.
/// @return Le timer cr�� ou NULL en cas d'erreur.
Timer* Timer_New();

/// @brief D�truit un timer pr�alablement allou� avec Timer_New().
/// @param[in,out] self le timer.
void Timer_Delete(Timer* self);

/// @brief Lance le timer.
/// @param[in,out] self le timer.
void Timer_Start(Timer* self);

/// @brief Met � jour le timer en fonction du temps actuel.
/// Cette fonction est typiquement appel�e � chaque tour de la boucle de rendu.
/// @param[in,out] self le timer.
void Timer_Update(Timer* self);

/// @brief D�finit l'�cart de temps maximal d'un timer.
/// @param self le timer.
/// @param maxDelta l'�cart de temps maximal.
INLINE void Timer_SetMaximumDeltaTime(Timer *self, float maxDelta)
{
    self->maxDelta = maxDelta;
}

/// @brief D�finit le facteur d'�chelle de temps appliqu�e � un timer.
/// Si l'�chelle vaut 0.5f, le temps s'�coule deux fois moins rapidement.
/// @param self le timer.
/// @param scale le facteur d'�chelle.
INLINE void Timer_SetTimeScale(Timer *self, float scale)
{
    assert(scale >= 0.0f);
    self->scale = scale;
}

/// @brief Renvoie le facteur d'�chelle de temps d'un timer.
/// @param self le timer.
/// @return Le facteur d'�chelle de temps d'un timer.
INLINE float Timer_GetTimeScale(Timer *self)
{
    return self->scale;
}

/// @brief Renvoie l'�cart de temps (en secondes) entre les deux derniers
/// appels � la fonction Timer_Update().
/// @param[in] self le timer.
/// @return L'�cart de temps entre les deux derni�res mises � jour.
INLINE float Timer_GetDelta(Timer *self)
{
    return self->delta;
}

/// @brief Renvoie l'�cart de temps (en secondes) entre les deux derniers
/// appels � la fonction Timer_Update().
/// Cette m�thode en tient pas compte de l'�chelle de temps du timer.
/// @param[in] self le timer.
/// @return L'�cart de temps entre les deux derni�res mises � jour
/// (sans �chelle de temps).
INLINE float Timer_GetUnscaledDelta(Timer *self)
{
    return self->unscaledDelta;
}

/// @brief Renvoie l'�cart de temps (en secondes) entre le lancement du timer
/// avec Timer_Start() et le dernier appel � Timer_Update().
/// @param[in] self le timer.
/// @return Le nombre de secondes �coul�es depuis le lancement du timer et la
/// derni�re mise � jour.
INLINE float Timer_GetElapsed(Timer *self)
{
    return self->elapsed;
}

/// @brief Renvoie l'�cart de temps (en secondes) entre le lancement du timer
/// avec Timer_Start() et le dernier appel � Timer_Update().
/// Cette m�thode en tient pas compte de l'�chelle de temps du timer.
/// @param[in] self le timer.
/// @return Le nombre de secondes �coul�es depuis le lancement du timer et la
/// derni�re mise � jour  (sans �chelle de temps).
INLINE float Timer_GetUnscaledElapsed(Timer *self)
{
    return self->unscaledElapsed;
}
