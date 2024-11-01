#include <stdio.h>
#include <stdlib.h>

#define MAX_STATIONS 7

typedef struct {
    double distance;
    double price;
} Station;

double calculate_min_cost(double D1, double C, double D2, double P, int N, Station stations[]) {
    int current_station = 0;
    double total_cost = 0.0;
    double current_fuel = 0.0;

    while (current_station < N) {
        int next_station = current_station + 1;
        double max_distance = C * D2;

        // 找到下一个可以到达的油价最低的加油站
        while (next_station < N && stations[next_station].distance - stations[current_station].distance <= max_distance) {
            next_station++;
        }

        // 如果无法到达下一个加油站，输出"No Solution"
        if (next_station == current_station) {
            printf("No Solution\n");
            return -1.0;
        }

        // 如果可以到达下一个加油站，计算到达的油价最低的加油站
        int min_price_station = current_station;
        double min_price = stations[current_station].price;
        for (int i = current_station + 1; i < next_station; i++) {
            if (stations[i].price < min_price) {
                min_price_station = i;
                min_price = stations[i].price;
            }
        }

        // 如果最低油价加油站的价格高于当前加油站的价格，需要加满油
        if (stations[min_price_station].price > stations[current_station].price) {
            double needed_fuel = (stations[min_price_station].distance - stations[current_station].distance) / D2;
            if (needed_fuel > C) {
                printf("No Solution\n");
                return -1.0;
            }
            total_cost += stations[current_station].price * (needed_fuel - current_fuel);
            current_fuel = 0.0;
        }

        // 沿路加满油，前往最低油价加油站
        total_cost += stations[current_station].price * (C - current_fuel);
        current_fuel = C;
        current_station = min_price_station;
    }

    // 加油到最后一个加油站
    total_cost += stations[current_station].price * ((D1 - stations[current_station].distance) / D2 - current_fuel);
    return total_cost;
}

int main() {
    double D1, C, D2, P;
    int N;
    Station stations[MAX_STATIONS];

    scanf("%lf %lf %lf %lf %d", &D1, &C, &D2, &P, &N);

    stations[0].distance = 0.0;
    stations[0].price = P;

    for (int i = 1; i <= N; i++) {
        scanf("%lf %lf", &stations[i].distance, &stations[i].price);
    }

    double min_cost = calculate_min_cost(D1, C, D2, P, N, stations);
    if (min_cost != -1.0) {
        printf("%.2lf\n", min_cost);
    }

    return 0;
}