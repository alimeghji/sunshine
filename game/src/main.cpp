#include "rlImGui.h"
#include "math.h"
#include <vector>
#include "raylib.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

class Agent
{
public:
    Vector2 lineStart;
    Vector2 lineEnd;
    Vector2 circlePosition;
    float circleRadius;
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

    Vector2 obstaclePosition = { (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2 };
    const float obstacleRadius = 40.0f;

    Agent agent1;
    agent1.circlePosition = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    agent1.circleRadius = 40.0f;

    while (!WindowShouldClose())
    {
        obstaclePosition = GetMousePosition();
        HideCursor();
        DrawCircleV(obstaclePosition, obstacleRadius, RED);

        DrawCircleV(agent1.circlePosition, agent1.circleRadius, BLUE);

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