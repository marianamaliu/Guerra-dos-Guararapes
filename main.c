#include <raylib.h>
#include "scene.h"
#include "game.h"
#include "gameInitScreens.h"
#include <math.h> // Para fminf
#include <time.h>
#include <float.h> // Necessário para DBL_MAX
#include <string.h>
#include <stdio.h>

// para compilar e executar rapidamente:  make clean && make && ./guararapes.exe

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
