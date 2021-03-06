#include "program.h"
#include "statics.h"
#include "window.h"

// No comand line arguments passed
Program::Program()
{
}

// Command line arguments passed
Program::Program(int argc, char** argv)
: _argc(argc),
  _argv(argv)
{
}

// Run the program
void Program::run()
{
	// Continue to poll events as long as their are windows running
	while (Window::getNumberOfWindows() > 0)
	{
		pollEvent(); // Listen for events
	}

	// Quit SDL, essentially quitting the entire application, since there are no windows left on the screen
	SDL_Quit();
}

// Poll for events using the first Window object in the windows map
void Program::pollEvent()
{
	SDL_Event event;

	// Poll for the event and handle it
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			// Handle events to do with windows
			case SDL_WINDOWEVENT:
				windows.begin()->second->handleWindowEvent(event);
				break;
			// Handle mouse click events
			case SDL_MOUSEBUTTONDOWN:
				windows.begin()->second->handleWindowClickEvent(event);
				break;
		}
	}
}