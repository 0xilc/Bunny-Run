#pragma once
#include "GameObject.h"
#include "Mesh.h"

enum ContainerType
{
	TYPE_RED,
	TYPE_YELLOW
};

class Container : public GameObject
{
public:
	Container();
	void Update(float deltaTime, float gameSpeed) override;
	void Render(Camera& shader) override;

	void Disappear();
	void SetColor(ContainerType type);
	void SetPosition(glm::vec3 pos);
	glm::vec3 GetPosition();
	void MoveCloser(float deltaTime, float speed);


private:
	Mesh m_Mesh;
	glm::vec4 m_Color;
};
