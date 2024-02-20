#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h>
#include "glm/glm.hpp"

class Shader
{
public:
	GLuint m_Program;

	Shader();
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();
	void Use();
	void Load(const char* vertexPath, const char* fragmentPath);


	// Uniform setters
	void SetUniform1f(const std::string& name, float f);
	void SetUniform3f(const std::string& name, const glm::vec3& vector);
	void SetUniformMat4fv(const std::string& name, const glm::mat4& matrix);


private:
	void checkCompileErrors(GLuint shader, std::string type);

};