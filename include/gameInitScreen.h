#ifndef SCREEN_H
#define SCREEN_H

#include "game.h"
#include "scene.h"
#include "enemy.h"  
#include "raylib.h"

typedef struct {
    GameScreen currentScreen;
    Scene map1;
    int cliques;
    bool showDebug;
} screenState;

/**
 * @brief Inicializa o estado do jogo e a tela.
 * @return screenState inicializada.
 */
screenState iniciandoGame();

/**
 * @brief Inicializa a janela do Raylib com a resolucao do monitor.
 */
void InitWindow_REFACTOR();

void drawMenu(screenState *Sstate);
void drawLore(screenState *Sstate);
void drawGameplay(screenState *Sstate);
void draWinning(screenState *Sstate);
void drawLosing(screenState *Sstate);

#endif