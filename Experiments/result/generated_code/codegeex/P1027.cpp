#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_CITIES 100
#define MAX_COORD 20

typedef struct {
    int x, y;
} Point;

typedef struct {
    double cost;
    int prev_city;
    int prev_airport;
} AirportInfo;

Point cities[MAX_CITIES][4];
double rail_costs[MAX_CITIES];
double flight_cost;
int num_cities;

double calculate_distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double calculate_cost(int start_city, int start_airport, int end_city, int end_airport) {
    double cost = 0.0;
    cost += calculate_distance(cities[start_city][start_airport], cities[end_city][end_airport]) * rail_costs[end_city];
    return cost;
}

int main() {
    int num_tests;
    scanf("%d", &num_tests);

    while (num_tests--) {
        scanf("%d %lf %d %d", &num_cities, &flight_cost, &A, &B);

        for (int i = 0; i < num_cities; i++) {
            scanf("%d %d %d %d %d %d %lf", &cities[i][0].x, &cities[i][0].y, &cities[i][1].x, &cities[i][1].y, &cities[i][2].x, &cities[i][2].y, &rail_costs[i]);
        }

        double min_cost = INFINITY;
        for (int start_airport = 0; start_airport < 4; start_airport++) {
            for (int end_airport = 0; end_airport < 4; end_airport++) {
                double cost = calculate_distance(cities[A-1][start_airport], cities[B-1][end_airport]) * flight_cost;
                if (cost < min_cost) {
                    min_cost = cost;
                }
            }
        }

        printf("%.1lf\n", min_cost);
    }

    return 0;
}