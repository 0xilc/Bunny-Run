#include "Camera.h"
#include "string"


Camera::Camera()
{
    // Set up view matrix
    m_Position = glm::vec3(0, 10, 10);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 lookingPoint(0, 0, 0);
    m_ViewMatrix = glm::lookAt(m_Position, lookingPoint, up);
    
    // Construct projection matrix 100px x 100px as default.
    UpdateProjectionMatrix(100, 100);
}

Camera::Camera(int screenWidth, int screenHeight)
{
    // Set up view matrix
    m_Position = glm::vec3(0, 10, 10);
    glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 lookingPoint(0, 8, 0);
    m_ViewMatrix = glm::lookAt(m_Position, lookingPoint, up);

    // Set up projection matrix
    UpdateProjectionMatrix(screenWidth, screenHeight);
}

void Camera::UpdateProjectionMatrix(int screenWidth, int screenHeight)
{
	float fovyRad = (float)(90.0 / 180.0) * M_PI;
	m_ProjectionMatrix = glm::perspective(fovyRad, screenWidth / (float)screenHeight, 0.1f, 200.0f);
}
