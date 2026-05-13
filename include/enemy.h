#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include "raymath.h"
// #include "collision_map.h"

#define MAX_WAYPOINTS 10
#define MAX_ENEMIES 50

// Estrutura do inimigo
typedef struct
{

    Texture2D texture;
    Vector2 position;
    Vector2 velocity;
    float speed;
    float Xhitbox;
    float Yhitbox;
    int spriteHeight;
    int spriteWidth;

    // Sistema de patrulha
    Vector2 waypoints[MAX_WAYPOINTS];
    int waypointCount;
    int currentWaypoint;
    bool movingForward;

    int frameQtd;           // Quantidade total de sprites (frames) na animação
    int currentFrameIndex;  // Índice do frame atual (de 0 até frameQtd - 1)
    int currentFrameSheetLine; // Linha do spritesheet que o jogo está usando
    float frameTime;        // Tempo de espera (em segundos) até trocar para o próximo sprite
    float frameTimer;       // Timer que acumula o tempo decorrido desde o último frame (para controle de animação)
    bool flipX;             // Flag para virar o sprite horizontalmente (útil para inverter a direção sem ter novos assets)
    

    bool active;
    Color color;
} Enemy;

// Inicializa um inimigo
void InitEnemy(Enemy *enemy, Vector2 startPos, float speed, const char *firstFramePath);

// Adiciona um ponto de patrulha ao inimigo
void AddWaypoint(Enemy *enemy, Vector2 waypoint);

void UpdateEnemy(Enemy *enemy, float deltaTime);

void DrawEnemy(Enemy *enemy, bool debug);

// Verifica colisão entre o inimigo e um retângulo
bool CheckEnemyCollision(Enemy *enemy, Rectangle rect);

Vector2 function_line_frameSheet(Enemy *enemy);

#endif