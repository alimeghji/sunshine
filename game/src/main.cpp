#include "rlImGui.h"
#include "math.h"
#include <vector>
#include "raylib.h"
#include "TileMap.h"
#include "PathFinder.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Ali's Lab 5");
    SetTargetFPS(120);

    Tilemap tilemap;
    tilemap.Regenerate(tilemap);

    Tilemap& level = tilemap;

    Vector2 characterPosition = tilemap.TilePosToScreenPos(1, 1); // Starting position of the character
    TileCoord agentTilePos = tilemap.ScreenPosToTilePos(characterPosition);
    Texture2D characterSprite = LoadTexture("../game/assets/textures/character.png");

    float characterSpeed = 0.5f;
    Pathfinder pathfinder(&level, agentTilePos, TileCoord());

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Check keyboard input and update character position
        Vector2 oldCharacterPosition = characterPosition;

        if (IsKeyPressed(KEY_W) && tilemap.IsTraversible(tilemap.ScreenPosToTilePos({ characterPosition.x, characterPosition.y - tilemap.tileSizeY })))
            characterPosition.y -= tilemap.tileSizeY;
        if (IsKeyPressed(KEY_S) && tilemap.IsTraversible(tilemap.ScreenPosToTilePos({ characterPosition.x, characterPosition.y + tilemap.tileSizeY })))
            characterPosition.y += tilemap.tileSizeY;
        if (IsKeyPressed(KEY_A) && tilemap.IsTraversible(tilemap.ScreenPosToTilePos({ characterPosition.x - tilemap.tileSizeX, characterPosition.y })))
            characterPosition.x -= tilemap.tileSizeX;
        if (IsKeyPressed(KEY_D) && tilemap.IsTraversible(tilemap.ScreenPosToTilePos({ characterPosition.x + tilemap.tileSizeX, characterPosition.y })))
            characterPosition.x += tilemap.tileSizeX;

        // Reset character position if it moved onto a non-traversable tile
        if (!tilemap.IsTraversible(tilemap.ScreenPosToTilePos(characterPosition)))
            characterPosition = oldCharacterPosition;

        // Draw the tilemap
        tilemap.DrawTiles();
        tilemap.DrawBorders();

        // Draw the character sprite
        DrawTextureV(characterSprite, characterPosition, WHITE);

        TileCoord mouseTilePos = level.GetTileAtScreenPos(GetMousePosition());
        if (level.IsInsideGrid(mouseTilePos.x, mouseTilePos.y))
        {
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
            {
                pathfinder = Pathfinder(&level, agentTilePos, TileCoord(mouseTilePos));
            }

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            {
                pathfinder = Pathfinder(&level, agentTilePos, TileCoord(mouseTilePos));
                pathfinder.SolvePath();
            }
        }
        if (pathfinder.map != nullptr)
        {
            if (IsKeyPressed(KEY_SPACE))
            {
                pathfinder.ProcessNextIterationFunctional();
            }
        }

        EndDrawing();
    }

    UnloadTexture(characterSprite);
    CloseWindow();
    return 0;
}