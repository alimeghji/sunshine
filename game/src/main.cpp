#include "rlImGui.h"
#include "Math.h"
#include <vector>
#include <raylib.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Rigidbody
{
public:
    Vector2 position;
    Vector2 velocity;
};

class Agent
{
public:
    Rigidbody rigidbody;
    float maxSpeed;
    float maxAcceleration;
};

void UpdateRigidbody(Rigidbody& rigidbody, float deltaTime)
{
    rigidbody.position.x += rigidbody.velocity.x * deltaTime;
    rigidbody.position.y += rigidbody.velocity.y * deltaTime;
}

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    rlImGuiSetup(true);
    SetTargetFPS(240);

    std::vector<Agent> agents;

    // Create agents and add them to the container
    Agent agent1;
    agent1.rigidbody.position = { 0.0f, 0.0f };
    agent1.rigidbody.velocity = { 1.0f, 1.0f };
    agents.push_back(agent1);

    Agent agent2;
    agent2.rigidbody.position = { 2.0f, 2.0f };
    agent2.rigidbody.velocity = { -0.5f, 0.8f };
    agents.push_back(agent2);

    bool useGUI = false;
    while (!WindowShouldClose())
    {
        const float deltaTime = GetFrameTime();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (IsKeyPressed(KEY_GRAVE)) useGUI = !useGUI;
        if (useGUI)
        {
           
        }
        else
        {
            for (auto& agent : agents)
            {
                UpdateRigidbody(agent.rigidbody, deltaTime);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
