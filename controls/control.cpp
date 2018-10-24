#include <iostream>
#include <SDL2/SDL.h>

#include "control.h"
#include "../events/control_event.h"
#include "../statics.h"
#include "../window.h"

// Control with no parent. Control will be positioned at the exact position on screen
Control::Control()
{
    _id = nextControlId++; // Set the ID of the control
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

// Handles mouse click events.
// Calls any events handlers attached to mouse click events
void ControlEvent::handleControlEvent(SDL_Event event)
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

// Set the control's border color
// TODO: implement
void Control::setborderColor(Color borderColor)
{
	_borderColor = getRgbaFromColor(borderColor);
}

// Set the control and all of its child controls as added to the screen
// TODO: set all as added RECURSIVELY
void Control::setAllAsAdded()
{
	// Set all child controls as added
	for (auto control: getAllControls())
	{
		control->_hasBeenAdded = true;
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

// Set the z-index of the control, specifying if the element should be above or below other elements
void Control::setZIndex(int zIndex)
{
	// Set the current control's z-index
	this->_zIndex = zIndex;

	for (auto control: getAllControls())
	{
		if (control == this)
		{
			control->_zIndex = zIndex;
		}
	}

	// Redraw all the controls on the screen
	if (this->_hasBeenAdded)
	{
		redrawScreen(_windowId);
	}
}

// Draw the control and all its children on the screen
void Control::drawAll(SDL_Window* window)
{
	SDL_Renderer* renderer = SDL_GetRenderer(window);
	std::list<Control*> allControls = getAllControls();

	// Sort the control's according to their z-index
	allControls.sort([](Control current, Control next) { return current.getZIndex() > next.getZIndex(); });

	// Iterate over each control in the list and draw it on the screen
	for (auto control: allControls)
	{
		control->setAsAdded();
		drawControl(control, window, renderer);
	}
}

// Get a list containing the current control and all of the control's child controls
std::list<Control*> Control::getAllControls()
{
	// Maintain a list of all the controls
	std::list<Control*> allControls = std::list<Control*>();
	
	allControls.push_back(this);

	// Add all the control's child controls to the list
	if (!this->_childControls.empty())
	{
		// Get a list of the control's child controls
		std::list<Control*> childControls = this->getChildControls();

		// Iterate over each control's child controls and add it to the list
		for (auto childControl: childControls)
		{
			childControl->_hasBeenAdded = true; // Set the current control as added to the sceen
			allControls.push_back(childControl);

			addChildControls(childControl, allControls); // Draw all of the current control's child controls
		}
	}

	// Return the list of all the controls
	return allControls;
}

// Draw the child controls associated with a control
void Control::addChildControls(Control control, std::list<Control*> allControls)
{
	// Iterate over each child control in `control` recursively and draw it on the screen 
	for (auto& childControl: control.getChildControls())
	{
		// Draw the parent control
		allControls.push_back(childControl);
		//drawControl(&childControl, window, renderer); // B6
		childControl->_hasBeenAdded = true; // Set the control as added to the screen

		// If there are child controls, draw them
		if (!childControl->getChildControls().empty())
		{
			addChildControls(childControl, allControls);
		}
	}
}

// Draw a control on the screen
void Control::drawControl(Control* control, SDL_Window* window, SDL_Renderer* renderer)
{
	// Only draw control if its _visible field is set
	if (control->_isVisible)
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
}

// Add a child control to the control.
// `this` is the parent. `control` is the child.
// Set the parent ID of the child to the ID of the control the addControl() method is being called on
void Control::addControl(Control* control)
{
	// Draw the rectangle on the screen if it's parent control is already on the screen
	if (this->_hasBeenAdded)
	{
		control->_zIndex = this->_zIndex+1; // Set the control's z-index to 1 greater than that of the parent's z-index
		control->_parentId = this->_id; // Set the parent ID of the child control
		this->_childControls.push_back(control);
		redrawScreen(_windowId);
	}
	else
	{
		this->_childControls.push_back(control); // Add the control as a child control of the current control
	}
	
	control->_zIndex = this->_zIndex+1; // Set the control's z-index to +1 of the parent's z-index
	control->_parentId = this->_id; // Set the parent ID of the child control
}

// Remove the control and all of its controls
void Control::removeControl(Control* control)
{
	// "this" is button0
	// Iterate over each of the control's child controls
	
	// Iterator has to be used otherwise we get a segfault when
	// removing the control from the list
	for (auto it = _childControls.begin(); it != _childControls.end(); it++)
	{
		std::cout << (*it)->_name << "::" << control->_name << std::endl;

		if ((*it)->_id == control->_id)
		{
			// If the child control has more child controls, remove them from the list
			if (!(*it)->_childControls.empty())
			{
				removeChildControls((*it));
			}

			//std::cout << "YESSSSSSS!!!0;;->>" << childControl->getName() << std::endl;
			// "button0"'s _childControls
			it = _childControls.erase(it);
			redrawScreen(_windowId);
		}

		// Delete the child control
		//childControl->~Control();
	}
}

// Remove all of the control's child controls
void Control::removeChildControls(Control* control)
{
	std::cout << "abc123" << std::endl;
	for (auto childControl: control->_childControls)
	{
		if (!childControl->_childControls.empty())
		{
			removeChildControls(childControl);
		}

		_childControls.remove(childControl);
		//childControl->~Control();
	}
}