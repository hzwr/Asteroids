#pragma once

namespace Tile {

	struct Color
	{
		Color(int r, int g, int b) :r(r), g(g), b(b) {};
		int r, g, b;
	};
	class Tile
	{
	public:
		Tile();
		Tile(int id);
		int id;
		Color color;


	};
}

