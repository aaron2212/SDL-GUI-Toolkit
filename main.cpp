#include <iostream>
#include <SDL2/SDL.h>

#include "controls/button.h"
#include "drawing.h"
#include "program.h"
#include "window.h"

using namespace std;

void func();

int main(int argc, char** argv)
{
	// Create the program
	Program program;

	// Create windows. (title, x, y, width, height)
	Window mainWindow("My Window", CENTERED, CENTERED, 640, 480);
	//cout << "djeawf: " << windows.size() << endl;
	//Window window2("My 2nd Window", CENTERED, CENTERED, 320, 240);
	//Window window3("My 3rd Window", CENTERED, CENTERED, 500, 400);

	// Custom onClosed event handler for mainWindow
	mainWindow.onClosed = func;

	// Set the main window's background color
	mainWindow.setBackgroundColor(Color::Orange);
	//window3.setBackgroundColor(Color::LightBlue);
	//window2.setTitle("Hello, world!");

	// Create buttons
	Button button0("button0", 0, 0, 70, 30); // ID=0
	Button button1("button1", 50, 20, 70, 30); // ID=1
	Button button2("button2", 70, 0, 70, 30); // ID=2
	//Button button3("button3", 70, 30, 70, 30); // ID=3; pId=2
	//Button button4("button4", 60, 20, 70, 30);
	//button0.setBackgroundColor(Color::Purple);
	button1.setBackgroundColor(Color::Red);
	button1.setZIndex(2);
	//button2.setBackgroundColor(Color::DarkBlue);
	//button4.setBackgroundColor(Color::Red);

	// CHILD HAS Z-INDEX +1 OF PARENT
	mainWindow.addControl(button0);
	mainWindow.addControl(button1);
	mainWindow.addControl(button2);

	//mainWindow.removeControl(button4);
	
	//mainWindow.addControl(&button3);

	// Run the program
	program.run();

	return 0;
}

void func()
{
	//std::cout << "Called by a function pointer!" << std::endl;
}