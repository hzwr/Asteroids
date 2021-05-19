#pragma once
#include "SDL/SDL.h"
#include "Tile.h"
#include "Search.h"
#include "World.h"
#include "Math.h"

// Game class
class Game
{
public:
	Game();
	~Game();
	// Initialize the game
	bool Initialize();
	// Runs the game loop until the game is over
	void RunLoop();
	// Shutdown the game
	void Shutdown();

	//SDL_Renderer *GetRenderer() { return mRenderer; }

	SDL_Texture *GetTexture(const std::string& fileName);
	const std::string &GetText(const std::string &key);

	void AddActor(class Actor *actor);
	void RemoveActor(class Actor *actor);

	void AddAsteroid(class Asteroid *a);
	void RemoveAsteroid(class Asteroid *a);

	void AddSprite(class SpriteComponent *sprite);
	void RemoveSprite(class SpriteComponent *sprite);

	void AddWireframe(class WireframeComponent *wireframe);
	void RemoveWireframe(class WireframeComponent *wireframe);

	// Getter
	std::vector<class Asteroid *> &GetAsteroids() { return mAsteroids; }


private:
	// Helper functions for the game loop
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	// Map of textures loaded
	std::unordered_map<std::string, SDL_Texture *> mTextures;

	// Window created by SDL
	SDL_Window *mWindow;
	// Renderer for 2D drawing
	SDL_Renderer *mRenderer;
	// Number of ticks since start of game
	Uint32 mTicksCount;
	// Game should continue to run
	bool mIsRunning;
	std::unordered_map<std::string, std::string> mText;

	// For pathfinding
	World world;
	GraphNode *start;
	GraphNode *goal;

	// Game objects
	class Player *mPlayer;
	std::vector<class Asteroid *> mAsteroids;
	std::vector<class Bullet *> mBullets;
	std::vector<class Actor *> mActors;
	std::vector<class Actor *> mPendingActors;
	bool mIsUpdatingActors;
	bool mIsPathFound;

	// Sprites for drawing
	std::vector<class SpriteComponent *> mSprites;
	std::vector<class WireframeComponent *> mWireframes;
};
