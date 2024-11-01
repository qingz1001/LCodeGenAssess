#include <stdio.h>
#include <math.h>

#define MAX_STATIONS 6

int main() {
    double D1, C, D2, P;
    int N;
    scanf("%lf %lf %lf %lf %d", &D1, &C, &D2, &P, &N);

    if (D1 > C * D2) {
        printf("No Solution\n");
        return 0;
    }

    double total_cost = 0.0;
    double current_fuel = 0.0;
    double distance_traveled = 0.0;

    for (int i = 0; i <= N; i++) {
        double next_distance = (i == N) ? D1 : 0.0;
        double next_price = (i == N) ? 0.0 : 0.0;
        if (i < N) {
            scanf("%lf %lf", &next_distance, &next_price);
        }

        double fuel_needed = (next_distance - distance_traveled) / D2;
        if (fuel_needed + current_fuel > C) {
            double refuel_amount = C - current_fuel;
            total_cost += refuel_amount * P;
            current_fuel = C;
        }
        current_fuel -= fuel_needed;
        distance_traveled = next_distance;

        if (distance_traveled >= D1) {
            break;
        }
    }

    if (distance_traveled < D1) {
        printf("No Solution\n");
        return 0;
    }

    printf("%.2f\n", total_cost);
    return 0;
}