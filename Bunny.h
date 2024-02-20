#pragma once
#include "GameObject.h"
#include "Mesh.h"
enum MoveDir
{
	DIRECTION_LEFT,
	DIRECTION_RIGHT
};

class Bunny : public GameObject
{
public:
	Bunny();
	void Update(float deltaTime, float gameSpeed) override;
	void Render(Camera& shader) override;
	void Restart();
	
	void Move(MoveDir direction, float speed);
	float GetPositionX();
	void Die();
	void TurnAround();

private:
	double m_HopTimer;
	double m_HopSpeed;
	Mesh m_Mesh;

	bool m_TurnAroundAnim;
};

