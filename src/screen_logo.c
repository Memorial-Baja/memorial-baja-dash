/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Logo Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include "raylib.h"
#include "screens.h"
#include <stdio.h>

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

Image logo;
Texture2D texture;
//----------------------------------------------------------------------------------
// Logo Screen Functions Definition
//----------------------------------------------------------------------------------

// Logo Screen Initialization logic
void InitLogoScreen(void)
{
    logo = LoadImage("resources/baja_logo.png");
    texture = LoadTextureFromImage(logo);
    finishScreen = 0;
    framesCounter = 0;
}

// Logo Screen Update logic
void UpdateLogoScreen(void)
{
    if (framesCounter > 100) {
        finishScreen = 1;
    } else {
        framesCounter++;
    }
}

// Logo Screen Draw logic
void DrawLogoScreen(void) {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
    DrawTexture(texture, GetScreenWidth()/2 - texture.width/2, GetScreenHeight()/2 - texture.height/2 - 40, WHITE);
    DrawText("Loading...", GetScreenWidth()/2-(MeasureTextEx(font, "Loading...", 40, 2).x)/2.0f, GetScreenHeight()/2 + 160, 40, RAYWHITE);
}

// Logo Screen Unload logic
void UnloadLogoScreen(void) {
    UnloadImage(logo);
    UnloadTexture(texture);
    printf("LOGO SCREEN UNLOADED\n");
    // Unload LOGO screen variables here!
}

// Logo Screen should finish?
int FinishLogoScreen(void) {
    return finishScreen;
}
