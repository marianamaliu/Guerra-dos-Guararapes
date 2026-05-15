#ifndef SCENE_H
#define SCENE_H
#include "raylib.h"

typedef struct Scene
{
    Image collision_image;
    Vector2 offsetMap;
    Texture2D map[3];
    int currentMap;
    float mapScale;

} Scene;

void InitScene(Scene *scene, const char *imagePath);
Vector2 ScreenToMapPosition(Scene *scene, Vector2 screenPos);
bool CheckSceneCollision(Scene *scene, Vector2 screenPos);
void DrawScene(Scene *scene);
void UnloadScene(Scene *scene);

#endif