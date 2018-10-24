#ifndef _STATICS_H
#define _STATICS_H

#include <iostream>

#include "window.h"

// A map containing the window's ID, along with that window's Window object
static std::map<int, Window*> windows = std::map<int, Window*>();

// The ID of the current window which has focus. ##NOT YET IMPLEMENTED##
static int currentWindowId;

// Maintains the ID to give to the next control
static int nextControlId = 0;

#endif