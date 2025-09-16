#ifndef __SSGE_GEOMETRY_H__
#define __SSGE_GEOMETRY_H__

#include "SSGE/SSGE_config.h"
#include "SSGE/SSGE_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Draw a line
 * \param x1 The x coordinate of the first point
 * \param y1 The y coordinate of the first point
 * \param x2 The x coordinate of the second point
 * \param y2 The y coordinate of the second point
 * \param color The color of the line
 */
SSGEAPI void SSGE_DrawLine(int x1, int y1, int x2, int y2, SSGE_Color color);

/**
 * Draw a rectangle
 * \param x1 The x coordinate of the point at the top-left corner of the rectangle
 * \param y1 The y coordinate of the point at the top-left corner of the rectangle
 * \param x2 The x coordinate of the point at the bottom-right corner of the rectangle
 * \param y2 The y coordinate of the point at the bottom-right corner of the rectangle
 * \param color The color of the rectangle
 */
SSGEAPI void SSGE_DrawRect(int x1, int y1, int x2, int y2, SSGE_Color color);

/**
 * Draw an ellipse
 * \param x The x coordinate of the ellipse
 * \param y The y coordinate of the ellipse
 * \param rx The x radius of the ellipse
 * \param ry The y radius of the ellipse
 * \param color The color of the ellipse
 */
SSGEAPI void SSGE_DrawCircle(int x, int y, int radius, SSGE_Color color);

/**
 * Draw a circle
 * \param x The x coordinate of the circle
 * \param y The y coordinate of the circle
 * \param radius The radius of the circle
 * \param color The color of the circle
 */
SSGEAPI void SSGE_DrawEllipse(int x, int y, int rx, int ry, SSGE_Color color);

/**
 * Draw a line with a specified thickness
 * \param x1 The x coordinate of the first point
 * \param y1 The y coordinate of the first point
 * \param x2 The x coordinate of the second point
 * \param y2 The y coordinate of the second point
 * \param color The color of the line
 * \param thickness The thickness of the line
 */
SSGEAPI void SSGE_DrawLineThick(int x1, int y1, int x2, int y2, SSGE_Color color, int thickness);

/**
 * Draw a rectangle with a specified thickness
 * \param x1 The x coordinate of the point at the top-left corner of the rectangle
 * \param y1 The y coordinate of the point at the top-left corner of the rectangle
 * \param x2 The x coordinate of the point at the bottom-right corner of the rectangle
 * \param y2 The y coordinate of the point at the bottom-right corner of the rectangle
 * \param color The color of the rectangle
 * \param thickness The thickness of the rectangle
 */
SSGEAPI void SSGE_DrawRectThick(int x1, int y1, int x2, int y2, SSGE_Color color, int thickness);

/**
 * Draw a circle with a specified thickness
 * \param x The x coordinate of the circle
 * \param y The y coordinate of the circle
 * \param radius The radius of the circle
 * \param color The color of the circle
 * \param thickness The thickness of the circle
 */
SSGEAPI void SSGE_DrawCircleThick(int x, int y, int radius, SSGE_Color color, int thickness);

/**
 * Draw an ellipse with a specified thickness
 * \param x The x coordinate of the ellipse
 * \param y The y coordinate of the ellipse
 * \param rx The x radius of the ellipse
 * \param ry The y radius of the ellipse
 * \param color The color of the ellipse
 * \param thickness The thickness of the ellipse
 */
SSGEAPI void SSGE_DrawEllipseThick(int x, int y, int rx, int ry, SSGE_Color color, int thickness);

/**
 * Fill a rectangle
 * \param x1 The x coordinate of the point at the top-left corner of the rectangle
 * \param y1 The y coordinate of the point at the top-left corner of the rectangle
 * \param x2 The x coordinate of the point at the bottom-right corner of the rectangle
 * \param y2 The y coordinate of the point at the bottom-right corner of the rectangle
 */
