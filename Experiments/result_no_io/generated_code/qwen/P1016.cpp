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
    double next_station_distance = 0.0;
    double next_station_price = 0.0;

    for (int i = 0; i <= N; i++) {
        if (i == N) {
            next_station_distance = D1;
            next_station_price = P;
        } else {
            scanf("%lf %lf", &next_station_distance, &next_station_price);
        }

        double distance_to_next_station = next_station_distance - current_fuel * D2;
        if (distance_to_next_station > C * D2) {
            printf("No Solution\n");
            return 0;
        }

        double fuel_needed = distance_to_next_station / D2;
        if (fuel_needed > current_fuel) {
            total_cost += (current_fuel * D2 - current_fuel * D2) * P;
            current_fuel = 0.0;
            while (current_fuel < fuel_needed && i < N) {
                double fuel_to_buy = fmin(fuel_needed - current_fuel, C);
                total_cost += fuel_to_buy * next_station_price;
                current_fuel += fuel_to_buy;
                i++;
                if (i < N) {
                    scanf("%lf %lf", &next_station_distance, &next_station_price);
                }
            }
        }

        if (current_fuel < fuel_needed) {
            printf("No Solution\n");
            return 0;
        }

        current_fuel -= fuel_needed;
    }

    printf("%.2f\n", total_cost);
    return 0;
}