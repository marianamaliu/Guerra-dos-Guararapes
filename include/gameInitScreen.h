#ifndef SCREEN_H
#define SCREEN_H

#include "game.h"
#include "scene.h"
#include "enemy.h"  
#include "raylib.h"

typedef struct {
    GameScreen currentScreen;
    Scene map;
    int cliques;
    bool showDebug;
} screen;

/**
 * @brief Inicializa o estado do jogo e a tela.
 * @return screen inicializada.
 */
screen iniciandoGame();

/**
 * @brief Inicializa a janela do Raylib com a resolucao do monitor.
 */
void InitWindow_REFACTOR();

void drawMenu(screen *Sstate);
void drawLore(screen *Sstate);
void drawGameplay(screen *Sstate);
void draWinning(screen *Sstate);
void drawLosing(screen *Sstate);

#endif