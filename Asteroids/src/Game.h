#pragma once
#include "SDL/SDL.h"
#include "Tile.h"
#include "Search.h"
#include "World.h"
#include "math/Math.h"

enum class GameState
{
	ERunning,
	EGameover
};

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

	void AddActor(class Actor *actor);
	void RemoveActor(class Actor *actor);

	void AddAsteroid(class Asteroid *a);
	void RemoveAsteroid(class Asteroid *a);

	//void AddSprite(class SpriteComponent *sprite);
	//void RemoveSprite(class SpriteComponent *sprite);

	void AddWireframe(class WireframeComponent *wireframe);
	void RemoveWireframe(class WireframeComponent *wireframe);

	// UI
	class Font *GetFont(const std::string& fileName);
	const std::vector<class UIScreen *> &GetUIStack() { return mUIStack; }
	void PushUI(class UIScreen *screen);

	// Getter
	std::vector<class Asteroid *> &GetAsteroids() { return mAsteroids; }
	const std::string &GetText(const std::string &textKey);
	class Renderer *GetRenderer() { return mRenderer; }

private:
	// Helper functions for the game loop
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	// Game State
	GameState mGameState;

	// Map of textures loaded
	std::unordered_map<std::string, class Texture *> m_textures;

	// Window created by SDL
	SDL_Window *mWindow;
	class Renderer *mRenderer;

	// Number of ticks since start of game
	Uint32 mTicksCount;
	// Game should continue to run
	bool mIsRunning;

	// For pathfinding
	World world;
	GraphNode *start;
	GraphNode *goal;

	// Game objects
	class Player *mPlayer;
	class Camera *m_mainCamera;
	std::vector<class Asteroid *> mAsteroids;
	std::vector<class Bullet *> mBullets;
	std::vector<class Actor *> mActors;
	std::vector<class Actor *> mPendingActors;
	bool mIsUpdatingActors;
	bool mIsPathFound;

	// Sprites for drawing
	std::vector<class SpriteComponent *> mSprites;

	std::vector<class WireframeComponent *> mWireframes;

	// UI (fonts...)
	std::unordered_map<std::string, class Font *> mFonts; // <Filename, Font pointer>
	std::unordered_map<std::string, std::string> mText; // Actual texts

	std::vector<class UIScreen *> mUIStack;
};
