#include <scene.h>
#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "scene.h"

void InitScene(Scene *scene, const char *imagePath)
{
    scene->map = LoadTexture(imagePath);
}

void CalculateMap(Scene *scene)
{
    float screenWidth = (float)GetScreenWidth();
    float screenHeight = (float)GetScreenHeight();
    float mapWidth = (float)scene->map.width;
    float mapHeight = (float)scene->map.height;

    float scaleX = screenWidth / mapWidth;
    float scaleY = screenHeight / mapHeight;

    // 1. FATOR DE ESCALA UNIFICADO (fmaxf para "Cover")
    float scale = fmaxf(scaleX, scaleY);

    // 2. DIMENSÕES ESCALADAS USANDO O FATOR UNIFICADO
    float scaledWidth = mapWidth * scale;   // CORREÇÃO: Usar 'scale'
    float scaledHeight = mapHeight * scale; // CORREÇÃO: Usar 'scale'

    // 3. CÁLCULO DE OFFSET
    float offSetX = (screenWidth - scaledWidth) * 0.5f;
    float offSetY = (screenHeight - scaledHeight) * 0.5f;

    // 4. ARMAZENAMENTO
    scene->mapScale = scale;
    scene->offsetMap = (Vector2){offSetX, offSetY};
}

void DrawScene(Scene *scene)
{

    CalculateMap(scene);
    Color color_tarja = BLACK;

    // 1. Obtém as dimensões atuais da tela (dinâmicas)
    float screenWidth = (float)GetScreenWidth();
    float screenHeight = (float)GetScreenHeight();

    // 2. Obtém as dimensões da imagem do mapa
    float mapWidth = (float)scene->map.width;
    float mapHeight = (float)scene->map.height;

    // --- CÁLCULO PARA EVITAR DEFORMAÇÃO (Mantém a proporção) ---

    // Calcula o fator de escala necessário para preencher a largura e altura da tela.
    float scaleX = screenWidth / mapWidth;
    float scaleY = screenHeight / mapHeight;

    // Escolhe o fator de escala MAIOR (fmaxf) para garantir que o mapa COBRE toda a tela.
    // Isso evita tarjas brancas, mas causa o efeito "zoom" (corte nas bordas).
    float scale = fmaxf(scaleX, scaleY);

    // --- Dimensões Finais do Mapa na Tela ---
    float scaledWidth = mapWidth * scale;
    float scaledHeight = mapHeight * scale;

    // --- Posição para Centralizar o Mapa ---
    // Calcula o offset para centralizar a imagem escalada na tela.
    float offsetX = (screenWidth - scaledWidth) * 0.5f;
    float offsetY = (screenHeight - scaledHeight) * 0.5f;

    // 3. Retângulo de ORIGEM (Source): A Imagem Inteira
    Rectangle sourceRec = {0.0f, 0.0f, mapWidth, mapHeight};

    // 4. Retângulo de DESTINO (Destination): Onde e Quão Grande Desenhar na tela
    Rectangle destRec = {
        offsetX,     // Posição X ajustada para centralizar
        offsetY,     // Posição Y ajustada para centralizar
        scaledWidth, // Largura escalada (mantendo proporção)
        scaledHeight // Altura escalada (mantendo proporção)
    };

    DrawTexturePro(scene->map, sourceRec, destRec, (Vector2){0, 0}, 0.0f, WHITE);
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
    UnloadTexture(scene->map);
    UnloadImage(scene->collision_image);
}
