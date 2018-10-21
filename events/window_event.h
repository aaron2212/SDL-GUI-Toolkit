#ifndef _WINDOW_EVENT_H
#define _WINDOW_EVENT_H

#include <SDL2/SDL.h>

#include "event.h"

class Window;

// WindowEvent class which contains all events that may be fired
// from a window, including all generic events from the Event base class
class WindowEvent : Event
{
    public:
        // Function pointers for event handlers which the user can set their own custom event handlers for
        void (*onClosed)() = NULL;  // When the user closes the window
        void (*onResized)() = NULL; // When the user resized the window

        // Default event handlers if the user has not set any. Called even if the user has setup
        // their own event handlers and are used to ensure everything is handled correctly
        void defaultOnClosed(int windowId);
        void defaultOnResized(Window* window);

        // Handles window events received from SDL_PollEvent and are called when the appropriate event is fired 
        void handleWindowEvent(SDL_Event event); 
};

#endif