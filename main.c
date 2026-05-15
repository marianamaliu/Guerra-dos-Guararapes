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
    screen screen = iniciandoGame();

    // iniciando telas
    addScenes(&screen.map);

    while (!WindowShouldClose())
    {
        switch (screen.currentScreen){

            case MENU:
            {
                drawMenu(&screen);
            }
            break;

            case LORE:
            {
                drawLore(&screen);
            }
            break;

            case GAMEPLAY:
            {
                drawGameplay(&screen);
            }
            break;

            case WINNING:
            {
                draWinning(&screen);
            }
            break;

            case LOSING:
            {
                drawLosing(&screen);
            }
            break;

        }

    }
    
    // removendo texturas
    UnloadTexture(screen.map.mapTexture[screen.currentScreen]);
    CloseWindow();
    
    return 0;
}
