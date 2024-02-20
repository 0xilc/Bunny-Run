#include "GameObject.h"

GameObject::GameObject()
	: m_Position(0.0f), m_Rotation(0.0f), m_Scale(1.0f) {}

glm::mat4 GameObject::GetModelMatrix()
{
	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, m_Position);

	model = glm::rotate(model, glm::radians(m_Rotation.x), glm::vec3(1, 0, 0)); // Rotate around the X axis
	model = glm::rotate(model, glm::radians(m_Rotation.y), glm::vec3(0, 1, 0)); // Rotate around the Y axis
	model = glm::rotate(model, glm::radians(m_Rotation.z), glm::vec3(0, 0, 1)); // Rotate around the Z axis

	model = glm::scale(model, m_Scale);
	return model;
};
