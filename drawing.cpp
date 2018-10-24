#include <iostream>
#include <SDL2/SDL.h>

#include "drawing.h"
#include "statics.h"

// TODO: add more colors

// Return the RGBA values of a Color value
rgba getRgbaFromColor(Color color)
{
    rgba rgbaColor; // The RGBA color of the converted Color value

    switch (color)
	{
		case Black:
			rgbaColor = rgba {0, 0, 0, 255}; 		// Black
			break;
		case Brown:
			rgbaColor = rgba {165, 42, 42, 255}; 	// Brown
			break;
		case ControlColor:
			rgbaColor = rgba {173, 173, 173};		// A shade of gray for the default Control color
			break;
		case DarkBlue:
			rgbaColor = rgba {0, 0, 139, 255}; 	    // Dark blue
			break;
		case DarkGray:
			rgbaColor = rgba {169, 169, 169, 255};  // Dark gray
			break;
		case DarkGreen:
			rgbaColor = rgba {0, 100, 0, 255}; 	    // Dark green
			break;
		case Gray:
			rgbaColor = rgba {128, 128, 128};
			break;
		case LightBlue:
			rgbaColor = rgba {173, 216, 230, 255};  // Light blue
			break;
		case LightGray:
			rgbaColor = rgba {211, 211, 211, 255};  // Light gray
			break;
		case LightGreen:
			rgbaColor = rgba {144, 238, 144, 255};  // Light green
			break;
		case Orange:
			rgbaColor = rgba {255, 165, 0, 255}; 	// Orange
			break;
		case Peach:
			rgbaColor = rgba {255, 218, 185, 255};  // Peach
			break;
		case Pink:
			rgbaColor = rgba {255, 192, 203, 255};  // Pink
			break;
		case Purple:
			rgbaColor = rgba {128, 0, 128, 255}; 	// Purple
			break;
		case Red:
			rgbaColor = rgba {255, 0, 0, 255}; 	    // Red
			break;
		case Yellow:
			rgbaColor = rgba {255, 255, 0, 255}; 	// Yellow
			break;
		case White:
			rgbaColor = rgba {255, 255, 255, 255};  // White
			break;
    }

    // Return the converted Color value as an RGBA value
    return rgbaColor;
}

// Draw a rectangle on the window
void drawRect(SDL_Renderer* renderer, int x, int y, int w, int h, int r, int g, int b, int a)
{
    SDL_Rect* rect = new SDL_Rect {x, y, w, h}; // The rectangle to draw
    SDL_SetRenderDrawColor(renderer, r, g, b, a); // Set the color to draw the rectangle
    SDL_RenderFillRect(renderer, rect); // Draw the rectangle
	//std::cout << "Drawing rectangle with color: (" << r << ", " << g << ", " << b << ") at (" << x << ", " << y << ") -> (" << (x+w-1) << ", " << (y+h-1) << ")" << std::endl;
    SDL_RenderPresent(renderer);
}

// Helper method that accepts arguments for drawing a rectangle on the screen and then passes them to the actual drawRect() function
void drawRect(SDL_Renderer* renderer, Rectangle rect, rgba color)
{
    // Get the rectangle's geometry
    int x = rect.x;
    int y = rect.y;
    int w = rect.w;
    int h = rect.h;

    // Get the color to draw the rectangle
    int r = color.r;
    int g = color.g;
    int b = color.b;
    int a = color.a;

    // Draw the rectangle
    drawRect(renderer, x, y, w, h, r, g, b, a);
}

// Helper method that accepts arguments for drawing a rectangle on the screen and then passes them to the actual drawRect() function

