#pragma once
#include <string>
#include "Math.h"
#include <unordered_map>
#include <SDL/SDL_ttf.h>

class Font
{
public:
	Font(class Game *game);
	~Font();
	bool Load(const std::string &fileName);
	void Unload();
	class Texture *RenderText(const std::string &textKey,
		const Vector3 &color = Color::White,
		int pointSize = 30);
	
private:
	std::unordered_map<int, TTF_Font *> mFontData; // Point size, font data
	class Game *mGame;
};

