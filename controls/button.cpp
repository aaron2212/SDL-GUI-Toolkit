#include <iostream>

#include "button.h"
#include "control.h"

using namespace std;

// Create a new Button with text, x and y position, and width and height
Button::Button(string text, int x, int y, int w, int h)
: Control()
{
    _text = text;
    _position = Point {x, y};
    _size = Size {w, h};
}

Button::Button(std::string text, int x, int y, int w, int h, Control* relativeToParent)
: Control(relativeToParent)
{
    _text = text;
    _position = Point {_position.x+x, _position.y+y};
    _size = Size {w, h};
}

// Create a new Button with text, a position and a size
Button::Button(std::string text, Point position, Size size)
: Control()
{
    _text = text;
    _position = position;
    _size = size;
}

Button::Button(std::string text, Point position, Size size, Control* parentControl)
: Control()
{

}

// Set the button's parent ID
// TODO: move to Control class
void Control::setParentId(int parentId)
{
    _parentId = parentId;
}