#ifndef _CONTROL_H
#define _CONTROL_H

#include <iostream>
#include <list>

#include "../drawing.h"
#include "../events/event.h"

#define DEFAULT_CONTROL_BACKGROUND_COLOR       rgba {211, 211, 211, 255}
#define DEFAULT_CONTROL_FOREGROUND_COLOR       rgba {0, 0, 0, 0}
#define DEFAULT_CONTROL_POSITION               {0, 0}
#define DEFAULT_CONTROL_SIZE                   {0, 0}
#define DEFAULT_CONTROL_BORDER_PIXEL_THICKNESS 1
#define DEFAULT_CONTROL_HAS_BORDER             true
#define DEFAULT_CONTROL_BORDER_COLOR           rgba {0, 0, 0, 0}

class Control : Event
{
    public:
        Control(); // Control with no parent
        Control(Control* relativeToParent); // Control with a parent
        ~Control();
        // Set the control's properties
        void setSize(Size size); // Set the controls' size
        void setPosition(Point point); // Set the control's position on the window
        void setBackgroundColor(rgba backgroundColor); // Set the control's foreground color
        void setBackgroundColor(Color backgroundColor); // Set the control's foreground color
        void setForegroundColor(rgba foregroundColor); // Set the control's background color
        void setForegroundColor(Color foregroundColor); // Set the control's background color
        void setborderColor(rgba borderColor); // Set the control's background color
        void setborderColor(Color borderColor); // Set the control's background color
        void setParentId(int parentId);
        void setWindowId(int windowId);
        void setBorderThickness(int borderThickness);
        inline void setAsAdded() { this->_hasBeenAdded = true; } // Sets the control as added to the screen
        inline void setHasBorder(bool hasBorder) { _hasBorder = hasBorder; } // Set whether the control has a border or no border
        void setAllAsAdded(); // Set the control and all of its children as added to the screen
        inline void setZIndex(int zIndex) { _zIndex = zIndex; }

        void show(); // Show the control, making it visible
        void hide(); // Hide the control, making it invisible
        void addControl(Control* control); // Add a child control to the current control
        void drawAll(SDL_Window* window, SDL_Renderer* renderer); // Draw the control and all of its children on the screen
        void addChildControls(Control control, std::list<Control>* allControls);
        static void drawControl(Control* control, SDL_Window* window, SDL_Renderer* renderer); // Draw the control on the screen
        std::list<Control> getAllControls(); // Get a list containing the control and all of its child controls
        std::list<Control> getAllControlsOnWindow(int windowId);
        void removeControl(Control); // Remove the control from the screen
        static void sortControls(std::list<Control>* allControls); // Sort the list of controls by their z-index
        bool operator==(const Control& other) const;
        bool operator!=(const Control& other) const;

        // Get the control's properties
        inline Size getSize() { return _size; } // Get the controls' size
        inline Point getPosition() { return _position; } // Get the control's position on the window
        inline rgba getBackgroundColor() { return _backgroundColor; } // Get the control's foreground color
        inline rgba getForegroundColor() { return _foregroundColor; } // Get the control's background color
        inline std::list<Control> getChildControls() { return _childControls; }
        inline int getId() { return _id; } // FOR TESTING: REMOVE IN FUTURE!
        inline int getParentId() { return _parentId; } // FOR TESTING: REMOVING IN FUTURE!
        inline int getBorderThickness() { return _borderThickness; } // Return the thickness of the border in pixels
        inline rgba getBorderColor() { return _borderColor; } // Return the color of the control's border
        inline int getZIndex() { return _zIndex; } // Get the Z index of the control on the screen
        inline bool isVisible() { return _isVisible; } // Determines the visibility of the controls

    private:
        std::list<Control> _childControls = std::list<Control>(); // This controls child controls

    protected:
        int _id, _parentId = -1; // The ID of the control and ID of parent Control it belongs to; -1 for no parent
        Point _position = DEFAULT_CONTROL_POSITION; // The position of the control on the window
        Size _size = DEFAULT_CONTROL_SIZE; // The size of the control
        rgba _backgroundColor = DEFAULT_CONTROL_BACKGROUND_COLOR; // The control's background color
        rgba _foregroundColor = DEFAULT_CONTROL_FOREGROUND_COLOR; // The control's foreground color
        bool _isVisible = true; // Determines the visibility of the control
        bool _hasBeenAdded = false;
        int _windowId; // The window that the control belongs to
        std::string _title; // The control's title
        int _borderThickness = DEFAULT_CONTROL_BORDER_PIXEL_THICKNESS; // How many pixels thick the border is
        bool _hasBorder = DEFAULT_CONTROL_HAS_BORDER; // Determines if the control has a border or not
        rgba _borderColor = DEFAULT_CONTROL_BORDER_COLOR; // The color of the control's border
        int _zIndex = 0; // Z index of control - which control is drawn above which controls
        Padding _padding = {0, 0, 0, 0}; // The control's margin
        // TODO: implement padding
};

#endif