SSGEAPI void SSGE_FillRect(int x1, int y1, int x2, int y2, SSGE_Color color);

/**
 * Fill a circle
 * \param x The x coordinate of the circle
 * \param y The y coordinate of the circle
 * \param radius The radius of the circle
 * \param color The color of the circle
 */
SSGEAPI void SSGE_FillCircle(int x, int y, int radius, SSGE_Color color);

/**
 * Fill an ellipse
 * \param x The x coordinate of the ellipse
 * \param y The y coordinate of the ellipse
 * \param rx The x radius of the ellipse
 * \param ry The y radius of the ellipse
 * \param color The color of the ellipse
 */
SSGEAPI void SSGE_FillEllipse(int x, int y, int rx, int ry, SSGE_Color color);

/**
 * Draw geometry from a texture
 * \param texture The texture to draw
 * \param x The x coordinate at which the texture is drawn
 * \param y The y coordinate at which the texture is drawn
 */
SSGEAPI void SSGE_DrawGeometry(SSGE_Texture *texture, int x, int y);

/**
 * Create a line as a texture
 * \param id Where to store the id of the texture
 * \param name The name of the texture
 * \param x1 The x coordinate of the first point
 * \param y1 The y coordinate of the first point
 * \param x2 The x coordinate of the second point
 * \param y2 The y coordinate of the second point
 * \param color The color of the line
 * \return The texture
 * \note The texture is stored internally and can be accessed by its name
 */
SSGEAPI SSGE_Texture *SSGE_CreateLine(uint32_t *id, char *name, int x1, int y1, int x2, int y2, SSGE_Color color);

/**
 * Create a rectangle as a texture
 * \param id Where to store the id of the texture
 * \param name The name of the texture
 * \param x1 The x coordinate of the point at the top-left corner of the rectangle
 * \param y1 The y coordinate of the point at the top-left corner of the rectangle
 * \param x2 The x coordinate of the point at the bottom-right corner of the rectangle
 * \param y2 The y coordinate of the point at the bottom-right corner of the rectangle
 * \param color The color of the rectangle
 * \return The texture
 * \note The texture is stored internally and can be accessed by its name
 */
SSGEAPI SSGE_Texture *SSGE_CreateRect(uint32_t *id, char *name, int x1, int y1, int x2, int y2, SSGE_Color color);

/**
 * Create a circle as a texture
 * \param id Where to store the id of the texture
 * \param name The name of the texture
 * \param x The x coordinate of the circle
 * \param y The y coordinate of the circle
 * \param radius The radius of the circle
 * \param color The color of the circle
 * \return The texture
 * \note The texture is stored internally and can be accessed by its name
 */
SSGEAPI SSGE_Texture *SSGE_CreateCircle(uint32_t *id, char *name, int x, int y, int radius, SSGE_Color color);

/**
 * Create an ellipse as a texture
 * \param id Where to store the id of the texture
 * \param name The name of the texture
 * \param x The x coordinate of the ellipse
 * \param y The y coordinate of the ellipse
 * \param rx The x radius of the ellipse
 * \param ry The y radius of the ellipse
 * \param color The color of the ellipse
 * \return The texture
 * \note The texture is stored internally and can be accessed by its name
 */
SSGEAPI SSGE_Texture *SSGE_CreateEllipse(uint32_t *id, char *name, int x, int y, int rx, int ry, SSGE_Color color);

/**
 * Create a line with a specified thickness as a texture
 * \param id Where to store the id of the texture
 * \param name The name of the texture
 * \param x1 The x coordinate of the first point
 * \param y1 The y coordinate of the first point
 * \param x2 The x coordinate of the second point
 * \param y2 The y coordinate of the second point
 * \param color The color of the line
 * \param thickness The thickness of the line
 * \return The texture
 * \note The texture is stored internally and can be accessed by its name
 */
SSGEAPI SSGE_Texture *SSGE_CreateLineThick(uint32_t *id, char *name, int x1, int y1, int x2, int y2, SSGE_Color color, int thickness);

