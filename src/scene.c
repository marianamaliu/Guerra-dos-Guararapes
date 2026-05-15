#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "scene.h"

void InitScene(Scene *scene, const char *imagePath)
{
    scene->map[scene->currentMap] = LoadTexture(imagePath);
}

void DrawScene(Scene *scene)
{
    float screenWidth = (float)GetScreenWidth();
    float screenHeight = (float)GetScreenHeight();
    float mapWidth = (float)scene->map[scene->currentMap].width;
    float mapHeight = (float)scene->map[scene->currentMap].height;

    float scaleX = screenWidth / mapWidth;
    float scaleY = screenHeight / mapHeight;
    float scale = fmaxf(scaleX, scaleY);

    float scaledWidth = mapWidth * scale;
    float scaledHeight = mapHeight * scale;

    float offsetX = (screenWidth - scaledWidth) * 0.5f;
    float offsetY = (screenHeight - scaledHeight) * 0.5f;

    scene->mapScale = scale;
    scene->offsetMap = (Vector2){offsetX, offsetY};

    Rectangle sourceRec = {0.0f, 0.0f, mapWidth, mapHeight};
    Rectangle destRec = {
        offsetX,
        offsetY,
        scaledWidth,
        scaledHeight
    };

    DrawTexturePro(scene->map[scene->currentMap], sourceRec, destRec, (Vector2){0, 0}, 0.0f, WHITE);
}

// Define a posição do jogador no mapa de colisão a partir do mapa base
Vector2 ScreenToMapPosition(Scene *scene, Vector2 screenPos)
{
    // Remove o offset (margem de erro) de centralização
    float mapX = screenPos.x - scene->offsetMap.x;
    float mapY = screenPos.y - scene->offsetMap.y;

    mapX /= scene->mapScale;
    mapY /= scene->mapScale;

    return (Vector2){mapX, mapY};
}


void UnloadScene(Scene *scene)
{
    UnloadTexture(scene->map[scene->currentMap]);
    UnloadImage(scene->collision_image);
}
