#include "game.h"
#include "enemy.h"
#include <raylib.h>
#include <stdio.h>
#include "gameInitScreen.h"

screenState iniciandoGame() {
    screenState state;
    state.currentScreen = MENU;
    state.cliques = 1;
    state.showDebug = true;

    int WINDOW_WIDTH = GetMonitorWidth(0);
    int WINDOW_HEIGHT = GetMonitorHeight(0);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "blinky");
    SetTargetFPS(60);

    return state;
}

void drawMenu(screenState *Sstate){
    BeginDrawing();
    DrawScene(&Sstate->map1);

    const char *instrucao = "Pressione ENTER para JOGAR";
    int fontSizeInstrucao = 20;

    // 2. Centralização da Instrução:
    int xInstrucao = Sstate->map1.offsetMap.x / 2 - MeasureText(instrucao, fontSizeInstrucao) / 2;
    int yInstrucao = Sstate->map1.offsetMap.y / 2;

    DrawText(instrucao, xInstrucao, yInstrucao, fontSizeInstrucao, BLACK);
    if (IsKeyDown(KEY_ENTER))
    {
        Sstate.currentScreen = GAMEPLAY;
    }
    
    EndDrawing();
}

void drawLore(screenState *Sstate){
    printf("lore desenhada");
}

void drawGameplay(screenState *Sstate){
    printf("gameplay desenhada");
}
void draWinning(screenState *Sstate){
    printf("draWinning");
}
void drawLosing(screenState *Sstate){
    printf("draw losing");
}

