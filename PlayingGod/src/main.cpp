#define GLM_FORCE_RADIANS

#include "PreHeader.h"


#include "gl_core_4_3.hpp"
#include <GLFW/glfw3.h>
#include "scene.h"
#include "World.h"
#include <Menu.h>
#include <iostream>

#include <string>
using std::string;

Scene *g_pScene; // Scene to be rendered on window
GLFWwindow *g_pWindow; // Window

Menu CreationMenu(1600,900); // Options Menu

bool g_bGameWindowFocused; // True if main window is infocus

// States of game
#define MAIN_MENU 0
#define NEW_WORLD_MENU 1
#define LOAD_WORLD_MENU 2
#define CLOSE_MENU 3


sf::Clock Timer;
int iState = 0;

//////////////////////////////////////////////////////////
////  Key press callback /////////////////////////////////
//////////////////////////////////////////////////////////
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	//if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
	//	if (scene)
	//		scene->animate(!(scene->animating()));
}

static void focus_callback(GLFWwindow *pWindow, int iFocused)
{
	// If the callback is true
	if (iFocused)
	{
		g_bGameWindowFocused = true; // Sets global boolean 'focused' to true
	}
	
										   
	else // Else the callback is false
	{
		g_bGameWindowFocused = false; // Sets global boolean 'focused' to false
	}
}

// Get mouse position every frame
static void cursor_callback(GLFWwindow *pWindow, double dX, double dY)
{
	// If window is focused
	if (g_bGameWindowFocused)
	{
		g_pScene->setMousePos(g_pWindow, sf::Vector2i(dX, dY)); // Set mouse position
	}
}

//////////////////////////////////////////////////////////
//// Window resize callback //////////////////////////////
//////////////////////////////////////////////////////////
static void resize_callback(GLFWwindow *pWindow, int iWidth, int iHeight)
{
	// Resizes the scene to match the window
	g_pScene->resize(iWidth, iHeight);
}


////////////////////////////////////////////////////////
//////  Create the scene and initialise ////////////////
////////////////////////////////////////////////////////
void initializeGL() {
	
	gl::ClearColor(0.5f, 0.5f, 0.5f, 1.0f); // Clear window

	sf::Vector2i windowSize; 
	glfwGetWindowSize(g_pWindow, &windowSize.x, &windowSize.y); // Establish window size

	g_pScene = new World(windowSize); // The scene = World

	g_pScene->initScene(); // Initiate scene
}

void glfwSetWindowPositionCenter(GLFWwindow* window) {
	// Get windows height and width
	int WindowX, WindowY;
	glfwGetWindowPos(window, &WindowX, &WindowY);

	int Width, Height;
	glfwGetWindowSize(window, &Width, &Height);

	// Get the distance needed to centre the window
	Width *= 0.5;
	Height *= 0.5;

	WindowX += Width;
	WindowY += Height;

	// Accounts for multiple monitors
	int CombinedMonitorsLength;
	GLFWmonitor **MonitorList = glfwGetMonitors(&CombinedMonitorsLength);

	if (MonitorList == NULL) {
		// No monitors detected
		return;
	}

	// Figure out which monitor the window is in
	GLFWmonitor *WindowOwner = NULL;
	int WindowOwnerX, WindowOwnerY, WindowOwnerWidth, WindowOwnerHeight;

	for (int i = 0; i < CombinedMonitorsLength; i++) {
		// Get the monitor position
		int MonitorX, MonitorY;
		glfwGetMonitorPos(MonitorList[i], &MonitorX, &MonitorY);

		// Create video mode to get monitors size
		int MonitorWidth, MonitorHeight;
		GLFWvidmode *monitor_vidmode = (GLFWvidmode*)glfwGetVideoMode(MonitorList[i]);

		if (monitor_vidmode == NULL) {
			// Video mode is required for width and height, so skip this monitor
			continue;

		}
		else {
			MonitorWidth = monitor_vidmode->width;
			MonitorHeight = monitor_vidmode->height;
		}

		// Set the WindowOwner to this monitor if the center of the window is within its bounding box
		if ((WindowX > MonitorX && WindowX < (MonitorX + MonitorWidth)) && (WindowY > MonitorY && WindowY < (MonitorY + MonitorHeight))) {
			WindowOwner = MonitorList[i];

			WindowOwnerX = MonitorX;
			WindowOwnerY = MonitorY;

			WindowOwnerWidth = MonitorWidth;
			WindowOwnerHeight = MonitorHeight;
		}
	}

	if (WindowOwner != NULL) {
		// Set the window position to the center of the monitor which launched the exe
		glfwSetWindowPos(window, WindowOwnerX + (WindowOwnerWidth * 0.5) - Width, WindowOwnerY + (WindowOwnerHeight * 0.5) - Height);
	}
}




