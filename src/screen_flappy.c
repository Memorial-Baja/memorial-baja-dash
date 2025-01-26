#include <stdio.h> 
#include <math.h>
#include <raylib.h>
#include <rlgl.h>
#include "screens.h"
#include "gauges.h"
#include "debug.h"

static int framesCounter = 0;
static int finishScreen = 0;
Vector2 birdPosition = { 50.0f, 300.0f };
static float birdVelocity = 0.0f;
static const float gravityForce = 0.5f;
static const float jumpForce = -8.0f;
Image bird;
// Texture2D texture;

void gravity(void) {
    birdVelocity += gravityForce;
    birdPosition.y += birdVelocity;
}

void birdJump(void) {
    birdVelocity = jumpForce;
}

// Flappy Screen Initialization logic
void InitFlappyScreen(void) {
    framesCounter = 0;
    finishScreen = 0;
	birdVelocity = 0.0f;
	bird = LoadImage("resources/andy.png");
    // texture = LoadTextureFromImage(bird);
}

// Flappy Screen Update logic
void UpdateFlappyScreen(void) {
	if (IsKeyPressed(KEY_SPACE)) birdJump();
	gravity();
}

// Flappy Screen Draw logic
void DrawFlappyScreen(void) {
	DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), BLACK);
	// DrawTextureEx(texture, birdPosition, 0.0f, 0.085f, WHITE);
	DrawText(TextFormat("Framescounter %i", framesCounter), 10, 50, 10, MAROON);
}

// Flappy Screen Unload logic
void UnloadFlappyScreen(void) {
	UnloadImage(bird);
	// UnloadTexture(texture);
    // TODO: Unload TITLE screen variables here!
}

// Flappy Screen should finish?
int FinishFlappyScreen(void) {
    return finishScreen;
}
