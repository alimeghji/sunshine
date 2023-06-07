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
    Vector2 lineEndLeft;
    Vector2 lineEndRight;

    Agent()
    {
        circleRotation = 0.0f;
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

    while (!WindowShouldClose())
    {
        obstacle1.Update();

        Vector2 direction = Normalize(Subtract(obstacle1.position, agent1.circlePosition));
        agent1.circleRotation = atan2f(direction.y, direction.x) * RAD2DEG;  // Calculate the rotation angle of the Agent

        Vector2 directionLeft = Rotate(direction, -30.0f + agent1.circleRotation);  // Rotate the direction by the Agent's rotation
        Vector2 directionRight = Rotate(direction, 30.0f + agent1.circleRotation);  // Rotate the direction by the Agent's rotation

        agent1.lineStartLeft = agent1.circlePosition;
        agent1.lineStartRight = agent1.circlePosition;

        agent1.lineEndLeft = Add(agent1.lineStartLeft, Scale(Normalize(directionLeft), agent1.circleRadius * 2));
        agent1.lineEndRight = Add(agent1.lineStartRight, Scale(Normalize(directionRight), agent1.circleRadius * 2));

        DrawCircleV(obstacle1.position, obstacleRadius, RED);
        DrawCircleV(agent1.circlePosition, agent1.circleRadius, BLUE);

        // Drawing lines relative to the Agent's rotation
        DrawLineEx(agent1.lineStartLeft, agent1.lineEndLeft, 2.0f, GREEN);
        DrawLineEx(agent1.lineStartRight, agent1.lineEndRight, 2.0f, GREEN);

        // Check collision with lines
        bool collisionLeft = CheckCollisionLineCircle(agent1.lineStartLeft, agent1.lineEndLeft, obstacle1.position, obstacle1.radius);
        bool collisionRight = CheckCollisionLineCircle(agent1.lineStartRight, agent1.lineEndRight, obstacle1.position, obstacle1.radius);

        // Handle collision
        if (collisionLeft)
        {
            // Turn right
            agent1.circleRotation += 1.0f;
        }
        else if (collisionRight)
        {
            // Turn left
            agent1.circleRotation -= 1.0f;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

//float angle = atan2(direction.y, direction.x) * RAD2DEG;
        //float whiskerAngle = angle + 15;
        //angle = angle + 360;
        //angle = fmodf(angle, 360.0f);
        //whiskerAngle = fmodf(whiskerAngle, 360.0f);

        ////to create a vector from an angle use cos and sin
        //Vector2 whiskerLeft = Vector2{ cosf(whiskerAngle * DEG2RAD), sinf(whiskerAngle * DEG2RAD) };

        //float distanceFromObstacleToPoint = Distance(nearestPointC, obstaclePosition)
        // bool rightCollision = (distanceFromObstacleToPoint <= obstacleRadius)

//class Agent
//{
//public:
//    Vector2 lineStart;
//    Vector2 lineEnd;
//    Vector2 circlePosition;
//    float circleRadius;
//};
//
//class Obstacle
//{
//public:
//    Vector2 obstaclePosition = { (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 };
//    const float obstacleRadius = 40.0f;
//};