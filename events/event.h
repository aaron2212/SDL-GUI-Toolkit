#ifndef _EVENT_H
#define _EVENT_H

// Base class for all types of events.
// All widgets and windows have these events
class Event
{
    public:
        void onGotFocus();
        void onKeyDown();
        void onKeyUp();
        void onKeyPress();
        void onLeave();
        void onMouseClick();
        void onMouseDoubleClick();
        void onMouseDown();
        void onMouseEnter();
        void onMouseHover();
        void onMouseLeave();
        void onMouseMove();
        void onMouseUp();
        void onMouseWheel();
        void onResize();
        void onTextChanged();
};

#endif