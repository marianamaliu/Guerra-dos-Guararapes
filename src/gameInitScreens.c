#include "game.h"
#include "enemy.h"
#include <raylib.h>
#include <stdio.h>
#include "gameInitScreen.h"

screen iniciandoGame() {
    screen configs;
    configs.currentScreen = MENU;
    configs.showDebug = true;

    configs.screenSizes = (Vector2){GetScreenWidth(), GetScreenHeight()};

    InitWindow(configs.screenSizes.x, configs.screenSizes.y, "Bguararapes");
    SetTargetFPS(60);

    return configs;
}

void drawMenu(screen *Sstate){
    BeginDrawing();
    DrawScene(&Sstate->map);

    const char *instrucao = "Pressione ENTER para JOGAR";
    int fontSizeInstrucao = 20;

    // 2. Centralização da Instrução:
    int xInstrucao = Sstate->map.screenSizes.x / 2 - MeasureText(instrucao, fontSizeInstrucao) / 2;
    int yInstrucao = Sstate->map.screenSizes.y / 2;

    DrawText(instrucao, xInstrucao, yInstrucao, fontSizeInstrucao, BLACK);
    if (IsKeyDown(KEY_ENTER))
    {
        Sstate->currentScreen = GAMEPLAY;
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

