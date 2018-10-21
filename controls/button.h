#ifndef _BUTTON_H
#define _BUTTON_H

#include <iostream>

#include "control.h"
#include "../drawing.h"

class Button : public Control
{
    public:
        Button(std::string text, int x, int y, int w, int h);
        Button(std::string text, int x, int y, int w, int h, Control* parentControl);
        //Button(std::string text, int x, int y, int w, int h, rgba foreColor);
        //Button(std::string text, int x, int y, int w, int h, rgba foreColor, rgba backColor);
        Button(std::string text, Point position, Size size);
        Button(std::string text, Point position, Size size, Control* parentControl);
        //Button(std::string text, Point position, Size size, rgba foreColor);
        //Button(std::string text, Point position, Size size, rgba foreColor, rgba backColor);

        // Get the button's properties
        inline std::string getText() { return _text; }

        // Set the button's properties
        void setText(std::string);
    
    private:
        std::string _text;
};

#endif