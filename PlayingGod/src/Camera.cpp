#include "PreHeader.h"
#include "Camera.h"

Camera::Camera()
{
	// Sets Pos and View to default values
	CameraPos = glm::vec3(1.0f, 1.0f, 1.0);
	CameraView = glm::vec3(0.0f, 1.0f, 0.0f);
	if (!m_FootStep.loadFromFile("assets/sound/footstep.wav"));
	{
		sf::err() << "Failed to load music\n";
	}

	m_Sound.setBuffer(m_FootStep);
}

glm::vec3 Camera::GetCameraPos()
{
	return CameraPos;
}

glm::vec3 Camera::GetCameraView()
{
	return CameraView;
}

void Camera::setCameraPos(glm::vec3 NewCameraPos)
{
	CameraPos = NewCameraPos;
}

void Camera::setCameraView(glm::vec3 NewCameraView)
{
	CameraView = NewCameraView;
}

void Camera::ProcessUserInput(float yAngle, float zAngle) 
{
	glm::vec3 ViewVec = CameraView - CameraPos;
	
		// Allows looking around with the mouse
		CameraView.x = CameraPos.x + (float)cosf(-yAngle) * ViewVec.x - sinf(-yAngle) * ViewVec.z;
		CameraView.y += zAngle * 2.0f; // Allows looking up/down in the y axis
		CameraView.z = CameraPos.z + (float)sinf(-yAngle) * ViewVec.x + cosf(-yAngle) * ViewVec.z;
	
		float fMovementSpeed = 0.1f; // Fraction which limits movement speed
	
		// Sprint functionality
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::RShift)) 
		{
			fMovementSpeed = 0.5;
		}
		else
		{
			fMovementSpeed = 0.1;
		}

		// Forwards movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			CameraPos.x += ((float)cosf(-yAngle) * ViewVec.x - sinf(-yAngle) * ViewVec.z) * fMovementSpeed;
			CameraPos.z += ((float)sinf(-yAngle) * ViewVec.x + cosf(-yAngle) * ViewVec.z) * fMovementSpeed;
			CameraView.x += ((float)cosf(-yAngle) * ViewVec.x - sinf(-yAngle) * ViewVec.z) * fMovementSpeed;
			CameraView.z += ((float)sinf(-yAngle) * ViewVec.x + cosf(-yAngle) * ViewVec.z) * fMovementSpeed;
			PlayFootstepsSound();
		}
		// Backwards movement
		 if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			 CameraPos.x -= ((float)cosf(-yAngle) * ViewVec.x - sinf(-yAngle) * ViewVec.z) * fMovementSpeed;
			 CameraPos.z -= ((float)sinf(-yAngle) * ViewVec.x + cosf(-yAngle) * ViewVec.z) * fMovementSpeed;
			 CameraView.x -= ((float)cosf(-yAngle) * ViewVec.x - sinf(-yAngle) * ViewVec.z) * fMovementSpeed;
			 CameraView.z -= ((float)sinf(-yAngle) * ViewVec.x + cosf(-yAngle) * ViewVec.z) * fMovementSpeed;
			 PlayFootstepsSound();
		}
	
		 // Strafing right movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			CameraPos.z += ((float)cosf(-yAngle) * ViewVec.x - sinf(-yAngle) * ViewVec.z) * fMovementSpeed;
			CameraPos.x -= ((float)sinf(-yAngle) * ViewVec.x + cosf(-yAngle) * ViewVec.z) * fMovementSpeed;
			CameraView.z += ((float)cosf(-yAngle) * ViewVec.x - sinf(-yAngle) * ViewVec.z) * fMovementSpeed;
			CameraView.x -= ((float)sinf(-yAngle) * ViewVec.x + cosf(-yAngle) * ViewVec.z) * fMovementSpeed;
			PlayFootstepsSound();
		}

		// Strafing left movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			CameraPos.z -= ((float)cosf(-yAngle) * ViewVec.x - sinf(-yAngle) * ViewVec.z) * fMovementSpeed;
			CameraPos.x += ((float)sinf(-yAngle) * ViewVec.x + cosf(-yAngle) * ViewVec.z) * fMovementSpeed;
			CameraView.z -= ((float)cosf(-yAngle) * ViewVec.x - sinf(-yAngle) * ViewVec.z) * fMovementSpeed;
			CameraView.x += ((float)sinf(-yAngle) * ViewVec.x + cosf(-yAngle) * ViewVec.z) * fMovementSpeed;
			PlayFootstepsSound();
		}

}

void Camera::PlayFootstepsSound()
{
	if (m_Sound.getStatus() != sf::Sound::Playing)
	{
		m_Sound.setBuffer(m_FootStep);
		m_Sound.play();
	}
}