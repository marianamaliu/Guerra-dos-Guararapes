#include "game.h"
#include "enemy.h"
#include <raylib.h>

typedef struct {
    GameScreen currentScreen;
    Scene map1; // bug de versão
    bool showDebug;
    int cliques;
} screenState;

screenState iniciandoGame() {
    screenState state;
    state.currentScreen = INITIALIZE;
    state.cliques = 1;
    state.showDebug = true;

    int WINDOW_WIDTH = GetMonitorWidth(0);
    int WINDOW_HEIGHT = GetMonitorHeight(0);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "blinky");
    SetTargetFPS(60);

    return state;
}
