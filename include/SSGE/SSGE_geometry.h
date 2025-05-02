#ifndef __SSGE_GEOMETRY_H__
#define __SSGE_GEOMETRY_H__

#include "SSGE/SSGE_config.h"
#include "SSGE/SSGE_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Draws a line
 * \param x1 The x position of the first point
 * \param y1 The y position of the first point
 * \param x2 The x position of the second point
 * \param y2 The y position of the second point
 * \param color The color of the line
 */
SSGEDECL void SSGE_DrawLine(int x1, int y1, int x2, int y2, SSGE_Color color);

/**
 * Draws a rectangle
 * \param x1 The x position of the point at the top-left corner of the rectangle
 * \param y1 The y position of the point at the top-left corner of the rectangle
 * \param x2 The x position of the point at the bottom-right corner of the rectangle
 * \param y2 The y position of the point at the bottom-right corner of the rectangle
 * \param color The color of the rectangle
 */
SSGEDECL void SSGE_DrawRect(int x1, int y1, int x2, int y2, SSGE_Color color);

/**
 * Draws an ellipse
 * \param x The x position of the ellipse
 * \param y The y position of the ellipse
 * \param rx The x radius of the ellipse
 * \param ry The y radius of the ellipse
 * \param color The color of the ellipse
 */
SSGEDECL void SSGE_DrawCircle(int x, int y, int radius, SSGE_Color color);

/**
 * Draws a circle
 * \param x The x position of the circle
 * \param y The y position of the circle
 * \param radius The radius of the circle
 * \param color The color of the circle
 */
SSGEDECL void SSGE_DrawEllipse(int x, int y, int rx, int ry, SSGE_Color color);

/**
 * Draws a line with a specified thickness
 * \param x1 The x position of the first point
 * \param y1 The y position of the first point
 * \param x2 The x position of the second point
 * \param y2 The y position of the second point
 * \param color The color of the line
 * \param thickness The thickness of the line
 */
SSGEDECL void SSGE_DrawLineThick(int x1, int y1, int x2, int y2, SSGE_Color color, int thickness);

/**
 * Draws a rectangle with a specified thickness
 * \param x1 The x position of the point at the top-left corner of the rectangle
 * \param y1 The y position of the point at the top-left corner of the rectangle
 * \param x2 The x position of the point at the bottom-right corner of the rectangle
 * \param y2 The y position of the point at the bottom-right corner of the rectangle
 * \param color The color of the rectangle
 * \param thickness The thickness of the rectangle
 */
SSGEDECL void SSGE_DrawRectThick(int x1, int y1, int x2, int y2, SSGE_Color color, int thickness);

/**
 * Draws a circle with a specified thickness
 * \param x The x position of the circle
 * \param y The y position of the circle
 * \param radius The radius of the circle
 * \param color The color of the circle
 * \param thickness The thickness of the circle
 */
SSGEDECL void SSGE_DrawCircleThick(int x, int y, int radius, SSGE_Color color, int thickness);

/**
 * Draws an ellipse with a specified thickness
 * \param x The x position of the ellipse
 * \param y The y position of the ellipse
 * \param rx The x radius of the ellipse
 * \param ry The y radius of the ellipse
 * \param color The color of the ellipse
 * \param thickness The thickness of the ellipse
 */
SSGEDECL void SSGE_DrawEllipseThick(int x, int y, int rx, int ry, SSGE_Color color, int thickness);

/**
 * Fills a rectangle
 * \param x1 The x position of the point at the top-left corner of the rectangle
 * \param y1 The y position of the point at the top-left corner of the rectangle
 * \param x2 The x position of the point at the bottom-right corner of the rectangle
 * \param y2 The y position of the point at the bottom-right corner of the rectangle
 */
SSGEDECL void SSGE_FillRect(int x1, int y1, int x2, int y2, SSGE_Color color);

/**
 * Fills a circle
 * \param x The x position of the circle
 * \param y The y position of the circle
 * \param radius The radius of the circle
 * \param color The color of the circle
 */
SSGEDECL void SSGE_FillCircle(int x, int y, int radius, SSGE_Color color);

/**
 * Fills an ellipse
 * \param x The x position of the ellipse
 * \param y The y position of the ellipse
 * \param rx The x radius of the ellipse
 * \param ry The y radius of the ellipse
 * \param color The color of the ellipse
 */
SSGEDECL void SSGE_FillEllipse(int x, int y, int rx, int ry, SSGE_Color color);

