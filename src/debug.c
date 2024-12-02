#include <raylib.h>
#include "debug.h"

void debugGaugeControls(int *speed, int *rpm) {
	if (IsKeyDown(KEY_UP)) *speed += 1;
	if (IsKeyDown(KEY_DOWN)) *speed -= 1;
	if (IsKeyDown(KEY_RIGHT)) *rpm += 67;
	if (IsKeyDown(KEY_LEFT)) *rpm -= 67;
}