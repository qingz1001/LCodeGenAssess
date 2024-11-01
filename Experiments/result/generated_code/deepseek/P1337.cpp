#include <stdio.h>
#include <math.h>

#define MAXN 1000
#define EPS 1e-6

typedef struct {
    int x, y, w;
} Point;

Point points[MAXN];
int n;

double calculateEnergy(double x, double y) {
    double energy = 0;
    for (int i = 0; i < n; i++) {
        double dx = x - points[i].x;
        double dy = y - points[i].y;
        energy += points[i].w * sqrt(dx * dx + dy * dy);
    }
    return energy;
}

void simulatedAnnealing() {
    double x = 0, y = 0;
    double t = 1000;
    double delta = 0.98;
    double bestX = x, bestY = y;
    double bestEnergy = calculateEnergy(x, y);

    while (t > EPS) {
        double newX = x + (rand() * 2.0 / RAND_MAX - 1) * t;
        double newY = y + (rand() * 2.0 / RAND_MAX - 1) * t;
        double newEnergy = calculateEnergy(newX, newY);

        if (newEnergy < bestEnergy) {
            bestX = newX;
            bestY = newY;
            bestEnergy = newEnergy;
        }

        if (newEnergy < calculateEnergy(x, y) || exp((calculateEnergy(x, y) - newEnergy) / t) > rand() * 1.0 / RAND_MAX) {
            x = newX;
            y = newY;
        }

        t *= delta;
    }

    printf("%.3f %.3f\n", bestX, bestY);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &points[i].x, &points[i].y, &points[i].w);
    }

    simulatedAnnealing();

    return 0;
}