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

// Precompiled Header in order to include commonly used libraries
#pragma once

//#define GLM_FORCE_RADIANS

#include <stdio.h>
#include <tchar.h>

#include "../libraries/glm/glm/glm.hpp"
#include "../libraries/glm/glm/gtc/matrix_transform.hpp"
#include "../libraries/glm/glm/gtc/type_ptr.hpp"

#include <SFML\Graphics.hpp>
#include "gl_core_4_3.hpp"
#include <GLFW/glfw3.h>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include <algorithm>

#define _USE_MATH_DEFINES
#include <cmath>

