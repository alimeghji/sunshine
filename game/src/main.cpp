#include "rlImGui.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    SetTargetFPS(120);

    rlImGuiSetup(true);

    bool useGUI = false;
    while (!WindowShouldClose())
    {
        const float dt = GetFrameTime();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (IsKeyPressed(KEY_GRAVE)) useGUI = !useGUI;
        if (useGUI)
        {
            rlImGuiBegin();

            rlImGuiBegin();
        }

        //DrawText("Hello World!", 16, 9, 20, RED);
        DrawFPS(10, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}