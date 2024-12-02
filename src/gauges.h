#include "raylib.h"

void DrawCircularGauge(Vector2 gaugeCenter, int *metric, int metricMax, const char *metricLabel, Font *font);

void DrawSemiCircularGauge(Vector2 gaugeCenter, bool left);

void DrawNeedle(Vector2 gaugeCenter, int measurement, int maxMeasurement);

void calculateSpeedLocations(double centerX, double centerY, double radius, double startAngle, double endAngle, Font *font);

void calculateRPMLocations(double centerX, double centerY, double radius, double startAngle, double endAngle, Font *font);

void gaugeSweep(int *speed, int *rpm, int speedMax, bool *maxAngle, bool *sweepFinished);
