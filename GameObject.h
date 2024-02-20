#pragma once
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

struct Material
{
	Material() {};
	Material(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular)
		: ambient(_ambient), diffuse(_diffuse), specular(_specular) {};
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
};

class GameObject
{
public:
	GameObject();
	virtual ~GameObject() = default;

	virtual void Update(float deltaTime, float gameSpeed) = 0;
	virtual void Render(Camera& camera) = 0;

	glm::mat4 GetModelMatrix();
	
protected:
	// Object properties
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;

	Shader m_Shader;
	Material m_Material;
};