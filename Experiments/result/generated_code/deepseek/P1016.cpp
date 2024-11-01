#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 6

typedef struct {
    double distance;
    double price;
} GasStation;

int compare(const void *a, const void *b) {
    return ((GasStation *)a)->distance - ((GasStation *)b)->distance;
}

int main() {
    double D1, C, D2, P;
    int N;
    scanf("%lf %lf %lf %lf %d", &D1, &C, &D2, &P, &N);

    GasStation stations[MAX_N + 1];
    stations[0].distance = 0;
    stations[0].price = P;

    for (int i = 1; i <= N; i++) {
        scanf("%lf %lf", &stations[i].distance, &stations[i].price);
    }

    qsort(stations, N + 1, sizeof(GasStation), compare);

    double total_cost = 0.0;
    double current_fuel = 0.0;
    double max_distance = C * D2;

    for (int i = 0; i <= N; i++) {
        if (i > 0 && stations[i].distance - stations[i - 1].distance > max_distance) {
            printf("No Solution\n");
            return 0;
        }

        if (i > 0) {
            double distance_to_next = (i == N) ? D1 - stations[i - 1].distance : stations[i].distance - stations[i - 1].distance;
            double fuel_needed = distance_to_next / D2;

            if (current_fuel < fuel_needed) {
                double fuel_to_buy = fuel_needed - current_fuel;
                total_cost += fuel_to_buy * stations[i - 1].price;
                current_fuel = fuel_needed;
            }
            current_fuel -= fuel_needed;
        }

        if (i < N) {
            double min_price = stations[i].price;
            int min_price_index = i;
            for (int j = i + 1; j <= N && stations[j].distance - stations[i].distance <= max_distance; j++) {
                if (stations[j].price < min_price) {
                    min_price = stations[j].price;
                    min_price_index = j;
                }
            }

            if (min_price_index != i) {
                double distance_to_min_price = stations[min_price_index].distance - stations[i].distance;
                double fuel_needed = distance_to_min_price / D2;
                if (current_fuel < fuel_needed) {
                    double fuel_to_buy = fuel_needed - current_fuel;
                    total_cost += fuel_to_buy * stations[i].price;
                    current_fuel = fuel_needed;
                }
            } else {
                double fuel_to_buy = C - current_fuel;
                total_cost += fuel_to_buy * stations[i].price;
                current_fuel = C;
            }
        }
    }

    if (D1 - stations[N].distance > max_distance) {
        printf("No Solution\n");
    } else {
        double distance_to_end = D1 - stations[N].distance;
        double fuel_needed = distance_to_end / D2;
        if (current_fuel < fuel_needed) {
            double fuel_to_buy = fuel_needed - current_fuel;
            total_cost += fuel_to_buy * stations[N].price;
        }
        printf("%.2lf\n", total_cost);
    }

    return 0;
}