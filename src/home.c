#include <stdio.h>
#include <string.h>
#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define BACKGROUND_COLOR (Color){34, 40, 49, 255}   // Azul escuro
#define BUTTON_FRAME_COLOR (Color){70, 52, 38, 255} // Marrom escuro
#define BUTTON_BG_COLOR (Color){44, 48, 55, 255}    // Cinza escuro
#define TEXT_COLOR (Color){190, 180, 160, 255}      // Bege claro
#define HOVER_COLOR (Color){255, 255, 255, 255}     // Branco

#define TITLE_FONT_SIZE 60
#define BUTTON_FONT_SIZE 30
#define BUTTON_PADDING 20
#define BUTTON_SPACING 30

typedef struct
{
    Rectangle rect;
    const char *text;
    Color color;
    int fontSize;
} Button;

Button startButton;
Button scoresButton;

Rectangle CreateCenteredButton(int totalWidth, int totalHeight, int buttonWidth, int buttonHeight, int yOffset)
{
    return (Rectangle){
        (totalWidth - buttonWidth) / 2.0f,
        (totalHeight / 2.0f) + yOffset,
        buttonWidth,
        buttonHeight};
}