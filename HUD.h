#pragma once
#include <iostream>
#include "string"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 
#include "Shader.h"
#include "map"
#include <ft2build.h>
#include FT_FREETYPE_H

struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // Size of glyph
    glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
    unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class HUD
{
public:

	HUD(int windowWidth, int windowHeight);

	void Render(int score, bool dead);

	void RenderText(const std::string& text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);
	void OnWindowResize(int newWidth, int newHeight);

private:
	Shader m_Shader;
	std::map<GLchar, Character> m_Characters;
	unsigned int VAO, VBO;
	int m_WindowHeight, m_WindowWidth;
	glm::mat4 m_ProjectionMatrix;
};