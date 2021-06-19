#include "Renderer.h"
#include "Texture.h"
#include "SpriteComponent.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Shader.h"

void GLClearError()
{
	// Clear errors
	while (glGetError() != GL_NO_ERROR);

}

bool GLLogCall(const char *function, const char *file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << ") " << function << " Line " << line << std::endl;
		return false;
	}

	return true;
}

Renderer::Renderer(Game *game)
	:mGame(game)
	,m_shaderProgram(0)
	,m_r(0.0f)
	,m_increment(0.05f)
{
}

Renderer::~Renderer()
{
}

bool Renderer::Initialize(float screenWidth, float screenHeight)
{
	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	// Use OpenGL's core profile
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// Specify version 4.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// Request a color buffer with 8-bits per RGBA channel
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// Enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// Force OpenGL to use hardware acceleration
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mMainWindow = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		static_cast<int>(mScreenWidth), static_cast<int>(mScreenHeight), SDL_WINDOW_OPENGL);
	if (!mMainWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	// Create OpenGL context and attach it to our window
	mMainContext = SDL_GL_CreateContext(mMainWindow);

	/* This makes our buffer swap synchronized with the monitor's vertical refresh */
	//SDL_GL_SetSwapInterval(1);
	

	// Initialize GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}

	// On some platforms, GLEW will emit a benign error code,
	// so clear it
	glGetError();

	m_shader = new Shader("res/shaders/Basic.shader");
	m_shader->Bind();
	m_shader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

	return true;
}

void Renderer::Shutdown()
{
	// Unbind shader
	m_shader->Unbind();

	GLCall(glDeleteProgram(m_shaderProgram));
	SDL_GL_DeleteContext(mMainContext);
	SDL_DestroyWindow(mMainWindow);

	
}

void Renderer::Draw()
{
	// Set the clear color to black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Clear the color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	if (m_r > 1.0f)
	{
		m_increment = -0.05f;
	}
	else if (m_r < 0.0f)
	{
		m_increment = 0.05f;
	}

	m_r += m_increment;

	m_shader->SetUniform4f("u_Color", m_r, 0.3f, 0.8f, 1.0f);

	//for (auto sprite : mSprites)
	//{
	//	sprite->Draw(mRenderer);
	//}

	//for (auto wireframe : mWireframes)
	//{
	//	wireframe->Draw(mRenderer);
	//}

	GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

	// Swap the buffers
	SDL_GL_SwapWindow(mMainWindow);
	//TTF_Font *font = TTF_OpenFont("Assets/Carlito-Regular.ttf", 24);
	//if (font == nullptr)
	//{
	//	SDL_Log("Failed to load font");
	//}
}

void Renderer::AddSprite(SpriteComponent *sprite)
{
	int myDrawOrder = sprite->mDrawOrder;
	auto iter = mSprites.begin();
	for (;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->mDrawOrder)
		{
			break;
		}
	}
	mSprites.insert(iter, sprite);
}

void Renderer::RemoveSprite(SpriteComponent *sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

Texture *Renderer::GetTexture(const std::string &fileName)
{
	Texture *tex = nullptr;
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		tex = new Texture();
		if (tex->Load(fileName))
		{
			mTextures.emplace(fileName, tex);
		}
		else
		{
			delete tex;
			tex = nullptr;
		}
	}
	return tex;
}