/**
 * Create a rectangle with a specified thickness as a texture
 * \param id Where to store the id of the texture
 * \param name The name of the texture
 * \param x1 The x coordinate of the point at the top-left corner of the rectangle
 * \param y1 The y coordinate of the point at the top-left corner of the rectangle
 * \param x2 The x coordinate of the point at the bottom-right corner of the rectangle
 * \param y2 The y coordinate of the point at the bottom-right corner of the rectangle
 * \param color The color of the rectangle
 * \param thickness The thickness of the rectangle
 * \return The texture
 * \note The texture is stored internally and can be accessed by its name
 */
SSGEAPI SSGE_Texture *SSGE_CreateRectThick(uint32_t *id, char *name, int x1, int y1, int x2, int y2, SSGE_Color color, int thickness);

/**
 * Create a circle with a specified thickness as a texture
 * \param id Where to store the id of the texture
 * \param name The name of the texture
 * \param x The x coordinate of the circle
 * \param y The y coordinate of the circle
 * \param radius The radius of the circle
 * \param color The color of the circle
 * \param thickness The thickness of the circle
 * \return The texture
 * \note The texture is stored internally and can be accessed by its name
 */
SSGEAPI SSGE_Texture *SSGE_CreateCircleThick(uint32_t *id, char *name, int x, int y, int radius, SSGE_Color color, int thickness);

/**
 * Create an ellipse with a specified thickness as a texture
 * \param id Where to store the id of the texture
 * \param name The name of the texture
 * \param x The x coordinate of the ellipse
 * \param y The y coordinate of the ellipse
 * \param rx The x radius of the ellipse
 * \param ry The y radius of the ellipse
 * \param color The color of the ellipse
 * \param thickness The thickness of the ellipse
 * \return The texture
 * \note The texture is stored internally and can be accessed by its name
 */
SSGEAPI SSGE_Texture *SSGE_CreateEllipseThick(uint32_t *id, char *name, int x, int y, int rx, int ry, SSGE_Color color, int thickness);

/**
 * Create a filled rectangle as a texture
 * \param id Where to store the id of the texture
 * \param name The name of the texture
 * \param x1 The x coordinate of the point at the top-left corner of the rectangle
 * \param y1 The y coordinate of the point at the top-left corner of the rectangle
 * \param x2 The x coordinate of the point at the bottom-right corner of the rectangle
 * \param y2 The y coordinate of the point at the bottom-right corner of the rectangle
 * \param color The color of the rectangle
 * \return The texture
 * \note The texture is stored internally and can be accessed by its name
 */
SSGEAPI SSGE_Texture *SSGE_CreateFillRect(uint32_t *id, char *name, int x1, int y1, int x2, int y2, SSGE_Color color);

/**
 * Create a filled circle as a texture
 * \param id Where to store the id of the texture
 * \param name The name of the texture
 * \param x The x coordinate of the circle
 * \param y The y coordinate of the circle
 * \param radius The radius of the circle
 * \param color The color of the circle
 * \return The texture
 * \note The texture is stored internally and can be accessed by its name
 */
SSGEAPI SSGE_Texture *SSGE_CreateFillCircle(uint32_t *id, char *name, int x, int y, int radius, SSGE_Color color);

/**
 * Create a filled ellipse as a texture
 * \param id Where to store the id of the texture
 * \param name The name of the texture
 * \param x The x coordinate of the ellipse
 * \param y The y coordinate of the ellipse
 * \param rx The x radius of the ellipse
 * \param ry The y radius of the ellipse
 * \param color The color of the ellipse
 * \return The texture
 * \note The texture is stored internally and can be accessed by its name
 */
SSGEAPI SSGE_Texture *SSGE_CreateFillEllipse(uint32_t *id, char *name, int x, int y, int rx, int ry, SSGE_Color color);

#ifdef __cplusplus
}
#endif

#endif // __SSGE_GEOMETRY_H__