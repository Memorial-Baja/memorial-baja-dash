#include "gauges.h"
#include <raylib.h>
#include <rlgl.h>
#include <math.h>

void DrawNeedle(Vector2 gaugeCenter, int measurement, int maxMeasurement) {
    float startAngle = 225.0f;
    float endAngle = -40.0f;
    float angle = startAngle - ((startAngle - endAngle) * measurement/maxMeasurement);

    rlPushMatrix();
        rlTranslatef(gaugeCenter.x, gaugeCenter.y, 0);
        rlRotatef(angle, 0, 0, -1);
        DrawRectangle(0, 0, 165, 5, RED);
    rlPopMatrix();
    DrawCircle(gaugeCenter.x, gaugeCenter.y, 95, BLACK);
}

void DrawCircularGauge(Vector2 gaugeCenter, int* metric, int metricMax, const char *unitLabel, Font *font) {
    float innerRadius = 195.0f;
    float outerRadius = 200.0f;
    float startAngle = 50.0f;
    float endAngle = -230.0f;
    int segments = 180;
    static float heightOffset = 30.0f;
    
    DrawCircle(gaugeCenter.x, gaugeCenter.y, 210, BLACK);
    DrawNeedle(gaugeCenter, *metric, metricMax);
    DrawRing(gaugeCenter, innerRadius, outerRadius, startAngle, endAngle, segments, SKYBLUE);
    DrawRing(gaugeCenter, innerRadius-10, outerRadius-10, startAngle, endAngle, segments, WHITE);
    DrawRing(gaugeCenter, innerRadius-100, outerRadius-100, startAngle+22.5, endAngle-22.5, segments, SKYBLUE);
    DrawTextEx(
        *font,
        unitLabel,
        (Vector2){ (gaugeCenter.x-(MeasureTextEx(*font, unitLabel, 24, 2).x)/2.0f), (((GetScreenHeight())/2.0f)+30.0f)+heightOffset },
        24,
        2,
        RAYWHITE
    );
        DrawTextEx(
        *font,
        TextFormat("%i", *metric),
        (Vector2){ (gaugeCenter.x-(MeasureTextEx(*font, TextFormat("%i", *metric), 64, 2).x)/2.0f), (((GetScreenHeight())/2.0f)-35.0f)+heightOffset },
        64,
        2,
        RAYWHITE
    );
}

void DrawSemiCircularGauge(Vector2 gaugeCenter, bool left) {
    float innerRadius = 205.0f;
    float outerRadius = 215.0f;
    float startAngle = 130.0f;
    float endAngle = 230.0f;
    int segments = 180;

    if (left) {
        startAngle -= -180;
        endAngle -= -180;
    }

    DrawRing(gaugeCenter, innerRadius, outerRadius, startAngle, endAngle, segments, WHITE);
}

void calculateSpeedLocations(double centerX, double centerY, double radius, double startAngle, double endAngle, Font *font) {
	// Convert angles to radians
	startAngle = startAngle * M_PI / 180.0;
	endAngle = endAngle * M_PI / 180.0;

    int initSpeed = 0;

	// Calculate the number of steps
	int numSteps = 15;

	// Calculate the angle increment per step
	double angleIncrement = (endAngle - startAngle) / numSteps;

	// Calculate and print the coordinates
	for (int i = 0; i <= numSteps; i++) {
		double angle = startAngle + i * angleIncrement;
		double x = centerX + radius * cos(angle);
		double y = centerY + radius * sin(angle);

		DrawTextEx(
            *font,
            TextFormat("%i", initSpeed),
            (Vector2){ x-(MeasureTextEx(*font, TextFormat("%i", initSpeed), 24, 2).x)/2.0f, y },
            24,
            2,
            RAYWHITE
        );
        initSpeed += 5;
	}
}

void calculateRPMLocations(double centerX, double centerY, double radius, double startAngle, double endAngle, Font *font) {
	// Convert angles to radians
	startAngle = startAngle * M_PI / 180.0;
	endAngle = endAngle * M_PI / 180.0;

    int initRPM = 0;

	// Calculate the number of steps
	int numSteps = 4;

	// Calculate the angle increment per step
	double angleIncrement = (endAngle - startAngle) / numSteps;

	// Calculate and print the coordinates
	for (int i = 0; i <= numSteps; i++) {
		double angle = startAngle + i * angleIncrement;
		double x = centerX + radius * cos(angle);
		double y = centerY + radius * sin(angle);

		DrawTextEx(
            *font,
            TextFormat("%i", initRPM),
            (Vector2){ x-(MeasureTextEx(*font, TextFormat("%i", initRPM), 24, 2).x)/2.0f, y },
            24,
            2,
            RAYWHITE
        );
        initRPM += 1;
	}
}

void gaugeSweep(int *speed, int *rpm, int speedMax, bool *maxAngle, bool *sweepFinished) {
    if (*speed == speedMax && !*maxAngle) {
        *maxAngle = true;
    } else if (*speed <= 0 && *maxAngle) {
        *speed = 0;
        *rpm = 0;
        *sweepFinished = true;
    } else if (*speed <= speedMax && *maxAngle) {
        *speed -= 1;
        *rpm -= 53;
    } else if(!*maxAngle) {
        *speed += 1;
        *rpm += 53;
    }
}
