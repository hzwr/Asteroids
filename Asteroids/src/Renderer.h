#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL/SDL.h>
#include "src/Vendor/Math.h"
#include <GL/glew.h>



//-----------------------------------------------------------------------------
// Error checking for OpenGL calls
//-----------------------------------------------------------------------------
#define ASSERT(x) if(!(x)) __debugbreak();

#define GLCall(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char *function, const char *file, int line);
//-----------------------------------------------------------------------------


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

	void AddMeshComp(class MeshComponent *mesh);
	void RemoveMeshComp(class MeshComponent *mesh);

	float GetScreenWidth() const { return mScreenWidth; }
	float GetScreenHeight() const { return mScreenHeight; }

	class Texture *GetTexture(const std::string &fileName);
	class Mesh *GetMesh(const std::string &fileName);

	void SetViewMatrix(const Matrix4 &view) { m_view = view; }


private:
	void Renderer::CreateSpriteVerts();
	void Renderer::LoadShaders();

	// Map of textures loaded
	std::unordered_map<std::string, class Texture *> m_textures;
	// Map of meshes loaded
	std::unordered_map<std::string, class Mesh *> m_meshes;

	// All the sprite components drawn
	std::vector<class SpriteComponent *> mSprites;
	class Shader *m_spriteShader;

	class Shader *m_meshShader;
	Matrix4 m_view;
	Matrix4 m_proj;

	std::vector<class MeshComponent *> m_meshComps;

	class VertexArray *m_VAO;

	class Game *mGame;
	// Width/height of screen
	float mScreenWidth;
	float mScreenHeight;

	// Window handle
	SDL_Window *mMainWindow;
	// OpenGL context handle
	SDL_GLContext mMainContext;
	// Animate square
	float m_r; // color's r value
	float m_increment;
};

