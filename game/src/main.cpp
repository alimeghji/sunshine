#include "rlImGui.h"
#include "math.h"
#include <vector>
#include "raylib.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Agent
{
public:
    Vector2 circlePosition;
    float circleRadius;
    float circleRotation;
    Vector2 lineStartLeft;
    Vector2 lineStartRight;
    Vector2 lineStartFrontLeft;
    Vector2 lineStartFrontRight;
    Vector2 lineEndLeft;
    Vector2 lineEndRight;
    Vector2 lineEndFrontLeft;
    Vector2 lineEndFrontRight;

    Agent()
    {
        circleRotation = 0.0f;
    }

    void AvoidObstacle(const Vector2& obstaclePosition, bool collisionLeft, bool collisionRight, bool collisionFrontLeft, bool collisionFrontRight)
    {
        float rotationSpeed = 2.0f;
        float moveSpeed = 2.0f;

        if (collisionLeft || collisionFrontLeft)
        {
            // Turn right
            circleRotation += rotationSpeed;
        }
        else if (collisionRight || collisionFrontRight)
        {
            // Turn left
            circleRotation -= rotationSpeed;
        }

        // Move forward
        circlePosition.x += cosf(circleRotation * DEG2RAD) * moveSpeed;
        circlePosition.y += sinf(circleRotation * DEG2RAD) * moveSpeed;
    }
};

class Obstacle
{
public:
    Vector2 position;
    float radius;

    void Update()
    {
        position = GetMousePosition();
    }

    bool CheckCollisionWithPoint(Vector2 point)
    {
        return (Distance(position, point) <= radius);
    }

    bool CheckCollisionWithLine(Vector2 lineStart, Vector2 lineEnd)
    {
        Vector2 nearest = NearestPoint(lineStart, lineEnd, position);
        return Distance(nearest, position) <= radius;
    }
};

bool CheckCollisionLineCircle(Vector2 lineStart, Vector2 lineEnd, Vector2 circlePosition, float circleRadius)
{
    Vector2 nearest = NearestPoint(lineStart, lineEnd, circlePosition);
    return Distance(nearest, circlePosition) <= circleRadius;
}

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Ali's Lab 3");
    SetTargetFPS(120);

    const float obstacleRadius = 40.0f;

    Agent agent1;
    agent1.circlePosition = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    agent1.circleRadius = 40.0f;

    Obstacle obstacle1;
    obstacle1.radius = obstacleRadius;

    bool collisionLeft = false;
    bool collisionRight = false;
    bool collisionFrontLeft = false;
    bool collisionFrontRight = false;

    while (!WindowShouldClose())
    {
        obstacle1.Update();

        Vector2 direction = Normalize(Subtract(obstacle1.position, agent1.circlePosition));
        agent1.circleRotation = atan2f(direction.y, direction.x) * RAD2DEG;

        Vector2 directionLeft = Rotate(direction, -45.0f);
        Vector2 directionRight = Rotate(direction, 45.0f);
        Vector2 directionFrontLeft = Rotate(direction, 270.0f);
        Vector2 directionFrontRight = Rotate(direction, -270.0f);

        agent1.lineStartLeft = agent1.circlePosition;
        agent1.lineStartRight = agent1.circlePosition;
        agent1.lineStartFrontLeft = agent1.circlePosition;
        agent1.lineStartFrontRight = agent1.circlePosition;

        agent1.lineEndLeft = Add(agent1.lineStartLeft, Scale(Normalize(directionLeft), agent1.circleRadius * 2));
        agent1.lineEndRight = Add(agent1.lineStartRight, Scale(Normalize(directionRight), agent1.circleRadius * 2));
        agent1.lineEndFrontLeft = Add(agent1.lineStartFrontLeft, Scale(Normalize(directionFrontLeft), agent1.circleRadius * 2));
        agent1.lineEndFrontRight = Add(agent1.lineStartFrontRight, Scale(Normalize(directionFrontRight), agent1.circleRadius * 2));

        collisionLeft = obstacle1.CheckCollisionWithLine(agent1.lineStartLeft, agent1.lineEndLeft);
        collisionRight = obstacle1.CheckCollisionWithLine(agent1.lineStartRight, agent1.lineEndRight);
        collisionFrontLeft = obstacle1.CheckCollisionWithLine(agent1.lineStartFrontLeft, agent1.lineEndFrontLeft);
        collisionFrontRight = obstacle1.CheckCollisionWithLine(agent1.lineStartFrontRight, agent1.lineEndFrontRight);

        agent1.AvoidObstacle(obstacle1.position, collisionLeft, collisionRight, collisionFrontLeft, collisionFrontRight);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawCircleV(obstacle1.position, obstacleRadius, RED);
        DrawCircleV(agent1.circlePosition, agent1.circleRadius, BLUE);

        DrawLineEx(agent1.lineStartLeft, agent1.lineEndLeft, 2.0f, collisionLeft ? RED : GREEN);
        DrawLineEx(agent1.lineStartRight, agent1.lineEndRight, 2.0f, collisionRight ? RED : GREEN);
        DrawLineEx(agent1.lineStartFrontLeft, agent1.lineEndFrontLeft, 2.0f, collisionFrontLeft ? RED : GREEN);
        DrawLineEx(agent1.lineStartFrontRight, agent1.lineEndFrontRight, 2.0f, collisionFrontRight ? RED : GREEN);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}