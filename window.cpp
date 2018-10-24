#include <iostream>
#include <map>
#include <SDL2/SDL.h>

#include "drawing.h"
#include "errors.h"
#include "statics.h"
#include "window.h"

using namespace std;

Window::Window()
{
}

// Accept the title for the window, x and y coordinates of the window's position, width and height
Window::Window(string title, int x, int y, int width, int height) :
	_title(title),
	_x(x),
	_y(y),
	_width(width),
	_height(height)
{
	// Get the return value from init(). An error code of 0 (ERROR_SUCCESS) means everything was OK.
	// An error code of > 0 means there was an error
	int result = init();

	// Determine the error code
	switch (result)
	{
		case ERROR_SUCCESS: // Created window and renderer and initialized SDL successfully
			SDL_Log("Created window with ID %d", SDL_GetWindowID(_window));
			break;
		case ERROR_INITIALIZATION_FAILED: // Failed to initialize SDL
			SDL_Log("Failed to initialize SDL");
			break;
		case ERROR_WINDOW_CREATION_FAILED: // Failed to create the window
			SDL_Log("Failed to create the window");
			break;
		case ERROR_RENDERER_CREATION_FAILED: // Failed to create the renderer
			SDL_Log("Failed to create the renderer");
	}
}

// Destroy all necessary components and quit SDL after the deletion of the Window object
Window::~Window()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
}

// Initialize the window
int Window::init()
{
	// Initialize SDL video. Return the appropriate error code
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		return ERROR_INITIALIZATION_FAILED;
	}

	// Create the window with the specified title, x and y coordinates, width and height. Set the window's state to 'shown'
	_window = SDL_CreateWindow(_title.c_str(), _x, _y, _width, _height, SDL_WINDOW_RESIZABLE);

	// The window could not be created. Return the appropriate error code
	if (_window == nullptr)
	{
		return ERROR_WINDOW_CREATION_FAILED;
	}

	// Create the renderer for the window. -1 is used so that SDL will choose the appropriate renderering engine based on the flags
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_SOFTWARE);

	// The renderer could not be created. Return the appropriate error code
	if (_renderer == nullptr)
	{
		return ERROR_RENDERER_CREATION_FAILED;
	}

	windows[SDL_GetWindowID(_window)] = this; // Add the window to the map of <id, Window> windows
	_id = SDL_GetWindowID(_window); // Set the ID field of this Window object

	setBackgroundColor(_backgroundColor);

	// Everything was initialized and created successfully
	return ERROR_SUCCESS;
}

// Handle all types of window related events
void WindowEvent::handleWindowEvent(SDL_Event event)
{
	Window* window = windows[event.window.windowID]; // Get the Window being closed, so we can access that Window's onClosed event handler
	int windowId = event.window.windowID; // The ID of the window that the event was fired on

	switch (event.window.event)
	{
		// Call the window closed handler, and pass in the ID of the window being closed
		case SDL_WINDOWEVENT_CLOSE:
			if (window->onClose != NULL) { window->onClose(); } // Call the onClosed event if the user has specified a function to handle the event
			window->defaultOnClose(windowId); // Call the default handler for closing windows
			break;
		// Call the window resize handler and pass in the Window that is being resized
		case SDL_WINDOWEVENT_RESIZED:
			if (window->onResize != NULL) { window->onResize(); } // Call the onResize event if the user has specified a functionto handle the event
			window->defaultOnResize(windowId); // Call the default handler for resizing windows
			break;
		// Determine which window has focus
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			currentWindowId = windowId;
			std::cout << "Current window ID: " << currentWindowId << std::endl;
			break;
	}
}

void WindowEvent::handleWindowClickEvent(SDL_Event event)
{
	int windowId = event.window.windowID;
	Window* window = windows[windowId];
	
	std::cout << "(" << event.button.x << ", " << event.button.y << ") -> " << event.window.windowID << std::endl;
}

// The default handler for handling the closing of a window
void WindowEvent::defaultOnClose(int windowId)
{
	// If the close button was clicked on the main window, close all the windows and quit the application
	if (windowId == windows.begin()->first)
	{
		// Iterate through each item in the map, and delete it by its key
		for (auto& [ID, window]: windows)
		{
			window->~Window(); // Call the Window's destructor, thus destroying the SDL window and renderer
			windows.erase(ID); // Remove the window from the list of windows
		}
	}
	// Otherwise, close the window that the user requested to close
	else
	{
		windows[windowId]->~Window(); // Call the Window's descructor
		windows.erase(windowId); // Remove the window by its ID (key) from the map
	}
}

