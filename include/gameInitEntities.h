#ifndef ENTITY_H
#define ENTITY_H

#include "game.h"
#include "enemy.h"

typedef struct {
   
    Enemy enemy1;
    Enemy enemy2;
    Enemy enemy3;
    Enemy enemy4;
    
    bool isInitiated;
} entityState;

/**
 * @brief Inicializa o estado de todas as entidades do jogo.
 * @return entityState inicializada.
 */
entityState iniciandoEntidades();
bool iniciandoInimigos(entityState *entityState);

#endif 