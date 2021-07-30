#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <SDL/SDL.h>
#include "math/Math.h"
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

struct DirectionalLight
{
	Vector3 m_direction;
	Vector3 m_diffuseColor;
	Vector3 m_specColor;
};

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

	void AddModelComp(class ModelComponent *model);
	void RemoveModelComp(class ModelComponent *model);

	float GetScreenWidth() const { return mScreenWidth; }
	float GetScreenHeight() const { return mScreenHeight; }

	class Texture *GetTexture(const std::string &fileName);
	class Mesh *GetMesh(const std::string &fileName);
	class Model *Renderer::GetModel(const std::string &filePath);

	unsigned int GetDepthMapFBO() const { return m_depthMapFBO; }

	void SetAmbientLight(const Vector3 &ambient) { m_ambientLight = ambient; }
	DirectionalLight &GetDirectionalLight() { return m_dirLight; }

	void SetViewMatrix(const Matrix4 &view) { m_view = view; }
	void SetLightUniforms(class Shader *shader);

private:
	void Renderer::CreateSpriteVerts();
	void Renderer::LoadShaders();

	// Map of textures loaded
	std::unordered_map<std::string, class Texture *> m_textures;
	// Map of meshes loaded
	std::unordered_map<std::string, class Mesh *> m_meshes;
	// Map of model loaded
	std::unordered_map<std::string, class Model *> m_models;


	// All the sprite components drawn
	std::vector<class SpriteComponent *> mSprites;
	class Shader *m_spriteShader;
	class Shader *m_meshShader;
	class Shader *m_simpleDepthShader;
	Matrix4 m_view;
	Matrix4 m_proj;

	// Lighting
	Vector3 m_ambientLight;
	DirectionalLight m_dirLight;

	std::vector<class MeshComponent *> m_meshComps;
	std::vector<class ModelComponent *> m_modelComps;

	class VertexArray *m_VAO;
	unsigned int m_depthMapFBO;

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

