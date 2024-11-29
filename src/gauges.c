#include "gauges.h"
#include "raylib.h"
#include "rlgl.h"
#include <math.h>

void DrawCircularGauge(Vector2 gaugeCenter) {
    float innerRadius = 195.0f;
    float outerRadius = 200.0f;
    float startAngle = -40.0f;
    float endAngle = -320.0f;
    int segments = 180;

    DrawRing(gaugeCenter, innerRadius, outerRadius, startAngle, endAngle, segments, SKYBLUE);
    DrawRing(gaugeCenter, innerRadius-10, outerRadius-10, startAngle, endAngle, segments, WHITE);
    DrawRing(gaugeCenter, innerRadius-100, outerRadius-100, startAngle+22.5, endAngle-22.5, segments, SKYBLUE);
}

void DrawSemiCircularGauge(Vector2 gaugeCenter, bool left) {
    float innerRadius = 205.0f;
    float outerRadius = 215.0f;
    float startAngle = -220.0f;
    float endAngle = -320.0f;
    int segments = 180;

    if (!left) {
        startAngle *= -1;
        endAngle *= -1;
    }

    DrawRing(gaugeCenter, innerRadius, outerRadius, startAngle, endAngle, segments, WHITE);
}

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
	int numSteps = 5;

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
