#include <iostream>

#include "control.h"
#include "../statics.h"
#include "../window.h"

// Control with no parent. Control will be positioned at the exact position on screen
Control::Control()
{
    _id = nextControlId++; // Set the ID of the control
	std::cout << "This ID: " << _id << std::endl;
}

// Control with parent. Control will be positioned relative to parent
Control::Control(Control* relativeToParent):
Control()
{
	// Set the position of the control relative to its parent
	this->_position.x += relativeToParent->_position.x;
	this->_position.y += relativeToParent->_position.y;
}

// Destroy the control and all of its child controls
Control::~Control()
{

}

// Set the size of the control
// TODO: implement
void Control::setSize(Size size)
{
    _size = size;
}

// Set the control's position
// TODO: implement
void Control::setPosition(Point point)
{
    _position = point;
}

// Set the control's background color
// TODO: implement
void Control::setBackgroundColor(rgba backgroundColor)
{
    _backgroundColor = backgroundColor;
}

// Set the control's background color
// TODO: implement
void Control::setBackgroundColor(Color backgroundColor)
{
	_backgroundColor = getRgbaFromColor(backgroundColor);
}

// Set the control's background color
// TODO: implement
void Control::setForegroundColor(rgba foregroundColor)
{
    _foregroundColor = foregroundColor;
}

// Set the control's background color
// TODO: implement
void Control::setForegroundColor(Color foregroundColor)
{
	_foregroundColor = getRgbaFromColor(foregroundColor);
}

// Set the control's background color
// TODO: implement
void Control::setborderColor(rgba borderColor)
{
    _borderColor = borderColor;
}

// Set the control's background color
// TODO: implement
void Control::setborderColor(Color borderColor)
{
	_borderColor = getRgbaFromColor(borderColor);
}

// Set the control and all of its child controls as added to the screen
// TODO: set all as added RECURSIVELY
void Control::setAllAsAdded()
{
	this->_hasBeenAdded = true; // Set the current control as added

	// Set all child controls as added
	for (auto control: _childControls)
	{
		control._hasBeenAdded = true;
	}
}

// Set the window that the control belongs to
void Control::setWindowId(int windowId)
{
	_windowId = windowId;
}

// Set the thickness of the control's border
void Control::setBorderThickness(int borderThickness)
{
	_borderThickness = borderThickness;
}

// Show the control
void Control::show()
{
    // TODO: implement
}

// Hide the control
void Control::hide()
{
    // TODO: implement
}

// Sort the list of controls by their z-index
void Control::sortControls(std::list<Control>* allControls)
{
	std::cout << "Sorting list of " << allControls->size() << " items!" << std::endl;

	if (allControls->size() > 1)
	{
		bool swapped = true;

		while (swapped)
		{
			swapped = false;

			for (auto it = allControls->begin(); it != allControls->end();)
			{
				if (*it != allControls->back())
				{
					auto currentControl = *it++; // Advance the iterator, so we can access the next control in the list
					auto nextControl = *it;

					//std::cout << "current control: " << currentControl.getId() << "; next control: " << nextControl.getId() << std::endl;

					if (nextControl.getZIndex() < currentControl.getZIndex())
					{
						std::swap(currentControl, nextControl);
						swapped = true;
					}
				}
			}
		}
	}
}

// Equality comparison using `==`. Retur true if both control's have the same ID, false otherwise
bool Control::operator==(const Control& other) const
{
	return this->_id == other._id;
}

// Equality comparison using `!=`. Return true if the control's do not have the same ID
bool Control::operator!=(const Control& other) const
{
	return (this->_id != other._id);
}

// Draw the control and all its children on the screen
void Control::drawAll(SDL_Window* window, SDL_Renderer* renderer)
{
	std::list<Control> allControls = getAllControls();
	sortControls(&allControls);

	// Iterate over each control in the list and draw it on the screen
	for (auto control: allControls)
	{
		drawControl(&control, window, renderer);
	}
}

// Get a list containing the current control and all of the control's child controls
std::list<Control> Control::getAllControls()
{
	// Maintain a list of all the controls
	std::list<Control> allControls = std::list<Control>();

	//for (auto )
	allControls.push_back(*this);

	// Add all the control's child controls to the list
	if (this->_childControls.size() > 0)
	{
		// Get a list of the control's child controls
		std::list<Control> childControls = this->getChildControls();

		// Iterate over each control's child controls and add it to the list
		for (auto childControl: childControls)
		{
			allControls.push_back(childControl);
			childControl._hasBeenAdded = true; // Set the current control as added to the sceen

			addChildControls(childControl, &allControls); // Draw all of the current control's child controls
		}
	}

	// Return the list of all the controls
	return allControls;
}

// Draw the child controls associated with a control
void Control::addChildControls(Control control, std::list<Control>* allControls)
{
	// Iterate over each child control in `control` recursively and draw it on the screen 
	for (auto childControl: control.getChildControls()) // Iterating over B2
	{
		// Draw the parent control
		allControls->push_back(childControl);
		//drawControl(&childControl, window, renderer); // B6
		childControl._hasBeenAdded = true; // Set the control as added to the screen

		// If there are child controls, draw them
		if (childControl.getChildControls().size() > 0)
		{
			addChildControls(childControl, allControls);
		}
	}
}

// Draw a control on the screen
// TODO: only draw control if its _visible field is set
void Control::drawControl(Control* control, SDL_Window* window, SDL_Renderer* renderer)
{
	// The control's coordinates
	Rectangle rect;
	rect.x = control->getPosition().x;
	rect.y = control->getPosition().y;
	rect.w = control->getSize().w;
	rect.h = control->getSize().h;

	// Set the ID of the window the control belongs to
	control->_windowId = SDL_GetWindowID(window);

	// Draw the control
	drawRect(renderer, rect, control->getBackgroundColor());

	// Draw a border around the control if it has a border set
	if (control->_hasBorder)
	{
		// Draw an outline around the button _borderThickness times
		for (int i=0; i<control->_borderThickness; i++)
		{
			Rectangle rect;
			rect.x = control->getPosition().x;
			rect.y = control->getPosition().y;
			rect.w = control->getSize().w;
			rect.h = control->getSize().h;

			// Determine the color of the border
			int r = control->getBorderColor().r;
			int g = control->getBorderColor().g;
			int b = control->getBorderColor().b;
			int a = control->getBorderColor().a;

			// Draw the border
			drawRectOutline(renderer, (rect.x+i), (rect.y+i), (rect.w-(i*2)), (rect.h-(i*2)), r, g, b, a);
		}
	}
}

// Add a child control to the control.
// `this` is the parent. `control` is the child.
// Set the parent ID of the child to the ID of the control the addControl() method is being called on
void Control::addControl(Control* control)
{
	// Draw the rectangle on the screen if it's parent control is already on the screen
	if (this->_hasBeenAdded)
	{
		// Create a rectangle from the control's dimension and position
		Rectangle rect;
		rect.x = control->getPosition().x;
		rect.y = control->getPosition().y;
		rect.w = control->getSize().w;
		rect.h = control->getSize().h;

		Window* window = Window::getWindows()[_windowId]; // Get the window to draw the control on
		SDL_Renderer* renderer = window->getRenderer(); // Get the renderer for the window
		drawRect(renderer, rect, control->getBackgroundColor()); // Draw the rectangle
		// Should be drawAllControls()
		SDL_RenderPresent(renderer); // Render the drawn control
	}

	control->_zIndex = this->_zIndex+1;
	control->_parentId = this->_id; // Set the parent ID of the child control
	_childControls.push_back(*control); // Add the control as a child control of the current control
}