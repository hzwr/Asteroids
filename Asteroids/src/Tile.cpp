#include "Tile.h"
#include "SDL/SDL.h"

namespace Tile {

	Tile::Tile()
		:id(0)
		, color(Color(255, 255, 255))
	{
		//SDL_Log("Tile contructor");
	}

	Tile::Tile(int id)
		:id(id)
		, color(Color(255, 255, 255))
	{
	}

}