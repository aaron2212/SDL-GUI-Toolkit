#ifndef _WINDOW_H
#define _WINDOW_H

#include <SDL2/SDL.h>
#include <iostream>
#include <list>
#include <map>

#include "controls/control.h"
#include "drawing.h"
#include "events/window_event.h"

// Different flags which can be passed to the SDL_CreateWindow function.
// All the flags are simplified versions of the ones provided by SDL,
// and so are compatible with all SDL functions

#define FULLSCREEN 		   				SDL_FULLSCREEN
#define FULLSCREEN_DESKTOP 				SDL_FULLSCREEN_DESKTOP
#define SHOWN 			   				SDL_WINDOW_SHOWN
#define HIDDEN 			   				SDL_WINDOW_HIDDEN
#define BORDERLESS 		   				SDL_WINDOW_BORDERLESS
#define RESIZABLE 		   				SDL_WINDOW_RESIZABLE
#define MINIMIZED 		   				SDL_WINDOW_MINIMIZED
#define MAXIMIZED 		   				SDL_WINDOW_MAXIMIZED
#define INPUT_GRABBED 	   				SDL_WINDOW_INPUT_GRABBED
#define INPUT_FOCUS   	   				SDL_WINDOW_INPUT_FOCUS
#define MOUSE_FOCUS 	  				SDL_WINDOW_MOUSE_FOCUS
#define CENTERED 		   				SDL_WINDOWPOS_CENTERED

#define DEFAULT_WINDOW_BACKGROUND_COLOR rgba {200, 200, 200, 255}

class Window : public WindowEvent
{
	public:
		Window(); // Default constructor needed for map
		Window(std::string title, int x, int y, int width, int height); // Create the window
		~Window(); // Destroys the window and the renderer

		int init(); // Initialize SDL and setup the window and renderer

		// Used for setting a certain value pertaining to the current window
		void setBackgroundColor(int r, int g, int b, int a); // Used when passing in custom RGBA values
		void setBackgroundColor(rgba rgbaColor); // Used when passing in an rgba struct
		void setBackgroundColor(Color color); // Used for setting a predefined Color
		void setTitle(const char* title); // Set the window's title
		void setResizable(bool isResizable); // Set the window to resizable or not
		void setMinimumSize(Size size); // TODO: implement

		// Used for determining a value pertaining to the current window
		static int getNumberOfWindows(); // Return the number of windows currently on screen
		static std::map<int, Window*> getWindows(); // Return the map of windows (id, Window)
		inline SDL_Renderer* getRenderer() { return _renderer; } // Return the renderer used by the window
		inline std::list<Control*> getControls() { return _controls; } // Return the list of controls on the current window
		rgba getBackgroundColor() { return _backgroundColor; }; // Return the background color of the window
		inline Window getWindow() { return *this; } // Return the Window object
		inline int getWindowId() { return _id; } // Return the window's ID
		std::list<Control*> getAllControls(); // Get all the controls and child controls that have been added to the windoww
		void addChildControls(Control* control, std::list<Control*>* allControls);
		void deleteControls(Control* control);
		void deleteChildControls();
		inline std::string getTitle() { return _title; } // Return the window's title

		bool isResizable(); // Determines whether the window is resizable or not
		bool isVisible(); // Determines whether the window is hidden or not

		void redrawWindow(Window* window); // Redraw the background color of the window and all of its controls
		void hide(); // Hide the window
		void show(); // Show the window
		void addControl(Control* control); // Add a control to the window
		void removeControl(Control control); // Remove a control from the window
	
	private:
		int _id;
		std::string _title; // The window's title displayed in the title bar
		int _x, _y; // The x and y coordinates of the window's position
		int _width, _height; // The width and height of the window
		SDL_Window* _window = nullptr; // The actual window that will be opened
		SDL_Renderer* _renderer = nullptr; // Used for rendering stuff on the window

		// Holds the current background color of the window
		rgba _backgroundColor = DEFAULT_WINDOW_BACKGROUND_COLOR; // The window's background color
		bool _isResizable = true; // Holds a value indicating whether the window is resizable or not
		bool _isVisible = false; // Determines if the window is visible

		std::list<Control*> _controls = std::list<Control*>(); // A list of controls on the current window
};

#endif