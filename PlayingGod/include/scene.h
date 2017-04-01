////////////////////////////////////////////////////////////
//
// Playing God (3D Procedural World Generation) - Created by Jegor Kharlamov
// Created for Personal Final Year Project Year 3 at De Montfort University - Games Programming Course
//
// Playing God is a 3D world exploration game where the player can operate 
// a computer which generates new worlds based on selected parameters and creates a portal to them.
// The player can then travel through the portal to explore the worlds and search
// for powercells around the procedurally generated maps.
//
////////////////////////////////////////////////////////////
#ifndef SCENE_H
#define SCENE_H
#include <GLFW/glfw3.h>
#include <WorldReader.h>
#include <Freetype.h>

// Abstract class in order to set up world
class Scene
{
public:
	Scene() : m_animate(true) { }
	
	sf::Vector2i m_windowSize; // Dimensions of window

	bool m_bCloseToComputer;

    // Load in all texture and initilise shaders
    virtual void initScene(Freetype* Overlay) = 0;

	virtual void setMousePos(GLFWwindow *Gwindow, sf::Vector2i mousepos) = 0;


	// Run every frame
    virtual void update( float t ) = 0;

    // Draw Scene
    virtual void render() = 0;

	virtual void LoadMap(string FileLocation, bool isXML) = 0;

	// Aloow screen to be resized without causing rendering issues
	void resize(int w, int h)
	{
		m_windowSize.x = w;
		m_windowSize.y = h;

		gl::Viewport(0, 0, m_windowSize.x, m_windowSize.y);
	}
    
    void animate( bool value ) { m_animate = value; }
    bool animating() { return m_animate; }

	sf::Vector2i getWindowSize() { return m_windowSize; }
    
protected:
	bool m_animate;
};

#endif // SCENE_H
