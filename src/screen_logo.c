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

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

static int logoPositionX = 0;
static int logoPositionY = 0;

static int lettersCount = 0;

static int topSideRecWidth = 0;
static int leftSideRecHeight = 0;

static int bottomSideRecWidth = 0;
static int rightSideRecHeight = 0;

static int state = 0;              // Logo animation states
static float alpha = 1.0f;         // Useful for fading

Image logo;
Texture2D texture;
//----------------------------------------------------------------------------------
// Logo Screen Functions Definition
//----------------------------------------------------------------------------------

// Logo Screen Initialization logic
void InitLogoScreen(void)
{
    logo = LoadImage("resources/baja_logo_1.png");
    texture = LoadTextureFromImage(logo);
    finishScreen = 0;
    framesCounter = 0;
    lettersCount = 0;

    logoPositionX = GetScreenWidth()/2 - 128;
    logoPositionY = GetScreenHeight()/2 - 128;

    topSideRecWidth = 16;
    leftSideRecHeight = 16;
    bottomSideRecWidth = 16;
    rightSideRecHeight = 16;

    state = 0;
    alpha = 1.0f;
}

// Logo Screen Update logic
void UpdateLogoScreen(void)
{
    finishScreen = 1;
    if (state == 0)                 // State 0: Top-left square corner blink logic
    {
        framesCounter++;

        if (framesCounter == 80)
        {
            state = 1;
            framesCounter = 0;      // Reset counter... will be used later...
        }
    }
    else if (state == 1)            // State 1: Bars animation logic: top and left
    {
        topSideRecWidth += 8;
        leftSideRecHeight += 8;

        if (topSideRecWidth == 256) state = 2;
    }
    else if (state == 2)            // State 2: Bars animation logic: bottom and right
    {
        bottomSideRecWidth += 8;
        rightSideRecHeight += 8;

        if (bottomSideRecWidth == 256) state = 3;
    }
    else if (state == 3)            // State 3: "raylib" text-write animation logic
    {
        framesCounter++;

        if (lettersCount < 10)
        {
            if (framesCounter/12)   // Every 12 frames, one more letter!
            {
                lettersCount++;
                framesCounter = 0;
            }
        }
        else    // When all letters have appeared, just fade out everything
        {
            if (framesCounter > 200)
            {
                alpha -= 0.02f;

                if (alpha <= 0.0f)
                {
                    alpha = 0.0f;
                    finishScreen = 1;   // Jump to next screen
                }
            }
        }
    }
}

// Logo Screen Draw logic
void DrawLogoScreen(void) {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
    DrawTexture(texture, GetScreenWidth()/2 - texture.width/2, GetScreenHeight()/2 - texture.height/2 - 40, WHITE);
}

// Logo Screen Unload logic
void UnloadLogoScreen(void) {
    // Unload LOGO screen variables here!
}

// Logo Screen should finish?
int FinishLogoScreen(void) {
    return finishScreen;
}
