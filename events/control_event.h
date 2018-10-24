#ifndef _CONTROL_EVENT_H
#define _CONTROL_EVENT_H

#include <SDL2/SDL.h>

#include "event.h"

// ControlEvent class which contains all events related
// to all classes with a base class of Control.
// Includes all generic events from the Event class

class ControlEvent : Event
{
    void (*click)() = NULL; // Control clicked

    // Default event handlers called regardless of whether a customer event handler was specified
    void defaultOnClick();

    // Handle all control related events, received from SDL_PollEvent
    void handleControlEvent(SDL_Event event);
};

#endif