////////////////////////////////////////////////////////
/////// Main loop  /////////////////////////////////////
////////////////////////////////////////////////////////
void mainLoop() {
	while (!glfwWindowShouldClose(g_pWindow) && !glfwGetKey(g_pWindow, GLFW_KEY_ESCAPE)) {
		// If button pressed open world creation menu (SFML_
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
		{
			g_bGameWindowFocused = false;
			sf::RenderWindow MenuWindow(sf::VideoMode(1600, 900), "World Creation");
			while (MenuWindow.isOpen())
			{
				sf::Event event;
				while (MenuWindow.pollEvent(event))
				{
					// Closes window if close button clicked
					if (event.type == sf::Event::Closed)
					{
						MenuWindow.close(); // Allows window to close when 'X' is pressed
					}
					if (event.type == sf::Event::MouseMoved)
					{
						CreationMenu.TakeMousePos(MenuWindow.mapPixelToCoords(Mouse::getPosition(MenuWindow)));
					}
					if (event.type == sf::Event::MouseButtonPressed)
					{
						if (event.key.code == sf::Mouse::Left)
						{
							CreationMenu.Click();
						}
					}
					MenuWindow.draw(CreationMenu);
					MenuWindow.display();
				}
				if (Timer.getElapsedTime().asSeconds() > 0.005)
				{
					if (iState == MAIN_MENU)
						switch (CreationMenu.update(Timer.getElapsedTime().asSeconds()))
						{
						case NEW_WORLD_MENU:
							break;

						case LOAD_WORLD_MENU:
							
							break;

						case CLOSE_MENU:
							MenuWindow.close();
							break;
						}
				}
			}
		}
		else
		// Render, update and send data for 3D camera control while creation menu not open
		{
			
			if (g_bGameWindowFocused)
			{
				glfwMakeContextCurrent(g_pWindow);
				g_pScene->update((float)glfwGetTime());
				g_pScene->render();
			}
			glfwSwapBuffers(g_pWindow);
			glfwPollEvents();

			// If window focused lock mouse to the middle of the screen
			if (g_bGameWindowFocused)
			{
				glfwSetCursorPos(g_pWindow, g_pScene->getWindowSize().x*0.5, g_pScene->getWindowSize().y*0.5);
			}
			
		}
	}
}

///////////////////////////////////////////////////////
//// resize ///////////////////////////////////////////
///////////////////////////////////////////////////////
void resizeGL(int w, int h) {
	g_pScene->resize(w, h);
}



///////////////////////////////////////////////////////
///////  Main  ////////////////////////////////////////
///////////////////////////////////////////////////////
int main(int argc, char *argv[])
{

	// Initialize GLFW
	if (!glfwInit()) exit(EXIT_FAILURE);


	// Select OpenGL 4.3 with a forward compatible core profile.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, FALSE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, TRUE);



	// Open the window
	string title = "Playing God";
	g_pWindow = glfwCreateWindow(1920, 1080, title.c_str(), NULL, NULL);
	if (!g_pWindow) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(g_pWindow);
	g_bGameWindowFocused = true;

	glfwSetWindowPositionCenter(g_pWindow);

	glfwSetKeyCallback(g_pWindow, key_callback);
	glfwSetWindowFocusCallback(g_pWindow, focus_callback);
	glfwSetCursorPosCallback(g_pWindow, cursor_callback);
	//glfwSetWindowPositionCenter(window);
	glfwSetWindowSizeCallback(g_pWindow, resize_callback);
	

	// Hide mouse position 
	glfwSetInputMode(g_pWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	

	// Load the OpenGL functions.
	gl::exts::LoadTest didLoad = gl::sys::LoadFunctions();

	if (!didLoad) {
		//Claen up and abort
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Initialization
	initializeGL();

	// Enter the main loop
	mainLoop();

	// Close window and terminate GLFW
	glfwTerminate();

	// Exit program
	exit(EXIT_SUCCESS);
}