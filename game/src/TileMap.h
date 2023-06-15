#pragma once
#include "TileCoord.h"
#include <vector>
#include "raylib.h"

#define MAP_WIDTH 100
#define MAP_HEIGHT 100

const Vector2 NORTH = { -1, 0 };
const Vector2 SOUTH = { 1, 0 };
const Vector2 EAST = { 0, 1 };
const Vector2 WEST = { 0, -1 };

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

public:

	int tileSizeX = 100; // width of tiles in pixels when drawing
	int tileSizeY = 100; // height of tiles in pixels when drawing	

	TileCoord GetTileAtScreenPos(Vector2 positionOnScreen)
	{
		return { floorf(positionOnScreen.x / tileSizeX), floorf(positionOnScreen.y / tileSizeY) };
	}

	Vector2 GetScreenPosOfTile(TileCoord tilePosition)
	{
		return Vector2{ (float)tilePosition.x * tileSizeX, (float)tilePosition.y * tileSizeY };
	}

	int Tilemap::GetGridWidth()
	{
		return MAP_WIDTH;
	} // get number of columns in the grid
	int Tilemap::GetGridHeight()
	{
		return MAP_HEIGHT;
	} // get number of rows in the grid
	Tile Tilemap::GetTile(int x, int y)
	{
		return tiles[x][y];
	}
	// get the tile at the specified coordinate in the grid
	void Tilemap::SetTile(int x, int y, Tile type)
	{
		tiles[x][y] = type;
	} // set the tile at the specified coordinate in the grid
	bool Tilemap::IsInsideGrid(int x, int y)
	{
		return x >= 0 && x < MAP_WIDTH&& y >= 0 && y < MAP_HEIGHT;
	}
	// returns true if the coordinate is inside the grid, false otherwise
	Vector2 Tilemap::TilePosToScreenPos(int x, int y)
	{
		return Vector2{ static_cast<float>(x) * tileSizeX, static_cast<float>(y) * tileSizeY };
	} // convert from a tile coordinate to a screen position
	Vector2 ScreenPosToTilePos(Vector2 positionOnScreen)
	{
		return { floorf(positionOnScreen.x / tileSizeX), floorf(positionOnScreen.y / tileSizeY) };
	} // find a tile coordinate given a position on the screen over a tile

	void DrawBorders(Color color = BLACK)
	{
		for (int x = 0; x < GetGridWidth(); x++)
			DrawLine(x * tileSizeX, 0, x * tileSizeX, GetGridHeight() * tileSizeY, color);

		for (int y = 0; y < GetGridHeight(); y++)
			DrawLine(0, y * tileSizeY, GetGridWidth() * tileSizeX, y * tileSizeY, color);
	}

	void Tilemap::DrawTiles()
	{
		for (int x = 0; x < GetGridWidth(); x++)
		{
			for (int y = 0; y < GetGridHeight(); y++)
			{
				Tile tileType = tiles[x][y]; // Get what type of tile is here
				Vector2 tilePosition = TilePosToScreenPos(x, y);
				Color colorToDraw = PINK;
				if (tileType == Tile::Floor) colorToDraw = LIGHTGRAY;
				else if (tileType == Tile::Wall) colorToDraw = BROWN;

				DrawRectangle(tilePosition.x, tilePosition.y, tileSizeX, tileSizeY, colorToDraw);

				if (tileType == Tile::Floor)
				{
					// Draw a circle in the center of the tile
					Vector2 tileCenter = { tilePosition.x + tileSizeX / 2, tilePosition.y + tileSizeY / 2 };
					DrawCircleV(tileCenter, 5, RED);

					// Draw lines connecting the current tile to adjacent traversable tiles
					std::vector<Vector2> adjacentTiles = GetTraversibleTilesAdjacentTo({ static_cast<float>(x), static_cast<float>(y) });
					for (const auto& adjacentTile : adjacentTiles)
					{
						Vector2 adjacentTileCenter = { adjacentTile.x * tileSizeX + tileSizeX / 2, adjacentTile.y * tileSizeY + tileSizeY / 2 };
						DrawLineEx(tileCenter, adjacentTileCenter, 1, GREEN);
					}
				}
			}
		}
	}


	void Regenerate(Tilemap& level, float chanceOfWall = 0.2)
	{
		for (int x = 0; x < level.GetGridWidth(); x++)
		{
			for (int y = 0; y < level.GetGridHeight(); y++)
			{
				if (Random(0.0, 1.0) < chanceOfWall)
					level.SetTile(x, y, Tile::Wall);
				else
					level.SetTile(x, y, Tile::Floor);
			}
		}
	}

	bool IsTraversible(Vector2 tilePosition)
	{
		if (IsInsideGrid(tilePosition.x, tilePosition.y))
		{
			if (GetTile(tilePosition.x, tilePosition.y) == Tile::Floor) return true;
		}
		return false;
	}

	std::vector<Vector2> GetTraversibleTilesAdjacentTo(Vector2 tilePos)
	{
		std::vector<Vector2> adjacentTilePositions;

		Vector2 N = tilePos + NORTH;
		Vector2 S = tilePos + SOUTH;
		Vector2 E = tilePos + EAST;
		Vector2 W = tilePos + WEST;
		if (IsTraversible(N)) adjacentTilePositions.push_back(N);
		if (IsTraversible(S)) adjacentTilePositions.push_back(S);
		if (IsTraversible(E)) adjacentTilePositions.push_back(E);
		if (IsTraversible(W)) adjacentTilePositions.push_back(W);

		return adjacentTilePositions;
	}

	
};


