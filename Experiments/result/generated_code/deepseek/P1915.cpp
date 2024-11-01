#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 1000

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

int canEat(int i, double t) {
    double shrimpX = shrimps[i].x + shrimps[i].p * t;
    double shrimpY = shrimps[i].y + shrimps[i].q * t;
    double distance = calculateDistance(x0, y0, shrimpX, shrimpY);
    double timeToReach = distance / V;
    return timeToReach <= t && shrimps[i].w < w0;
}

void simulate() {
    double currentTime = 0;
    while (currentTime <= T) {
        int bestShrimp = -1;
        double bestTime = T + 1;
        for (int i = 0; i < n; i++) {
            if (canEat(i, currentTime)) {
                double shrimpX = shrimps[i].x + shrimps[i].p * currentTime;
                double shrimpY = shrimps[i].y + shrimps[i].q * currentTime;
                double distance = calculateDistance(x0, y0, shrimpX, shrimpY);
                double timeToReach = distance / V;
                if (timeToReach < bestTime) {
                    bestTime = timeToReach;
                    bestShrimp = i;
                }
            }
        }
        if (bestShrimp != -1) {
            double shrimpX = shrimps[bestShrimp].x + shrimps[bestShrimp].p * currentTime;
            double shrimpY = shrimps[bestShrimp].y + shrimps[bestShrimp].q * currentTime;
            events[eventCount].t = currentTime + bestTime;
            events[eventCount].x = shrimpX;
            events[eventCount].y = shrimpY;
            events[eventCount].s = bestShrimp + 1;
            eventCount++;
            w0 += shrimps[bestShrimp].w;
            x0 = shrimpX;
            y0 = shrimpY;
            currentTime += bestTime;
        } else {
            break;
        }
    }
}

int main() {
    FILE *input = fopen("nemo1.in", "r");
    FILE *output = fopen("nemo1.out", "w");

    fscanf(input, "%lf %lf %lf %lf %lf", &w0, &V, &T, &x0, &y0);
    fscanf(input, "%d", &n);
    for (int i = 0; i < n; i++) {
        fscanf(input, "%lf %lf %lf %lf %lf", &shrimps[i].w, &shrimps[i].x, &shrimps[i].y, &shrimps[i].p, &shrimps[i].q);
    }

    simulate();

    fprintf(output, "%d\n", eventCount);
    fprintf(output, "%.6f\n", w0 - w0);
    for (int i = 0; i < eventCount; i++) {
        fprintf(output, "%.6f %.6f %.6f %d\n", events[i].t, events[i].x, events[i].y, events[i].s);
    }

    fclose(input);
    fclose(output);
    return 0;
}