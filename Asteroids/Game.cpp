#include "Game.h"
#include <string>
#include <iostream>
#include <SDL/SDL_ttf.h>
#include "SDL/SDL_image.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "WireframeComponent.h"
#include "Player.h"
#include "Asteroid.h"
#include "ColliderComponent.h"
#include "Font.h"
#include "Renderer.h"
#include "VertexArray.h"
#include <GL/glew.h>

Game::Game()
:mWindow(nullptr)
,mRenderer(nullptr)
,mTicksCount(0)
,mIsRunning(true)
,start(nullptr)
,goal(nullptr)
,mIsPathFound(false)
,world(48,27,nullptr)
,mGameState(GameState::ERunning)
,mPlayer(nullptr)
,mIsUpdatingActors(false)
,mSpriteVerts(nullptr)
{

	
}

Game::~Game()
{

}

bool Game::Initialize()
{
	// Create renderer
	mRenderer = new Renderer(this);
	
	// Create an SDL Window
	mWindow = SDL_CreateWindow(
		"Game", // Window title
		100,	// Top left x-coordinate of window
		100,	// Top left y-coordinate of window
		1920,	// Width of window
		1080,	// Height of window
		0		// Flags (0 for no flags set)
	);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	

	if (!mRenderer->Initialize(1920.0f, 1080.0f))
	{
		SDL_Log("Failed to initialize renderer");
		delete mRenderer;
		mRenderer = nullptr;
		return false;
	}

	//// Create SDL renderer
	//mRenderer = SDL_CreateRenderer(
	//	mWindow, // Window to create renderer for
	//	-1,		 // Usually -1
	//	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	//);


	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Unable to initialize SDL_Image: %s", SDL_GetError);
		return false;
	}

	// Initialize SDL_ttf
	if (TTF_Init() != 0)
	{
		SDL_Log("Failed to initialize SDL_ttf");
		return false;
	}


	// Gameplay

	// Create player - ship
	mPlayer = new Player(this);
	mPlayer->mPosition = Vector2(810.0f, 500.0f);
	mPlayer->mScale = 1.5f;
	mPlayer->mRotation = Math::PiOver2;

	// Create asteroids
	const int numAsteroids = 20;
	for (int i = 0; i < numAsteroids; ++i)
	{
		new Asteroid(this);
	}

	CreateSpriteVerts();
	
	return true;

}

void Game::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput()
{
	//if (!mIsPathFound)
	//{
	//	//testBFS();
	//	world.SetStartNode(50);
	//	world.SetGoalNode(1295);
	//	world.FindPath();
	//	mIsPathFound = true;
	//}

	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			// If we get an SDL_QUIT event, end loop
			case SDL_QUIT:
				mIsRunning = false;
				break;
			/*case SDL_MOUSEBUTTONDOWN:*/
				//int squareIndex = (event.button.x / length) // Column offset in a row
				//	+ ((event.button.y / length) * 48)	// Row number
				//	;
				//SDL_Log (std::to_string(squareIndex).c_str());
				////std::cout << squareIndex << std::endl;
				//tiles[squareIndex].color.r = 0;
		}
	}
	
	// Get state of keyboard
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	
	mIsUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->ProcessInput(state);
	}
	mIsUpdatingActors = false;
	
	// If escape is pressed, also end loop
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
	


}

void Game::UpdateGame()
{
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;

	// Delta time is the difference in ticks from last frame
	// (converted to seconds)
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	
	// Clamp maximum delta time value
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

	// Update tick counts (for next frame)
	mTicksCount = SDL_GetTicks();
	
	// Update all actors
	mIsUpdatingActors = true;
	for (auto actor : mActors)
	{
		actor->Update(deltaTime);
	}
	mIsUpdatingActors = false;

	// Move any pending actors to mActors
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	std::vector<Actor *> deadActors;
	for (auto actor : mActors)
	{
		if (actor->mState == ActorState::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	for (auto actor : deadActors)
	{
		delete actor;
	}

	if (mGameState == GameState::ERunning)
	{
		// Check collision
		for (auto asteroid : mAsteroids)
		{
			if (Intersect(*(mPlayer->GetCollider()), *(asteroid->GetCollider())))
			{
				mPlayer->mState = ActorState::EDead;
				mGameState = GameState::EGameover;
				break;
				//mIsRunning = false;
			}
		}
	}

}

void Game::GenerateOutput()
{
	mRenderer->Draw();
}

void Game::CreateSpriteVerts()
{
	float positions[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f 
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	mSpriteVerts = new VertexArray(
		positions,
		4,
		indices,
		6);
}

void Game::Shutdown()
{
	// Delete actors
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	TTF_Quit();
	if (mRenderer)
	{
		mRenderer->Shutdown();
	}
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::AddActor(Actor *actor)
{
	if (mIsUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}

}

void Game::RemoveActor(Actor *actor)
{
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		// Swap to end of vector and pop off to remove it
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void Game::AddAsteroid(Asteroid *a)
{
	mAsteroids.emplace_back(a);
}

void Game::RemoveAsteroid(Asteroid *a)
{
	auto iter = std::find(mAsteroids.begin(), mAsteroids.end(), a);
	if (iter != mAsteroids.end())
	{
		std::iter_swap(iter, mAsteroids.end() - 1);
		mAsteroids.pop_back();
	}
}

void Game::AddWireframe(WireframeComponent *wireframe)
{
	int myDrawOrder = wireframe->mDrawOrder;
	auto iter = mWireframes.begin();
	for (;
		iter != mWireframes.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->mDrawOrder)
		{
			break;
		}
	}
	mWireframes.insert(iter, wireframe);
}

void Game::RemoveWireframe(WireframeComponent *wireframe)
{
	// Assume we can always find the vertices
	// ?
	// Need check
	auto iter = std::find(mWireframes.begin(), mWireframes.end(), wireframe);
	mWireframes.erase(iter);
}

Font *Game::GetFont(const std::string &fileName)
{
	// Check if the font is in the map
	auto iter = mFonts.find(fileName);
	if (iter == mFonts.end())
	{
		// If not found, load the font
		Font *font = new Font(this);
		if (font->Load(fileName))
		{
			mFonts.emplace(fileName, font);
		}
		else
		{
			font->Unload();
			delete font;
			font = nullptr;
		}
		return font;
	}

	return nullptr;
}

void Game::PushUI(UIScreen *screen)
{
	mUIStack.emplace_back(screen);
}

SDL_Texture *LoadTexture(SDL_Renderer *renderer, const std::string& fileName)
{
	SDL_Surface *surface = IMG_Load(fileName.c_str());
	if (!surface)
	{
		SDL_Log("Failed to load texture file %s", fileName.c_str());
		return nullptr;
	}

	// Create texture from surface
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
	if (!texture)
	{
		SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
		return nullptr;
	}

	return texture;
}

const std::string &Game::GetText(const std::string &textKey)
{
	static std::string errorMsg("**KEY NOT FOUND**");
	// Find this text in the map, if it exists
	auto iter = mText.find(textKey);
	if (iter != mText.end())
	{
		return iter->second;
	}
	else
	{
		return errorMsg;
	}
}