void drawRect(SDL_Renderer* renderer, Rectangle rect, Color color)
{
    // Convert the given Color value to an RGBA value
    rgba rgbaColor = getRgbaFromColor(color);

    // Get the rectangle's geometry
    int x = rect.x;
    int y = rect.y;
    int w = rect.w;
    int h = rect.h;

    // Get the color to draw the rectangle
    int r = rgbaColor.r;
    int g = rgbaColor.g;
    int b = rgbaColor.b;
    int a = rgbaColor.a;

    // Draw the rectangle
    drawRect(renderer, x, y, w, h, r, g, b, a);
}

// Draw a rectangle on the window
void drawRectOutline(SDL_Renderer* renderer, int x, int y, int w, int h, int r, int g, int b, int a)
{
	SDL_Rect sdlRect = {x, y, w, h};

    SDL_SetRenderDrawColor(renderer, r, g, b, a); // Set the color to draw the rectangle
    SDL_RenderDrawRect(renderer, &sdlRect); // Draw the rectangle
    SDL_RenderPresent(renderer);
}

// Helper method that accepts arguments for drawing a rectangle on the screen and then passes them to the actual drawRect() function
void drawRectOutline(SDL_Renderer* renderer, Rectangle rect, rgba color)
{
    // Get the rectangle's geometry
    int x = rect.x;
    int y = rect.y;
    int w = rect.w;
    int h = rect.h;

    // Get the color to draw the rectangle
    int r = color.r;
    int g = color.g;
    int b = color.b;
    int a = color.a;

    // Draw the rectangle
    drawRectOutline(renderer, x, y, w, h, r, g, b, a);
}

// Helper method that accepts arguments for drawing a rectangle on the screen and then passes them to the actual drawRect() function

void drawRectOutline(SDL_Renderer* renderer, Rectangle rect, Color color)
{
    // Convert the given Color value to an RGBA value
    rgba rgbaColor = getRgbaFromColor(color);

    // Get the rectangle's geometry
    int x = rect.x;
    int y = rect.y;
    int w = rect.w;
    int h = rect.h;

    // Get the color to draw the rectangle
    int r = rgbaColor.r;
    int g = rgbaColor.g;
    int b = rgbaColor.b;
    int a = rgbaColor.a;

    // Draw the rectangle
    drawRectOutline(renderer, x, y, w, h, r, g, b, a);
}

// Redraw all of a control's child controls
void getChildControls(Control* control, std::list<Control*>* allControls)
{
	// Iterate over the control's child controls and draw each child control
	for (auto childControl: control->getChildControls())
	{
		allControls->push_back(childControl);

		// If the control has child controls, draw them too
		if (!childControl->getChildControls().empty())
		{
			getChildControls(childControl, allControls);
		}
	}
}

// Redraw all controls on the window and set its background color
void redrawScreen(int windowId)
{
	// The window to and renderer to redraw the controls onto
	Window* windowToRedraw = Window::getWindows()[windowId];
	SDL_Window* sdlWindow = SDL_GetWindowFromID(windowId);
	SDL_Renderer* sdlRenderer = SDL_GetRenderer(sdlWindow);

	// Set the window's background color again before redrawing each control
	rgba backgroundColor = windowToRedraw->getBackgroundColor();
	SDL_SetRenderDrawColor(sdlRenderer, backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
	SDL_RenderClear(sdlRenderer);
	SDL_RenderPresent(sdlRenderer);

	// The list of controls
	std::list<Control*> allControls = std::list<Control*>();

	// Iterate over all of this window's controls and redraw each control
	std::list<Control*> controls = windowToRedraw->getControls();
	
	for (auto& control: controls)
	{
		//std::cout << control->getName() << std::endl;
		allControls.push_back(control);

		// If the control has child controls, draw them too
		if (!control->getChildControls().empty())
		{
			getChildControls(control, &allControls);
		}
	}

	// Sort the controls by their z-index
	allControls.sort([](Control* current, Control* next) { return current->getZIndex() > next->getZIndex(); });
	allControls.reverse();
	
	// Draw each control in the list
	for (auto control: allControls)
	{
		Control::drawControl(control, sdlWindow, sdlRenderer);
	}
}