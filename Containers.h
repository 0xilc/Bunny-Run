#pragma once
#include "Container.h"
#include "vector"
#include "random"
#include "Bunny.h"
#include <memory>
enum HitStatus
{
	NO_HIT,
	HIT_RED,
	HIT_YELLOW
};

class Containers
{
public:
	Containers();
	
	void Render(Camera& camera);
	void Update(float deltaTime, float gameSpeed);
	void Restart();

	void Shuffle();
	void MoveFurther();
	void CheckCollision(HitStatus& status, Bunny& bunny);

private:
	std::vector<std::shared_ptr<Container>> m_Containers;
	int m_YellowBoxIndex;
	float m_DistanceFromCamera;
	bool m_Hittable;
};
