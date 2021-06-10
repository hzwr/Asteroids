#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL/SDL.h>
#include "Math.h"
#include <GL/glew.h>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char *function, const char *file, int line);

class Renderer
{
public:
	Renderer(class Game *game);
	~Renderer();

	bool Initialize(float screenWidth, float screenHeight); // Initialize OpenGL
	void Shutdown();
	void UnloadData();

	void Draw();

	void AddSprite(class SpriteComponent *sprite);
	void RemoveSprite(class SpriteComponent *sprite);

	class Texture *GetTexture(const std::string &fileName);

	float GetScreenWidth() const { return mScreenWidth; }
	float GetScreenHeight() const { return mScreenHeight; }

private:
	// Map of textures loaded
	std::unordered_map<std::string, class Texture *> mTextures;

	// All the sprite components drawn
	std::vector<class SpriteComponent *> mSprites;

	class Game *mGame;
	// Width/height of screen
	float mScreenWidth;
	float mScreenHeight;

	// Window handle
	SDL_Window *mMainWindow;
	// OpenGL context handle
	SDL_GLContext mMainContext;
	unsigned int m_shaderProgram;

	// Animate square
	float m_r; // color's r value
	float m_increment;
};

