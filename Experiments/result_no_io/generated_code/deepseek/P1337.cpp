#include <stdio.h>
#include <math.h>

#define MAXN 1000

typedef struct {
    int x, y, w;
} Point;

Point points[MAXN];

double calculate_energy(double x, double y, int n) {
    double energy = 0.0;
    for (int i = 0; i < n; i++) {
        double dx = x - points[i].x;
        double dy = y - points[i].y;
        energy += points[i].w * sqrt(dx * dx + dy * dy);
    }
    return energy;
}

void simulated_annealing(int n) {
    double x = 0.0, y = 0.0;
    double temperature = 1000.0;
    double cooling_rate = 0.995;
    double best_x = x, best_y = y;
    double best_energy = calculate_energy(x, y, n);

    while (temperature > 1e-6) {
        double new_x = x + (2.0 * rand() / RAND_MAX - 1.0) * temperature;
        double new_y = y + (2.0 * rand() / RAND_MAX - 1.0) * temperature;
        double new_energy = calculate_energy(new_x, new_y, n);

        if (new_energy < best_energy) {
            best_x = new_x;
            best_y = new_y;
            best_energy = new_energy;
        }

        if (new_energy < calculate_energy(x, y, n) || exp((calculate_energy(x, y, n) - new_energy) / temperature) > (double)rand() / RAND_MAX) {
            x = new_x;
            y = new_y;
        }

        temperature *= cooling_rate;
    }

    printf("%.3f %.3f\n", best_x, best_y);
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &points[i].x, &points[i].y, &points[i].w);
    }
    simulated_annealing(n);
    return 0;
}