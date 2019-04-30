#include "Engine.h"
#include "WindowManager.h"
#include <GLEW/glew.h>
#include "ModelManager.h"
#include "Defines.h"
#include "ShaderManager.h"

Engine::Engine()
{
	auto windowManager = WindowManager::GetInstance();
	auto modelManager = ModelManager::GetInstance();
	auto shaderManager = ShaderManager::GetInstance();

	float vertices[] = {
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};

	shaderManager->loadVertexShader("..\\Assets\\Shaders\\vertexShader.vert");
	shaderManager->loadFragmentShader("..\\Assets\\Shaders\\fragmentShader.frag");
	shaderManager->bindPrograms();

	m_model = modelManager->loadModelToVao(vertices, ARRAY_SIZE(vertices) / 3);

	m_is_running = true;
}


Engine::~Engine()
{

}

void Engine::getInput()
{
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			std::cout << "MEME" << std::endl;
			break;
		case SDL_QUIT:
			m_is_running = false;;
			break;
		default:
			break;
		}
	}
}

void Engine::update()
{

}

void Engine::render()
{
	auto pWindow = WindowManager::GetInstance()->getRenderWindow();

	glClearColor(0.0, 1.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, 512, 512);
	glUseProgram(ShaderManager::GetInstance()->getProgramID());

	WindowManager::GetInstance()->renderObject(m_model);

	SDL_GL_SwapWindow(pWindow);
}

void Engine::cleanUp()
{
	WindowManager::GetInstance()->cleanUp();
	ModelManager::GetInstance()->cleanUp();
}

bool Engine::isRunning()
{
	return m_is_running;
}