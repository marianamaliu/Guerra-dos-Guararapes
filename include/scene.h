#ifndef SCENE_H
#define SCENE_H
#include "raylib.h"

typedef struct Scene
{
    Texture2D map;
    Image collision_image;
    float mapScale;
    Vector2 offsetMap;

    Color *collision_pixels;
} Scene;

void InitScene(Scene *scene, const char *imagePath);
void CalculateMap(Scene *scene);
Vector2 ScreenToMapPosition(Scene *scene, Vector2 screenPos);
bool CheckSceneCollision(Scene *scene, Vector2 screenPos);
void DrawScene(Scene *scene);
void UnloadScene(Scene *scene);

#endif