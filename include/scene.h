#ifndef SCENE_H
#define SCENE_H
#include "raylib.h"
#include "game.h"

typedef struct Scene
{
    Image collision_image;
    Vector2 offsetMap;
    Texture2D mapTexture[3];
    GameScreen currentScreen;
    float mapScale;
} Scene;

void addScenes(Scene *scene);
Vector2 ScreenToMapPosition(Scene *scene, Vector2 screenPos);
bool CheckSceneCollision(Scene *scene, Vector2 screenPos);
void DrawScene(Scene *scene);
void UnloadScene(Scene *scene);

#endif