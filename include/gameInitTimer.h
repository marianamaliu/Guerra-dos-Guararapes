#ifndef TIMESTATE_H
#define TIMESTATE_H
#include <raylib.h>
#include "scene.h"
#include "enemy.h"

typedef struct{
    double start_time;
    bool scoreCalculated; // Flag para garantir que o tempo só seja medido uma vez
    char scoreText[64];
    char recordText[64];
}timerState;

timerState newTimerState(void);

#endif