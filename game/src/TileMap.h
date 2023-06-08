#pragma once
#include "TileCoord.h"
#include <vector>
#include "raylib.h"

#define MAP_WIDTH 100
#define MAP_HEIGHT 100

enum class Tile
{
	Floor = 0, // Floor tiles can be walked on
	Wall, // Wall tiles cannot be walked on
	Count // Number of tile types
};

class Tilemap
{
private:
	Tile tiles[MAP_WIDTH][MAP_HEIGHT];

	std::vector<std::vector<Tile>> tiles;
	int width = 0; // number of columns
	int height = 0; // number of rows in each column

public:
	int tileSizeX = 100; // width of tiles in pixels when drawing
	int tileSizeY = 100; // height of tiles in pixels when drawing	

	Vector2 GetScreenPosOfTile(TileCoord tilePosition)
	{
		return Vector2{ (float)tilePosition.x * tileSizeX, (float)tilePosition.y * tileSizeY };
	}

	TileCoord GetTileAtScreenPos(Vector2 positionOnScreen)
	{
		return { floorf(positionOnScreen.x / tileSizeX), floorf(positionOnScreen.y / tileSizeY) };
	}

	int GetGridWidth(); // get number of columns in the grid
	int GetGridHeight(); // get number of rows in the grid
	Tile GetTile(int x, int y); // get the tile at the specified coordinate in the grid
	void SetTile(int x, int y, Tile type); // set the tile at the specified coordinate in the grid
	bool IsInsideGrid(int x, int y); // returns true if the coordinate is inside the grid, false otherwise
	Vector2 TilePosToScreenPos(Vector2 tilePosition); // convert from a tile coordinate to a screen position
	Vector2 TilePosToScreenPos(int x, int y); // convert from a tile coordinate to a screen position
	Vector2 ScreenPosToTilePos(Vector2 positionOnScreen); // find a tile coordinate given a position on the screen over a tile

	void DrawBorders(Color color = BLACK)
	{
		for (int x = 0; x < GetGridWidth(); x++)
			DrawLine(x * tileSizeX, 0, x * tileSizeX, GetGridHeight() * tileSizeY, color);
	}
};


