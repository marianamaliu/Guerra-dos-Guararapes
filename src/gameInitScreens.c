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

    // load all scene textures
    addScenes(&configs.map);
    
    // set default map to MENU
    configs.map.currentScreen = MENU;

    configs.screenSizes = (Vector2){ (float)GetScreenWidth(), (float)GetScreenHeight() };

    return configs;
}

void drawMenu(screen *Sstate){
    BeginDrawing();
    DrawScene(&Sstate->map);
    

    const char *instrucao = "Pressione ENTER para JOGAR";
    int fontSizeInstrucao = 20;

    // 2. Centralização da Instrução (calcula no momento do desenho)
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();
    int xInstrucao = screenW / 2 - MeasureText(instrucao, fontSizeInstrucao) / 2;
    int yInstrucao = screenH / 2;

    DrawText(instrucao, xInstrucao, yInstrucao, fontSizeInstrucao, BLACK);
    if (IsKeyPressed(KEY_ENTER))
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

    const char *instrucao = "Pressione ENTER para ganhar, DELETE para perder";
    int fontSizeInstrucao = 20;

    // 2. Centralização da Instrução (calcula no momento do desenho)
    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();
    int xInstrucao = screenW / 2 - MeasureText(instrucao, fontSizeInstrucao) / 2;
    int yInstrucao = screenH / 2;

    DrawText(instrucao, xInstrucao, yInstrucao, fontSizeInstrucao, BLACK);
    if (IsKeyPressed(KEY_ENTER))
    {
        //Talvez valha a pena fazer uma função somente para isso
        Sstate->currentScreen = WINNING;
        Sstate->map.currentScreen = WINNING;
    }
    else if (IsKeyPressed(KEY_DELETE))
    {
        Sstate->currentScreen = LOSING;
        Sstate->map.currentScreen = LOSING;
    }

    EndDrawing();
}
void draWinning(screen *Sstate){
    BeginDrawing();
    DrawScene(&Sstate->map);

    const char *instrucao = "ENTER para voltar para o menu principal";
    int fontSizeInstrucao = 20;

    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();
    int xInstrucao = screenW / 2 - MeasureText(instrucao, fontSizeInstrucao) / 2;
    int yInstrucao = screenH / 2;

    DrawText(instrucao, xInstrucao, yInstrucao, fontSizeInstrucao, BLACK);
    if (IsKeyPressed(KEY_ENTER))
    {
        Sstate->currentScreen = MENU;
        Sstate->map.currentScreen = MENU;
    }

    EndDrawing();
}
void drawLosing(screen *Sstate){
    BeginDrawing();
    DrawScene(&Sstate->map);

    const char *instrucao = "ENTER para voltar para o menu principal";
    int fontSizeInstrucao = 20;

    int screenW = GetScreenWidth();
    int screenH = GetScreenHeight();
    int xInstrucao = screenW / 2 - MeasureText(instrucao, fontSizeInstrucao) / 2;
    int yInstrucao = screenH / 2;

    DrawText(instrucao, xInstrucao, yInstrucao, fontSizeInstrucao, BLACK);
    if (IsKeyPressed(KEY_ENTER))
    {
        Sstate->currentScreen = MENU;
        Sstate->map.currentScreen = MENU;
    }

    EndDrawing();
}

