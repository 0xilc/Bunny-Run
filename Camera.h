#pragma once
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#define M_PI       3.14159265358979323846

class Camera
{
public:
	Camera();
	Camera(int screenWidth, int screenHeight);

	void UpdateProjectionMatrix(int width, int height);

	glm::vec3 m_Position;
	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix;
};