// The default handler for handling the resizing of a window
void WindowEvent::defaultOnResize(int windowId)
{
	Window* window = windows[windowId];
	window->redrawWindow(window); // Redraw all the controls on the window
}


// Set the window's background color to an RGBA value
void Window::setBackgroundColor(int r, int g, int b, int a)
{
	SDL_SetRenderDrawColor(_renderer, r, g, b, a); // Set the color to change the window's background to
	SDL_RenderClear(_renderer); // Set the window's background color
	SDL_RenderPresent(_renderer); // Render the settings set above

	// Store the background color of the window in a variable
	_backgroundColor = {r, g, b, a};
	redrawScreen(_id);
}

// Set the background color of the window from the passed in rgba struct
void Window::setBackgroundColor(rgba rgbaColor)
{
	// Extract the RGBA values from the rgbaColor struct
	int r = rgbaColor.r;
	int g = rgbaColor.g;
	int b = rgbaColor.b;
	int a = rgbaColor.a;

	setBackgroundColor(r, g, b, a); // Set the background color of the window
}

// Set the window's background color to that of a predefined color
void Window::setBackgroundColor(Color color)
{
	// Convert the Color value to an RGBA value
	rgba rgbaColor = getRgbaFromColor(color);
	setBackgroundColor(rgbaColor);
}

// Set the window's title
void Window::setTitle(const char* title)
{
	SDL_SetWindowTitle(_window, title);
	_title = title;
}

// Set whether the window is resizable or not
void Window::setResizable(bool isResizable)
{
	SDL_SetWindowResizable(_window, (SDL_bool) isResizable);
}

// Return the number of currently open windows; this is the size of the map holding the Window objects
int Window::getNumberOfWindows()
{
	return windows.size();
}

// Return the map containing the currently open windows, which includes each window's ID
map<int, Window*> Window::getWindows()
{
	return windows;
}

// Determine whether the window is resiable or not
bool Window::isResizable()
{
	return _isResizable;
}

// Determine if the window is shown
bool Window::isVisible()
{
	return _isVisible;
}

// Redraws the window's background color and controls
// TODO: implement rest of method!
void Window::redrawWindow(Window* window)
{
	redrawScreen(_id); // Redraw all controls on the window with the specified ID
}

// Hide the window
void Window::hide()
{
	SDL_HideWindow(_window);
	_isVisible = false; // Set the window's state to invisible
}

// Show the window
void Window::show()
{
	SDL_ShowWindow(_window);
	_isVisible = true; // Set the window's state to visible

	redrawWindow(this); // Redraw the window's background color and controls
}

// Get a list of controls and child controls on the window
std::list<Control*> Window::getAllControls()
{
	// Stores a list of all controls on the screen to be returned after all the controls have been added to it
	std::list<Control*> allControls = std::list<Control*>();

	// Iterate over each control on the window and add it and child controls to the list
	for (auto control: _controls)
	{
		allControls.push_back(control);

		// If the control has any child controls, iterate through those
		// recursively and add them to the list
		if (!control->getChildControls().empty())
		{
			addChildControls(control, &allControls);
		}
	}

	// Return the list of controls
	return allControls;
}

// Get a list of the control's child controls 
void Window::addChildControls(Control* control, std::list<Control*>* allControls)
{
	// Iterate over each child control and add it to the list
	for (auto childControl: control->getChildControls())
	{
		allControls->push_back(childControl);

		// If the control has child controls, iterate through each child control
		// recursively and add it to the list
		if (!childControl->getChildControls().empty())
		{
			addChildControls(childControl, allControls);
		}
	}
}

// Delete the control and its child controls from the window
void Window::deleteControls(Control* control)
{
	_controls.remove(control);
}

// Add a control to the window
void Window::addControl(Control* control)
{
	_controls.push_back(control); // Add the control to the list

	control->setWindowId(_id);

	// Draw the current control and all of its children
	control->drawAll(_window);
}

// Remove a control from the window
void Window::removeControl(Control control)
{
	// Iterate through each control on the window
	for (auto windowControl: _controls)
	{
		std::cout << windowControl->getName() << "::" << control.getName() << std::endl;
		// If the control being removed is currently on the window, delete it
		if (windowControl->getId() == control.getId())
		{
			// Remove the control from the list of controls on this window
			_controls.remove(windowControl);

			std::cout << "Deleting " << control.getName() << std::endl;
			redrawScreen(_id);

			return;
		}
	}
}