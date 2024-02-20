#include "Ground.h"

Ground::Ground()
{
	m_Mesh.LoadFromOBJ("quad.obj");
	m_Shader.Load("ground.vert", "ground.frag");
	m_Scale = glm::vec3(20, 120, 1);
	m_Rotation = glm::vec3(-90, 0, 0);
	m_Position = glm::vec3(0, 0, -90);
	m_ShiftAmount = 0;
}

void Ground::Update(float deltaTime, float gameSpeed)
{
	m_ShiftAmount += deltaTime * gameSpeed * 55;
}

void Ground::Render(Camera& camera)
{
	m_Shader.Use();
	m_Shader.SetUniformMat4fv("model", GetModelMatrix());
	m_Shader.SetUniformMat4fv("view", camera.m_ViewMatrix);
	m_Shader.SetUniformMat4fv("projection", camera.m_ProjectionMatrix);
	m_Shader.SetUniform1f("offset", 550);
	m_Shader.SetUniform1f("scale", 0.1);
	m_Shader.SetUniform1f("shiftAmount", m_ShiftAmount);
	m_Mesh.Draw();
}

void Ground::Restart()
{
	m_Scale = glm::vec3(20, 120, 1);
	m_Rotation = glm::vec3(-90, 0, 0);
	m_Position = glm::vec3(0, 0, -90);
	m_ShiftAmount = 0;
}
