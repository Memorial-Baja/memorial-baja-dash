#include <stdio.h> 
#include <math.h>
#include <raylib.h>
#include <rlgl.h>
#include "screens.h"
#include "gauges.h"
#include "debug.h"

static int framesCounter = 0;
static int finishScreen = 0;
static float heightOffset = 30.0f;
int rpm = 0;
const int rpmMax = 5000;
int speed = 0;
const int speedMax = 75;
float temp = 0;
float voltage = 6;
bool maxAngle = false;
bool sweepFinished = false;

// Main Screen Initialization logic
void InitMainScreen(void) {
    framesCounter = 0;
    finishScreen = 0;
}

// Main Screen Update logic
void UpdateMainScreen(void) {
    if (!sweepFinished) gaugeSweep(&speed, &rpm, speedMax, &maxAngle, &sweepFinished);
    if (DEBUG) debugGaugeControls(&speed, &rpm);
}

// Main Screen Draw logic
void DrawMainScreen(void) {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);

    // LEFT HAND SIDE ( RPM )
    Vector2 speedCenter = { (GetScreenWidth() / 4.0f), (GetScreenHeight() / 2.0f) + heightOffset };
    Vector2 rpmCenter = { (GetScreenWidth() / 1.35f), (GetScreenHeight() / 2.0f) + heightOffset };

    DrawRectangle(speedCenter.x, speedCenter.y-160, rpmCenter.x-speedCenter.x, 320, (Color){102, 191, 255, 155});

    DrawCircularGauge(speedCenter, &speed, speedMax, "KM/H", &font);
    DrawSemiCircularGauge(speedCenter, true);
    calculateSpeedLocations(speedCenter.x, speedCenter.y-10, 160, -223.5f, 41.5f, &font);

    DrawCircularGauge(rpmCenter, &rpm, rpmMax, "RPM", &font);
    DrawSemiCircularGauge(rpmCenter, false);
    calculateRPMLocations(rpmCenter.x, rpmCenter.y-10, 160, -223.5f, 41.5f, &font);
}

// Main Screen Unload logic
void UnloadMainScreen(void) {
    // TODO: Unload TITLE screen variables here!
}

// Main Screen should finish?
int FinishMainScreen(void) {
    return finishScreen;
}
