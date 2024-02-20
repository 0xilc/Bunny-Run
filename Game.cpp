#include "Game.h"
#define _USE_MATH_DEFINES
#include <math.h>


Game::Game()
{
    m_WindowState = WindowState(1000, 800, "Bunny Run");
    Init();
    PrepareScene();
}

Game::~Game()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Game::Init()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    if (!glfwInit())
    {
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(m_WindowState.width, m_WindowState.height, "Bunny Run", NULL, NULL);

    if (!m_Window)
    {
        glfwTerminate();
        exit(-1);
    }

    glfwMakeContextCurrent(m_Window);
    // glfwSwapInterval(1);

    // Initialize GLEW to setup the OpenGL Function pointers
    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        exit(-1);
    }

    //char rendererInfo[512] = { 0 };
    //strcpy(rendererInfo, (const char*)glGetString(GL_RENDERER)); // Use strcpy_s on Windows, strcpy on Linux
    //strcat(rendererInfo, " - "); 
    //strcat(rendererInfo, (const char*)glGetString(GL_VERSION)); // Use strcpy_s on Windows, strcpy on Linux
    //glfwSetWindowTitle(m_Window, rendererInfo);
    glfwSetWindowUserPointer(m_Window, this);
    
    // glfw state
    glfwSwapInterval(1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// GLFW Events
	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
			Game* game = (Game*)glfwGetWindowUserPointer(window);
            game->m_WindowState.width = width;
            game->m_WindowState.height = height;
            // Update Projection matrix on resize
            game->m_Camera->UpdateProjectionMatrix(width, height);
            game->m_GameHUD->OnWindowResize(width, height);
        });
}

void Game::PrepareScene()
{
    m_GameHUD = std::make_shared<HUD>(m_WindowState.width, m_WindowState.height);
    m_Camera = std::make_shared<Camera>(m_WindowState.width, m_WindowState.height);
    m_Bunny = std::make_shared<Bunny>();
    m_Ground = std::make_shared<Ground>();
    m_Containers = std::make_shared<Containers>();

    m_GameState.gameSpeed = 1;
    m_GameState.hitStatus = NO_HIT;
    m_GameState.score = 0;
    m_GameState.time = 0;
    m_GameState.gameEnd = false;
}

void Game::Restart()
{
    // I know this is very inefficient, but I have finals.
    m_Bunny->Restart();
    m_Ground->Restart();
    m_Containers->Restart();
    m_Ground->Restart();
    m_GameState.gameSpeed = 1;
    m_GameState.hitStatus = NO_HIT;
    m_GameState.score = 0;
    m_GameState.time = 0;
    m_GameState.gameEnd = false;
}

void Game::Run()
{   
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    double currentFrame = glfwGetTime();
    double lastFrame = currentFrame;
    double deltaTime;

    // Main loop
    while (!glfwWindowShouldClose(m_Window))
    {
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        ProcessInput();

        glClearColor(0, 0, 0, 1);
        glClearDepth(1.0f);
        glClearStencil(0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        
        if (!m_GameState.gameEnd)
        {
            Update(deltaTime);
        }
        Render();
       
        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}

void Game::Update(float deltaTime)
{
    m_GameState.score += deltaTime * m_GameState.gameSpeed * 20;
    m_GameState.gameSpeed += deltaTime * 0.1;

    m_Ground->Update(deltaTime, m_GameState.gameSpeed);
    m_Bunny->Update(deltaTime, m_GameState.gameSpeed);
    m_Containers->Update(deltaTime, m_GameState.gameSpeed);
    
    m_Containers->CheckCollision(m_GameState.hitStatus, *m_Bunny);
    switch (m_GameState.hitStatus)
    {
        case NO_HIT:
            break;

        case HIT_RED:
            m_GameState.gameEnd = true;
            m_Bunny->Die();
            break;

        case HIT_YELLOW:
            m_GameState.score += 1000;
            //m_GameState.gameSpeed += 0.3;
            m_Bunny->TurnAround();
            break;

        default:
            break;
    }
}

void Game::Render()
{
    m_Ground->Render(*m_Camera);
    m_Bunny->Render(*m_Camera);
    m_Containers->Render(*m_Camera);
    m_GameHUD->Render(m_GameState.score, m_GameState.gameEnd);
}

void Game::ProcessInput()
{
    if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_Window, true);

    if (glfwGetKey(m_Window, GLFW_KEY_R) == GLFW_PRESS)
    {
        Restart();
    }
    if (!m_GameState.gameEnd)
    {
        if (glfwGetKey(m_Window, GLFW_KEY_A) == GLFW_PRESS)
        {
            m_Bunny->Move(DIRECTION_LEFT, m_GameState.gameSpeed);
        }
        
        if (glfwGetKey(m_Window, GLFW_KEY_D) == GLFW_PRESS)
        {
            m_Bunny->Move(DIRECTION_RIGHT, m_GameState.gameSpeed);
        }
    }
}
