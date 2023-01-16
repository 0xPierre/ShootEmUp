#pragma once

#include "Settings.h"
#include "Math.h"

/// @brief Structure repr�sentant une cam�ra.
typedef struct Camera_s
{
    /// @brief Rectangle repr�sentant la vue de la cam�ra.
    /// Ces coordonn�es sont dans le r�f�rentiel monde.
    AABB m_worldView;

    /// @brief Largeur (en pixels) du r�f�rentiel vue de la cam�ra.
    int m_width;

    /// @brief Hauteur (en pixels) du r�f�rentiel vue de la cam�ra.
    int m_height;
} Camera;

/// @brief Cr�e une nouvelle cam�ra.
/// @param width largeur en pixels de la cam�ra.
/// @param height hauteur en pixels de la cam�ra.
/// @return La cam�ra cr��e.
Camera *Camera_New(int width, int height);

/// @brief D�truit une cam�ra.
/// @param self la cam�ra.
void Camera_Delete(Camera *self);

/// @brief Renvoie le rectangle vu par la cam�ra.
/// Les coordonn�es sont exprim�es dans le r�f�rentiel monde.
/// @param self la cam�ra.
/// @return Le rectangle vu par la cam�ra.
INLINE AABB Camera_GetWorldView(Camera *self)
{
    return self->m_worldView;
}

/// @brief D�finit le rectangle vu par la cam�ra.
/// Les coordonn�es sont exprim�es dans le r�f�rentiel monde.
/// @param self la cam�ra.
/// @param worldView le rectangle.
INLINE void Camera_SetWorldView(Camera *self, AABB worldView)
{
    self->m_worldView = worldView;
}

/// @brief D�place le rectangle vu par la cam�ra.
/// Les coordonn�es sont exprim�es dans le r�f�rentiel monde.
/// @param self la cam�ra.
/// @param displacement le vecteur de translation (dans le r�f�rentiel monde).
void Camera_TranslateWorldView(Camera *self, Vec2 displacement);

/// @brief Renvoie la largeur en pixels de la cam�ra.
/// @param self la cam�ra.
/// @return La largeur en pixels de la cam�ra.
int Camera_GetWidth(Camera *self);

/// @brief Renvoie la hauteur en pixels de la cam�ra.
/// @param self la cam�ra.
/// @return La hauteur en pixels de la cam�ra.
int Camera_GetHeight(Camera *self);

/// @brief Renvoie le facteur d'�chelle par lequel il faut multiplier des
/// distances exprim�es dans le ref�rentiel monde pour obtenir des distances
/// exprim�es dans le r�f�rentiel vue (en pixels).
/// @param self la cam�ra.
/// @return Le facteur d'�chelle monde vers vue (en pixels).
float Camera_GetWorldToViewScale(Camera *self);

/// @brief Transforme des coordonn�es exprim�es dans le r�f�rentiel monde vers
/// le r�f�rentiel vue (en pixels).
/// @param[in] self la cam�ra.
/// @param[in] position la position d'un point dans le r�f�rentiel monde.
/// @param[out] x l'abscisse du point dans la vue (en pixels).
/// @param[out] y l'ordonn�e du point dans la vue (en pixels).
void Camera_WorldToView(Camera *self, Vec2 position, float *x, float *y);

/// @brief Transforme des coordonn�es exprim�e dans le r�f�rentiel de la vue
/// (en pixels) vers le r�f�rentiel monde.
/// @param[in] self camera la cam�ra.
/// @param[in] x l'abscisse d'un point dans le r�f�rentiel vue (en pixels).
/// @param[in] y l'ordonn�e d'un point dans le r�f�rentiel vue (en pixels).
/// @param[out] position la position du point dans le r�f�rentiel monde.
void Camera_ViewToWorld(Camera *self, float x, float y, Vec2 *position);
