#include "game.h"
#include "enemy.h"
#include <raylib.h>
#include <stdio.h>
#include "gameInitScreen.h"

screen iniciandoGame() {
    screen configs;
    configs.currentScreen = MENU;
    configs.showDebug = true;

    int monitor = GetCurrentMonitor();
    int w = GetMonitorWidth(monitor);
    int h = GetMonitorHeight(monitor);

    InitWindow(w, h, "Bguararapes");
    SetTargetFPS(60);

    configs.screenSizes = (Vector2){ GetScreenWidth(), GetScreenHeight() };

    return configs;
}

void drawMenu(screen *Sstate){
    BeginDrawing();
    DrawScene(&Sstate->map);

    const char *instrucao = "Pressione ENTER para JOGAR";
    int fontSizeInstrucao = 20;

    // 2. Centralização da Instrução:
    int xInstrucao = Sstate->screenSizes.x / 2 - MeasureText(instrucao, fontSizeInstrucao) / 2;
    int yInstrucao = Sstate->screenSizes.y / 2;

    DrawText(instrucao, xInstrucao, yInstrucao, fontSizeInstrucao, BLACK);
    if (IsKeyDown(KEY_ENTER))
    {
        //Talvez valha a pena fazer uma função somente para isso
        Sstate->currentScreen = GAMEPLAY;
        Sstate->map.currentScreen = GAMEPLAY;
    }
    
    EndDrawing();
}

void drawLore(screen *Sstate){
    printf("lore desenhada");
}

void drawGameplay(screen *Sstate){
    BeginDrawing();
    DrawScene(&Sstate->map);

    EndDrawing();
}
void draWinning(screen *Sstate){
    printf("draWinning");
}
void drawLosing(screen *Sstate){
    printf("draw losing");
}

