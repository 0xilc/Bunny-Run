#include "Bunny.h"

Bunny::Bunny()
{
	m_Mesh.LoadFromOBJ("bunny.obj");
	m_Shader.Load("bunny.vert", "bunny.frag");
	m_Scale = glm::vec3(1.5);
	m_Rotation = glm::vec3(0, -90, 0);
	m_Position = glm::vec3(0, 0.4, 0);
	m_HopTimer = 0;
	m_HopSpeed = 4;
	m_TurnAroundAnim = false;
}

void Bunny::Update(float deltaTime, float gameSpeed)
{
	// Hopping animation
	m_HopTimer += deltaTime * gameSpeed *2;
	if (m_HopTimer > 1) m_HopTimer = 0;
	float verticalPos = sin(m_HopTimer * M_PI)+ 1.5;
	m_Position.y = verticalPos;

	// Turn around
	if (m_TurnAroundAnim)
	{
		if (m_Rotation.y > 270)
		{
			m_Rotation.y = -90;
			m_TurnAroundAnim = false;
		}
		else
		{
			m_Rotation.y += deltaTime * gameSpeed * 250;
		}
	}
}

void Bunny::Render(Camera& camera)
{
	m_Shader.Use();
	m_Shader.SetUniformMat4fv("model", GetModelMatrix());
	m_Shader.SetUniformMat4fv("view", camera.m_ViewMatrix);
	m_Shader.SetUniformMat4fv("projection", camera.m_ProjectionMatrix);
	m_Shader.SetUniform3f("eyePos", camera.m_Position);
	m_Mesh.Draw();
}

void Bunny::Restart()
{
	m_Scale = glm::vec3(1.5);
	m_Rotation = glm::vec3(0, -90, 0);
	m_Position = glm::vec3(0, 0.4, 0);
	m_HopTimer = 0;
	m_HopSpeed = 4;
	m_TurnAroundAnim = false;
}

void Bunny::Move(MoveDir direction, float speed)
{
	if (direction == DIRECTION_LEFT)
	{
		if (m_Position.x > -17)
			m_Position = glm::vec3(m_Position.x - 0.2 * speed, m_Position.y, m_Position.z);
	}
	else
	{
		if(m_Position.x < 17)
			m_Position = glm::vec3(m_Position.x + 0.2 * speed, m_Position.y, m_Position.z);
	}
}

float Bunny::GetPositionX()
{
	return m_Position.x;
}

void Bunny::Die()
{
	m_Rotation = glm::vec3(-90, 0, -90);
}

void Bunny::TurnAround()
{
	m_TurnAroundAnim = true;
}
