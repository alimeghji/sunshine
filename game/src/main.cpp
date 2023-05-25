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
    float maxSpeed = 1000;
    float maxAcceleration = 1000;
};

void UpdateRigidbody(Rigidbody& rigidbody, float deltaTime)
{
    rigidbody.position.x += rigidbody.velocity.x * deltaTime;
    rigidbody.position.y += rigidbody.velocity.y * deltaTime;
}

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    SetTargetFPS(240);

    std::vector<Agent> agents;

    // Create agents and add them to the container
    Agent agent1;
    agent1.rigidbody.position = { SCREEN_WIDTH/2, SCREEN_HEIGHT/2 };
    agent1.rigidbody.velocity = { 150.0f, -150.0f };
    agents.push_back(agent1);

    Agent agent2;
    agent2.rigidbody.position = { SCREEN_WIDTH/2, SCREEN_HEIGHT/2 };
    agent2.rigidbody.velocity = { -150.0f, 150.0f };
    agents.push_back(agent2);

    while (!WindowShouldClose())
    {
        const float deltaTime = GetFrameTime();

        // Update all agents
        for (auto& agent : agents)
        {
            UpdateRigidbody(agent.rigidbody, deltaTime);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Draw agents
        for (const auto& agent : agents)
        {
            DrawCircle(agent.rigidbody.position.x, agent.rigidbody.position.y, 50.0f, BLUE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}