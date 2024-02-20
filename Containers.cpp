#include "Containers.h"

Containers::Containers()
{
	m_Containers.push_back(std::make_shared<Container>());
	m_Containers.push_back(std::make_shared<Container>());
	m_Containers.push_back(std::make_shared<Container>());
	m_Hittable = true;
	MoveFurther();
	Shuffle();
}

void Containers::Render(Camera& camera)
{
	for (auto container : m_Containers)
	{
		container->Render(camera);
	}
}

void Containers::Update(float deltaTime, float gameSpeed)
{
	if (m_DistanceFromCamera < -12)
	{
		Shuffle();
		MoveFurther();
	}
	else
	{
		for (auto container : m_Containers)
		{
			container->MoveCloser(deltaTime, gameSpeed);
		}
		m_DistanceFromCamera = -m_Containers[0]->GetPosition().z;
	}
}
void Containers::Restart()
{
	Shuffle();
	MoveFurther();
}

void Containers::Shuffle()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, 2);
	m_YellowBoxIndex = distrib(gen);				// random number
	for (int i = 0; i < 3; i++)
	{
		if (i == m_YellowBoxIndex)
		{
			m_Containers[i]->SetColor(TYPE_YELLOW);
		}
		else
		{
			m_Containers[i]->SetColor(TYPE_RED);
		}
	}
}

void Containers::MoveFurther()
{
	m_Containers[0]->SetPosition(glm::vec3(-15, 5, -180));
	m_Containers[1]->SetPosition(glm::vec3(0, 5, -180));
	m_Containers[2]->SetPosition(glm::vec3(15, 5, -180));
	m_DistanceFromCamera = 180;
	m_Hittable = true;
}

void Containers::CheckCollision(HitStatus& status, Bunny& bunny)
{
	int hitBoxIndex = -1;
	if (m_DistanceFromCamera < 3 && m_Hittable)
	{	
		float posx = bunny.GetPositionX();
		
		if (posx < -12) hitBoxIndex = 0;
		else if (posx < 4 && posx > -4) hitBoxIndex = 1;
		else if (posx > 12) hitBoxIndex = 2;
		if (hitBoxIndex != -1)					// we hit a box
		{
			m_Hittable = false;
			if (m_YellowBoxIndex == hitBoxIndex)
			{
				m_Containers[hitBoxIndex]->Disappear();
				status = HIT_YELLOW;
			}
			else
			{
				m_Containers[hitBoxIndex]->Disappear();
				status = HIT_RED;
			}
		}
		else
		{
			status = NO_HIT;
		}
	}
	else
	{
		status = NO_HIT;
	}
}


