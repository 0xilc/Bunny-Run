#include "Container.h"

Container::Container()
{
	m_Mesh.LoadFromOBJ("cube.obj");
	m_Shader.Load("container.vert", "container.frag");
	m_Scale = glm::vec3(2, 4, 2);
	m_Rotation = glm::vec3(0);
	m_Position = glm::vec3(0, 4.5, -10);
	m_Color = glm::vec4(0.7, 0.6, 0, 0.2);
}

void Container::Update(float deltaTime, float gameSpeed)
{
}


void Container::Render(Camera& camera)
{
	m_Shader.Use();
	m_Shader.SetUniformMat4fv("model", GetModelMatrix());
	m_Shader.SetUniformMat4fv("view", camera.m_ViewMatrix);
	m_Shader.SetUniformMat4fv("projection", camera.m_ProjectionMatrix);
	m_Shader.SetUniform3f("eyePos", camera.m_Position);
	m_Shader.SetUniform3f("kd", glm::vec3(m_Color.r, m_Color.g, m_Color.b));
	m_Shader.SetUniform1f("alpha", m_Color.a);
	m_Mesh.Draw();
}

void Container::Disappear()
{
	m_Color.a = 0;
}

void Container::SetColor(ContainerType type)
{
	if (type == TYPE_RED)
	{
		m_Color = glm::vec4(0.9, 0.1, 0.1, 1);
	}
	else
	{
		m_Color = glm::vec4(0.7, 0.6, 0, 1);
	}
}

void Container::SetPosition(glm::vec3 pos)
{
	m_Position = pos;
}

glm::vec3 Container::GetPosition()
{
	return m_Position;
}

void Container::MoveCloser(float deltaTime, float speed)
{
	m_Position.z += deltaTime * speed * 50;
}
