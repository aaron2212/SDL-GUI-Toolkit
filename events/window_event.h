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
        void (*onClose)() = NULL;  // When the user closes the window
        void (*onResize)() = NULL; // When the user resized the window
        void (*onClick)() = NULL;

        // Default event handlers if the user has not set any. Called even if the user has setup
        // their own event handlers and are used to ensure everything is handled correctly
        void defaultOnClose(int windowId);
        void defaultOnResize(int windowId);
        void defaultOnClick();

        // Handles window events received from SDL_PollEvent and are called when the appropriate event is fired 
        void handleWindowEvent(SDL_Event event);
        void handleWindowClickEvent(SDL_Event event);
};

#endif