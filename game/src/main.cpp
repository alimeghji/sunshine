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
    float maxSpeed = 500;
    float maxAcceleration = 1000;
    float desiredSpeed = 0;
    Texture2D fish;
};

class Obstacle
{
public:
    Vector2 position;
    Texture2D rock;
};

float Vector2Length(const Vector2& vector)
{
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

Vector2 CustomNormalize(const Vector2& vector)
{
    float length = Vector2Length(vector);
    if (length != 0)
        return { vector.x / length, vector.y / length };
    else
        return { 0, 0 };
}

Vector2 Seek(const Vector2& agentPosition, const Vector2& targetPosition, const Vector2& agentVelocity, float maxAcceleration)
{
    Vector2 desiredVelocity = CustomNormalize(targetPosition - agentPosition) * maxAcceleration;
    Vector2 steering = desiredVelocity - agentVelocity;

    return steering;
}

Vector2 Flee(const Vector2& agentPosition, const Vector2& obstaclePosition, const Vector2& agentVelocity, float maxAcceleration)
{
    Vector2 desiredVelocity = CustomNormalize(agentPosition - obstaclePosition) * maxAcceleration;
    Vector2 steering = desiredVelocity - agentVelocity;

    return steering;
}

void UpdateRigidbody(Rigidbody& rigidbody, const Vector2& acceleration, float deltaTime)
{
    rigidbody.velocity.x += acceleration.x * deltaTime;
    rigidbody.velocity.y += acceleration.y * deltaTime;

    rigidbody.position.x += rigidbody.velocity.x * deltaTime;
    rigidbody.position.y += rigidbody.velocity.y * deltaTime;
}

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Sunshine");
    SetTargetFPS(240);

    Texture2D background = LoadTexture("../game/assets/textures/sea.png");

    std::vector<Agent> agents;
    std::vector<Obstacle> obstacles;

    // Create agents and add them to the container
    Agent agent1;
    agent1.rigidbody.position = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    agent1.rigidbody.velocity = { 200.0f, -200.0f };
    agent1.fish = LoadTexture("../game/assets/textures/fish.png");
    agents.push_back(agent1);

    Agent agent2;
    agent2.rigidbody.position = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    agent2.rigidbody.velocity = { -200.0f, 200.0f };
    agent2.fish = LoadTexture("../game/assets/textures/fish.png");
    agents.push_back(agent2);

    // Create obstacles and add them to the container
    Obstacle obstacle;
    obstacle.position = { SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 };
    obstacle.rock = LoadTexture("../game/assets/textures/shark1.png");
    obstacles.push_back(obstacle);

    bool isMouseButtonDown = false;

    while (!WindowShouldClose())
    {
        const float deltaTime = GetFrameTime();

        // Check mouse button state
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        {
            isMouseButtonDown = true;
        }
        else
        {
            isMouseButtonDown = false;
        }

        // Update all agents
        for (auto& agent : agents)
        {
            if (isMouseButtonDown)
            {
                // Seek toward the mouse
                Vector2 mousePosition = GetMousePosition();
                Vector2 acceleration = Seek(agent.rigidbody.position, mousePosition, agent.rigidbody.velocity, agent.maxAcceleration);
                UpdateRigidbody(agent.rigidbody, acceleration, deltaTime);
            }
            else
            {
                // Flee from the obstacles
                for (const auto& obstacle : obstacles)
                {
                    Vector2 acceleration = Flee(agent.rigidbody.position, obstacle.position, agent.rigidbody.velocity, agent.maxAcceleration);
                    UpdateRigidbody(agent.rigidbody, acceleration, deltaTime);
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTexture(background, 0, 0, RAYWHITE);

        // Draw agents
        for (const auto& agent : agents)
        {
            DrawTexture(agent.fish, agent.rigidbody.position.x - agent.fish.width / 2, agent.rigidbody.position.y - agent.fish.height / 2, WHITE);
        }

        // Draw obstacles
        for (const auto& obstacle : obstacles)
        {
            DrawTexture(obstacle.rock, obstacle.position.x - obstacle.rock.width / 2, obstacle.position.y - obstacle.rock.height / 2, WHITE);
        }

        EndDrawing();
    }

    UnloadTexture(background);
   
    // Unload textures
    for (auto& agent : agents)
    {
        UnloadTexture(agent.fish);
    }

    for (auto& obstacle : obstacles)
    {
        UnloadTexture(obstacle.rock);
    }

    CloseWindow();
    return 0;
}