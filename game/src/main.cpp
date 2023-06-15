#include "rlImGui.h"
#include "math.h"
#include <vector>
#include "raylib.h"
#include "TileMap.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Ali's Lab 4");
    SetTargetFPS(120);

    Tilemap tilemap;
    tilemap.Regenerate(tilemap);

    Vector2 characterPosition = tilemap.TilePosToScreenPos(1, 1); // Starting position of the character
    Texture2D characterSprite = LoadTexture("../game/assets/textures/character.png");

    float characterSpeed = 0.5f;

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Check keyboard input and update character position
        Vector2 oldCharacterPosition = characterPosition;

        if (IsKeyDown(KEY_W) && tilemap.IsTraversible(tilemap.ScreenPosToTilePos({ characterPosition.x, characterPosition.y - tilemap.tileSizeY })))
            characterPosition.y -= tilemap.tileSizeY * characterSpeed;
        if (IsKeyDown(KEY_S) && tilemap.IsTraversible(tilemap.ScreenPosToTilePos({ characterPosition.x, characterPosition.y + tilemap.tileSizeY })))
            characterPosition.y += tilemap.tileSizeY * characterSpeed;
        if (IsKeyDown(KEY_A) && tilemap.IsTraversible(tilemap.ScreenPosToTilePos({ characterPosition.x - tilemap.tileSizeX, characterPosition.y })))
            characterPosition.x -= tilemap.tileSizeX * characterSpeed;
        if (IsKeyDown(KEY_D) && tilemap.IsTraversible(tilemap.ScreenPosToTilePos({ characterPosition.x + tilemap.tileSizeX, characterPosition.y })))
            characterPosition.x += tilemap.tileSizeX * characterSpeed;

        // Reset character position if it moved onto a non-traversable tile
        if (!tilemap.IsTraversible(tilemap.ScreenPosToTilePos(characterPosition)))
            characterPosition = oldCharacterPosition;

        // Draw the tilemap
        tilemap.DrawTiles();
        tilemap.DrawBorders();

        // Draw the character sprite
        DrawTextureV(characterSprite, characterPosition, WHITE);

        EndDrawing();
    }

    UnloadTexture(characterSprite);
    CloseWindow();
    return 0;
}
