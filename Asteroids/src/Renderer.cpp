#include "Renderer.h"
#include "Texture.h"
#include "GameEngine/EntitySystem/Components/SpriteComponent.h"
#include "GameEngine/EntitySystem/Components/MeshComponent.h"
#include "GameEngine/EntitySystem/Components/ModelComponent.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Mesh.h"
#include "Model.h"


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
	,m_r(0.0f)
	,m_increment(0.05f)
{
}

Renderer::~Renderer()
{
	// Unbind shader
	m_spriteShader->Unbind();
	delete m_spriteShader;
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
	// Specify version 3.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
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

	// Request a depth buffer before creating the OpenGL context
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // 24-bit is a typical size


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

	// GL blend
	/*GLCall(glEnable(GL_BLEND));
	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));*/

	LoadShaders();

	//CreateSpriteVerts();


	// For shadows
	//-----------------------------------------------------------------------------


	unsigned int m_depthMapFBO;
	glGenFramebuffers(1, &m_depthMapFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, m_depthMapFBO);

	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

	// Create depth map texture
	unsigned int depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	//
	//

	return true;
}

void Renderer::CreateSpriteVerts()
{
	float positions[] = {
		// vertice position and texture coordinates
		// Most texture image formats start at the top row
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom left
		 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	// Create VAO and index buffer for the sprite quad
	// all sprites use the same vertices
	m_VAO = new VertexArray();


	// Specify vertex attributes
	VertexBufferLayout layout;
	layout.Push<float>(3); // position
	layout.Push<float>(3); // normal
	layout.Push<float>(2); // texture

	// Create and bind vertex buffer
	VertexBuffer vb(positions, 4 * layout.GetStride());

	// Bind VAO and add vertex buffer to it
	m_VAO->AddBuffer(vb, layout);

	// Bind array element buffer after VAO is bound
	// This information is stored in VAO
	// Note: If no VAO is bound, you cannot bind a index buffer object 
	IndexBuffer ib(indices, 6);

}

void Renderer::LoadShaders()
{
	//m_spriteShader = new Shader("res/shaders/Transform.shader");
	//m_spriteShader->Bind();
	//m_spriteShader->SetUniform4f("u_color", 0.8f, 0.3f, 0.8f, 1.0f);

	//m_spriteShader->SetUniform1i("u_texture", 0);
	//Matrix4 viewProj = Matrix4::CreateSimpleViewProj(1920, 1080);
	//m_spriteShader->SetUniformMat4f("u_viewProj", viewProj);

	m_meshShader = new Shader("res/shaders/Transform.shader");
	m_meshShader->Bind();
	m_view = Matrix4::CreateLookAt(
		Vector3::Zero,
		Vector3::UnitX,
		Vector3::UnitZ
	);
	m_proj = Matrix4::CreatePerspectiveFOV(
		Math::ToRadians(70.0f),
		mScreenWidth,
		mScreenHeight,
		1.0f,
		127.5f
	);
	m_meshShader->SetUniformMat4f("u_viewProj", m_view * m_proj);
}

void Renderer::Shutdown()
{
	SDL_GL_DeleteContext(mMainContext);
	SDL_DestroyWindow(mMainWindow);
}

void Renderer::UnloadData()
{
	for (auto model : m_models)
	{
		model.second->Unload();
		delete model.second;
	}
	m_models.clear();
}

void Renderer::Draw()
{

	// Set the clear color
	glClearColor(0.05f, 0.05f, 0.05f, 1.0f);

	// Clear the color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	//glDisable(GL_BLEND);

	m_meshShader->Bind();
	m_meshShader->SetUniformMat4f("u_viewProj", m_view * m_proj);
	SetLightUniforms(m_meshShader);
	//

	//for (auto mesh : m_meshComps)
	//{
	//	mesh->Draw(m_meshShader);
	//}

	for (auto model : m_modelComps)
	{
		model->Draw(m_meshShader);
	}



	// Draw all sprite components
	// Disable depth buffering
	//glDisable(GL_DEPTH_TEST);
	// Enable alpha blending on the color buffer
	//glEnable(GL_BLEND);
	/*glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);*/


	/*m_spriteShader->Bind();
	m_VAO->Bind();

	for (auto sprite : mSprites)
	{
		sprite->Draw(m_spriteShader);
	}*/

	//for (auto wireframe : mWireframes)
	//{
	//	wireframe->Draw(mRenderer);
	//}

	//GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

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

void Renderer::AddMeshComp(MeshComponent *mesh)
{
	m_meshComps.emplace_back(mesh);
}

void Renderer::RemoveMeshComp(MeshComponent *mesh)
{
	auto iter = std::find(m_meshComps.begin(), m_meshComps.end(), mesh);
	m_meshComps.erase(iter);
}

void Renderer::AddModelComp(ModelComponent *model)
{
	m_modelComps.emplace_back(model);
}

void Renderer::RemoveModelComp(ModelComponent *model)
{
	auto iter = std::find(m_modelComps.begin(), m_modelComps.end(), model);
	m_modelComps.erase(iter);
}

Texture *Renderer::GetTexture(const std::string &fileName)
{
	Texture *tex = nullptr;
	auto iter = m_textures.find(fileName);
	if (iter != m_textures.end())
	{
		tex = iter->second;
	}
	else
	{
		tex = new Texture();
		if (tex->Load(fileName))
		{
			m_textures.emplace(fileName, tex);
		}
		else
		{
			delete tex;
			tex = nullptr;
		}
	}
	return tex;
}

Mesh *Renderer::GetMesh(const std::string &fileName)
{
//	Mesh *m = nullptr;
//	auto iter = m_meshes.find(fileName);
//	if (iter != m_meshes.end())
//	{
//		m = iter->second;
//	}
//	else
//	{
//		m = new Mesh();
//		if (m->Load(fileName, this))
//		{
//			m_meshes.emplace(fileName, m);
//		}
//		else
//		{
//			delete m;
//			m = nullptr;
//		}
//	}
//	return m;

	return nullptr;
}

Model *Renderer::GetModel(const std::string &filePath)
{
	Model *m = nullptr;
	auto iter = m_models.find(filePath);
	if (iter != m_models.end())
	{
		m = iter->second;
	}
	else
	{
		m = new Model();
		if (m->Load(filePath, this))
		{
			m_models.emplace(filePath, m);
		}
		else
		{
			delete m;
			m = nullptr;
		}
	}
	return m;
}

void Renderer::SetLightUniforms(Shader *shader)
{
	// Get camera position in world-space coordiante by inverting the view matrix
	Matrix4 invView = m_view;
	invView.Invert();
	shader->SetUniform3fv("u_cameraPos", invView.GetTranslation());

	// Ambient light
	shader->SetUniform3fv("u_ambientLight", m_ambientLight);
	// Directional light
	shader->SetUniform3fv("u_dirLight.m_direction",
		m_dirLight.m_direction);
	shader->SetUniform3fv("u_dirLight.m_diffuseColor",
		m_dirLight.m_diffuseColor);
	shader->SetUniform3fv("u_dirLight.m_specColor",
		m_dirLight.m_specColor);

}
