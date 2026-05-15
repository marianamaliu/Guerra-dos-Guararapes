#include <raylib.h>
#include "scene.h"
#include "game.h"
#include "enemy.h"
#include "gameInitEntities.h"
#include "gameInitScreen.h"
#include <math.h> // Para fminf
#include <time.h>
#include <float.h> // Necessário para DBL_MAX
#include <string.h>
#include <stdio.h>

// Sempre que precisar compilar para gerar um novo executável com as alterações, o comando é:
// gcc main.c src/*.c -I include -I /opt/homebrew/include -o blinky.exe -L /opt/homebrew/lib -lraylib -std=c99  

int main(int argc, char const *argv[])
{
    screenState screenState = iniciandoGame();

    // iniciando telas
    InitScene(&screenState.map1, "assets/image.png");

    while (!WindowShouldClose())
    {
        switch (screenState.currentScreen){

            case MENU:
            {
                drawMenu(&screenState);
            }
            break;


            case LORE:
            {
                drawLore(&screenState);
            }
            break;

            case GAMEPLAY:
            {
                drawGameplay(&screenState);
            }
            break;

            case WINNING:
            {
                draWinning(&screenState);
            }
            break;

            case LOSING:
            {
                drawLosing(&screenState);
            }
            break;

        }

    }
    
    // removendo texturas
    UnloadTexture(screenState.map1.map);
    CloseWindow();
    
    return 0;
}
