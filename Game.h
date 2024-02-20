#pragma once
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp> 
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> 

#include "Mesh.h"
#include "Camera.h"
#include "Shader.h"
#include "Ground.h"
#include "Bunny.h"
#include "Containers.h"
#include "HUD.h"

struct WindowState
{
	WindowState() {};
	WindowState(int _width, int _height, std::string _title) :width(_width), height(_height), title(_title) {}
	int width;
	int height;
	std::string title;
	float fps;
};

struct GameState
{
	double gameSpeed;
	double score;
	double time;
	bool gameEnd;
	HitStatus hitStatus;
};

class Game
{
public:
	Game();
	~Game();
	void Init();
	void Run();
	
	void Update(float deltaTime);
	void Render();

	void Restart();

	// Utility functions
	void ProcessInput();
	void PrepareScene();

private:
	// Window
	GLFWwindow* m_Window;
	WindowState m_WindowState;

	// Camera
	std::shared_ptr<Camera> m_Camera;

	GameState m_GameState;
	std::shared_ptr<HUD> m_GameHUD;

	// Game Objects
	std::shared_ptr<Bunny> m_Bunny;
	std::shared_ptr<Ground> m_Ground;
	std::shared_ptr<Containers> m_Containers;
};