/**
 * Draws geometry from a texture
 * \param texture The texture to draw
 * \param x The x position to draw the texture
 * \param y The y position to draw the texture
 */
SSGEDECL void SSGE_DrawGeometry(SSGE_Texture *texture, int x, int y);

/**
 * Create a line as a texture
 * \param name The name of the texture
 * \param x1 The x position of the first point
 * \param y1 The y position of the first point
 * \param x2 The x position of the second point
 * \param y2 The y position of the second point
 * \param color The color of the line
 * \return The texture id
 * \note The texture is stored internally and can be accessed by its name
 */
SSGEDECL uint32_t SSGE_CreateLine(char *name, int x1, int y1, int x2, int y2, SSGE_Color color);

/**
 * Create a rectangle as a texture
 * \param name The name of the texture
 * \param x1 The x position of the point at the top-left corner of the rectangle
 * \param y1 The y position of the point at the top-left corner of the rectangle
 * \param x2 The x position of the point at the bottom-right corner of the rectangle
 * \param y2 The y position of the point at the bottom-right corner of the rectangle
 * \param color The color of the rectangle
 * \return The texture id
 * \note The texture is stored internally and can be accessed by its name
 */
SSGEDECL uint32_t SSGE_CreateRect(char *name, int x1, int y1, int x2, int y2, SSGE_Color color);

/**
 * Create a circle as a texture
 * \param name The name of the texture
 * \param x The x position of the circle
 * \param y The y position of the circle
 * \param radius The radius of the circle
 * \param color The color of the circle
 * \return The texture id
 * \note The texture is stored internally and can be accessed by its name
 */
SSGEDECL uint32_t SSGE_CreateCircle(char *name, int x, int y, int radius, SSGE_Color color);

/**
 * Create an ellipse as a texture
 * \param name The name of the texture
 * \param x The x position of the ellipse
 * \param y The y position of the ellipse
 * \param rx The x radius of the ellipse
 * \param ry The y radius of the ellipse
 * \param color The color of the ellipse
 * \return The texture id
 * \note The texture is stored internally and can be accessed by its name
 */
SSGEDECL uint32_t SSGE_CreateEllipse(char *name, int x, int y, int rx, int ry, SSGE_Color color);

/**
 * Create a line with a specified thickness as a texture
 * \param name The name of the texture
 * \param x1 The x position of the first point
 * \param y1 The y position of the first point
 * \param x2 The x position of the second point
 * \param y2 The y position of the second point
 * \param color The color of the line
 * \param thickness The thickness of the line
 * \return The texture id
 * \note The texture is stored internally and can be accessed by its name
 */
SSGEDECL uint32_t SSGE_CreateLineThick(char *name, int x1, int y1, int x2, int y2, SSGE_Color color, int thickness);

/**
 * Create a rectangle with a specified thickness as a texture
 * \param name The name of the texture
 * \param x1 The x position of the point at the top-left corner of the rectangle
 * \param y1 The y position of the point at the top-left corner of the rectangle
 * \param x2 The x position of the point at the bottom-right corner of the rectangle
 * \param y2 The y position of the point at the bottom-right corner of the rectangle
 * \param color The color of the rectangle
 * \param thickness The thickness of the rectangle
 * \return The texture id
 * \note The texture is stored internally and can be accessed by its name
 */
SSGEDECL uint32_t SSGE_CreateRectThick(char *name, int x1, int y1, int x2, int y2, SSGE_Color color, int thickness);

/**
 * Create a circle with a specified thickness as a texture
 * \param name The name of the texture
 * \param x The x position of the circle
 * \param y The y position of the circle
 * \param radius The radius of the circle
 * \param color The color of the circle
 * \param thickness The thickness of the circle
 * \return The texture id
 * \note The texture is stored internally and can be accessed by its name
 */
SSGEDECL uint32_t SSGE_CreateCircleThick(char *name, int x, int y, int radius, SSGE_Color color, int thickness);

/**
 * Create an ellipse with a specified thickness as a texture
 * \param name The name of the texture
 * \param x The x position of the ellipse
 * \param y The y position of the ellipse
 * \param rx The x radius of the ellipse
 * \param ry The y radius of the ellipse
 * \param color The color of the ellipse
 * \param thickness The thickness of the ellipse
 * \return The texture id
 * \note The texture is stored internally and can be accessed by its name
 */
SSGEDECL uint32_t SSGE_CreateEllipseThick(char *name, int x, int y, int rx, int ry, SSGE_Color color, int thickness);

#ifdef __cplusplus
}
#endif

#endif // __SSGE_GEOMETRY_H__