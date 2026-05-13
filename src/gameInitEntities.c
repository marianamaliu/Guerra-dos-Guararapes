#include "game.h"
#include "enemy.h"

typedef struct {
    
    Enemy enemy1;
    Enemy enemy2;
    Enemy enemy3;
    Enemy enemy4;

    bool isInitiated;
} entityState;

entityState iniciandoEntidades() {
    entityState state;
    state.enemy2.color = PURPLE;

    return state;
}

// Faz a proporção da escala corretamente
Vector2 AdjustPosition(float x, float y) {
    float scaleX = GetScreenWidth() / 1920.0f;
    float scaleY = GetScreenHeight() / 1080.0f;
    
    return (Vector2){x * scaleX, y * scaleY};
}

bool iniciandoInimigos(entityState *entityState){
    TraceLog(LOG_INFO, "JOGO: Cena de Jogo iniciada.");


    // Inimigo[1]
    InitEnemy(&entityState->enemy1, AdjustPosition(221.0f, 466.0f), 100.0f, "assets/ghost_cream.png");
    AddWaypoint(&entityState->enemy1, AdjustPosition(422.0f, 633.0f));
    AddWaypoint(&entityState->enemy1, AdjustPosition(628.0f, 772.0f));
    AddWaypoint(&entityState->enemy1, AdjustPosition(864.0f, 858.0f));
    AddWaypoint(&entityState->enemy1, AdjustPosition(1125.0f, 914.0f));
    AddWaypoint(&entityState->enemy1, AdjustPosition(1295.0f, 849.0f));
    AddWaypoint(&entityState->enemy1, AdjustPosition(1509.0f, 691.0f));
    AddWaypoint(&entityState->enemy1, AdjustPosition(1633.0f, 660.0f));

    // Inimigo[2]
    InitEnemy(&entityState->enemy2, AdjustPosition(1370.0f, 310.0f), 80.0f, "assets/ghost_cream.png");
    AddWaypoint(&entityState->enemy2, AdjustPosition(1255.0f, 397.0f));
    AddWaypoint(&entityState->enemy2, AdjustPosition(1147.0f, 448.0f));
    AddWaypoint(&entityState->enemy2, AdjustPosition(1331.0f, 522.0f));
    AddWaypoint(&entityState->enemy2, AdjustPosition(1211.0f, 451.0f));
    AddWaypoint(&entityState->enemy2, AdjustPosition(1077.0f, 412.0f));
    AddWaypoint(&entityState->enemy2, AdjustPosition(953.0f, 352.0f));
    AddWaypoint(&entityState->enemy2, AdjustPosition(959.0f, 211.0f));

    // Inimigo[3]
    InitEnemy(&entityState->enemy3, AdjustPosition(916.0f, 298.0f), 80.0f, "assets/ghost_cream.png");
    AddWaypoint(&entityState->enemy3, AdjustPosition(761.0f, 391.0f));
    AddWaypoint(&entityState->enemy3, AdjustPosition(673.0f, 461.0f));
    AddWaypoint(&entityState->enemy3, AdjustPosition(608.0f, 389.0f));
    AddWaypoint(&entityState->enemy3, AdjustPosition(608.0f, 482.0f));
    AddWaypoint(&entityState->enemy3, AdjustPosition(503.0f, 566.0f));
    AddWaypoint(&entityState->enemy3, AdjustPosition(419.0f, 654.0f));
    AddWaypoint(&entityState->enemy3, AdjustPosition(534.0f, 722.0f));

    // Inimigo[4]
    InitEnemy(&entityState->enemy4, AdjustPosition(1516.0f, 692.0f), 80.0f, "assets/ghost_cream.png");
    AddWaypoint(&entityState->enemy4, AdjustPosition(1419.0f, 596.0f));
    AddWaypoint(&entityState->enemy4, AdjustPosition(1300.0f, 487.0f));
    AddWaypoint(&entityState->enemy4, AdjustPosition(1559.0f, 682.0f));
    AddWaypoint(&entityState->enemy4, AdjustPosition(1749.0f, 685.0f));
    AddWaypoint(&entityState->enemy4, AdjustPosition(1851.0f, 585.0f));
    AddWaypoint(&entityState->enemy4, AdjustPosition(1863.0f, 498.0f));

    return true;
}