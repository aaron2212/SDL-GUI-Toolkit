#ifndef _DRAWING_H
#define _DRAWING_H

#include <SDL2/SDL.h>

// A color struct representing RGBA values
typedef struct _rgba
{
    int r;
    int g;
    int b;
    int a;
} rgba;

// List of predefined colors
enum Color
{
    Black,
    Brown,
    ControlColor,
    DarkBlue,
    DarkGray,
    DarkGreen,
    Gray,
    LightBlue,
    LightGray,
    LightGreen,
    Orange,
    Peach,
    Pink,
    Purple,
    Red,
    Yellow,
    White,
};

// Represents a point (x, y) on the screen
typedef struct point
{
    int x;
    int y;
} Point;

// Represents the size (width, height) of the control
typedef struct size
{
    int w;
    int h;
} Size;

// A rectangle. Contains the rectangle's X and Y cooridnates (top left), and its width and height
typedef struct rectangle
{
    int x;
    int y;
    int w;
    int h;
} Rectangle;

// The margin for the control
typedef struct padding
{
    int left;
    int top;
    int right;
    int bottom;
} Padding;

// Returns an RGBA color from a Color enum value
rgba getRgbaFromColor(Color color);

// Draw a rectagle
void drawRect(SDL_Renderer* renderer, int x, int y, int w, int h, int r, int g, int b, int a); // The actual drawing function
void drawRect(SDL_Renderer* renderer, Rectangle rect, rgba color); // Helper function which passes its extracted arguments to drawRect() above
void drawRect(SDL_Renderer* renderer, Rectangle rect, Color color); // Helper function which passes its extracted arguments to drawRect() above

// Draw a rectangle outline
void drawRectOutline(SDL_Renderer* renderer, int x, int y, int w, int h, int r, int g, int b, int a); // The actual drawing function
void drawRectOutline(SDL_Renderer* renderer, Rectangle rect, rgba color); // Helper function which passes its extracted arguments to drawRectOutline() above
void drawRectOutline(SDL_Renderer* renderer, Rectangle rect, Color color); // Helper function which passes its extracted arguments to drawRectOutline() above

// Redraws each control on the screen and sets the background color of the window again
void redrawScreen(int windowId);

#endif