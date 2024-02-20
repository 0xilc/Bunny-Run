#pragma once
#include "GameObject.h"
#include "Mesh.h"
class Ground : public GameObject
{
public:
	Ground();
	void Update(float deltaTime, float gameSpeed) override;
	void Render(Camera& shader) override;
	void Restart();

private:
	Mesh m_Mesh;
	float m_ShiftAmount;
};