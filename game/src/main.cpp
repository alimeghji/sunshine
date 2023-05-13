#include "rlImGui.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    SetTargetFPS(60);

    Vector2 ballPosition = { (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 }; // Position for circle
    Color ballColor = DARKBLUE; // Color for circle

    Vector2 circlePosition = { (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 }; // Position for circle
    Color circleColor = DARKGREEN; // Color for circle

    const float ballRadius = 50.0f; // Circle radius
    const float circleRadius = 50.0f; // Circle radius

    const char* fileName = "..\assets\background11.jpg";

    Vector2 recPosition = { 200, 500 }; // Rectangle position
    Vector2 recSize = { 150, 200 }; // Rectangle size

    Vector2 lineStartPos = { 19,60 }; // Line start position
    Vector2 lineEndPos = { 1079, 60 }; // Line end position

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawLineEx(lineStartPos, lineEndPos, 10, DARKPURPLE); // Draws a line with thickness

        ballPosition = GetMousePosition(); // Used for input from the mouse
        
        DrawCircleV(circlePosition, circleRadius, circleColor); // Draws a circle on the screen

        DrawCircleV(ballPosition, ballRadius, ballColor); // Draws another circle on the screen

        if (CheckCollisionCircles(ballPosition, ballRadius, circlePosition, circleRadius)) // Checks for circle collision
        {                                                                                  // Then changes circle color
            ballColor = GREEN;
            circleColor = BLUE;
        }
        else
        {
            ballColor = PURPLE;
            circleColor = YELLOW;
        }

        Image LoadImage(const char* fileName); // Loads an image to the screen

        if (IsKeyDown(KEY_D)) recPosition.x += 7.5f;  
        if (IsKeyDown(KEY_A)) recPosition.x -= 7.5f;  // Keybaord input for rectangle
        if (IsKeyDown(KEY_W)) recPosition.y -= 7.5f;             
        if (IsKeyDown(KEY_S)) recPosition.y += 7.5f;

        DrawRectangleV(recPosition, recSize, ORANGE); // Draws a rectangle on screen

        DrawRing(Vector2{ 1000,175 }, 20, 40, 0, 360, 1, DARKBLUE); // Draws a 1 segment ring
        DrawRing(Vector2{ 1000,360 }, 20, 40, 0, 360, 4, GOLD); // Draws a 4 segment ring
        DrawRing(Vector2{ 1000,560 }, 20, 40, 0, 360, 5, DARKPURPLE); // Draws a 5 segment ring
       
        DrawText("USE YOUR MOUSE TO CONTROL THE CIRCLE AND (W, A, S, D) FOR THE RECTANGLE!", 16, 9, 25, BLACK);
    
        EndDrawing();
    }
}