#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 1000
#define EPSILON 1e-6

typedef struct {
    double w, x, y, p, q;
} Shrimp;

typedef struct {
    double t, x, y;
    int s;
} EatEvent;

double w0, V, T, x0, y0;
int n;
Shrimp shrimps[MAX_N];
EatEvent events[MAX_N];
int eventCount = 0;

double calculateDistance(double x1, double y1, double x2, double y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

double calculateTimeToCatch(double x0, double y0, double x, double y, double p, double q, double V) {
    double a = (p * p + q * q - V * V);
    double b = 2 * (p * (x - x0) + q * (y - y0));
    double c = (x - x0) * (x - x0) + (y - y0) * (y - y0);
    double discriminant = b * b - 4 * a * c;
    if (discriminant < 0) return -1;
    double t1 = (-b + sqrt(discriminant)) / (2 * a);
    double t2 = (-b - sqrt(discriminant)) / (2 * a);
    if (t1 < 0) return t2;
    if (t2 < 0) return t1;
    return fmin(t1, t2);
}

void simulate() {
    double currentWeight = w0;
    double currentX = x0, currentY = y0;
    double currentTime = 0;

    while (currentTime < T) {
        double minTime = T;
        int minIndex = -1;

        for (int i = 0; i < n; i++) {
            if (shrimps[i].w < currentWeight) {
                double t = calculateTimeToCatch(currentX, currentY, shrimps[i].x, shrimps[i].y, shrimps[i].p, shrimps[i].q, V);
                if (t >= 0 && t < minTime) {
                    minTime = t;
                    minIndex = i;
                }
            }
        }

        if (minIndex == -1) break;

        currentTime += minTime;
        currentX = shrimps[minIndex].x + shrimps[minIndex].p * minTime;
        currentY = shrimps[minIndex].y + shrimps[minIndex].q * minTime;
        events[eventCount].t = currentTime;
        events[eventCount].x = currentX;
        events[eventCount].y = currentY;
        events[eventCount].s = minIndex + 1;
        eventCount++;

        currentWeight += shrimps[minIndex].w;
        shrimps[minIndex].w = 0; // Mark as eaten
    }
}

int main() {
    FILE *inputFile = fopen("nemo1.in", "r");
    FILE *outputFile = fopen("nemo1.out", "w");

    fscanf(inputFile, "%lf %lf %lf %lf %lf", &w0, &V, &T, &x0, &y0);
    fscanf(inputFile, "%d", &n);

    for (int i = 0; i < n; i++) {
        fscanf(inputFile, "%lf %lf %lf %lf %lf", &shrimps[i].w, &shrimps[i].x, &shrimps[i].y, &shrimps[i].p, &shrimps[i].q);
    }

    simulate();

    fprintf(outputFile, "%d\n", eventCount);
    double totalWeight = 0;
    for (int i = 0; i < eventCount; i++) {
        totalWeight += shrimps[events[i].s - 1].w;
    }
    fprintf(outputFile, "%.6f\n", totalWeight);
    for (int i = 0; i < eventCount; i++) {
        fprintf(outputFile, "%.6f %.6f %.6f %d\n", events[i].t, events[i].x, events[i].y, events[i].s);
    }

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}