#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_CITIES 150
#define MAX_NAME_LENGTH 50

typedef struct {
    int students;
    int distance;
    char name[MAX_NAME_LENGTH];
} City;

int main() {
    City cities[MAX_CITIES];
    int total_cities = 0;
    int total_students = 0;

    while (1) {
        City city;
        if (scanf("%d %d %s", &city.students, &city.distance, city.name) != 3) {
            break;
        }
        cities[total_cities++] = city;
        total_students += city.students;
    }

    int min_cost = INT_MAX;
    int best_city = 0;

    for (int i = 0; i < total_cities; i++) {
        int cost = 0;
        for (int j = 0; j < total_cities; j++) {
            cost += abs(cities[i].distance - cities[j].distance) * cities[j].students;
        }
        if (cost < min_cost || (cost == min_cost && cities[i].distance < cities[best_city].distance)) {
            min_cost = cost;
            best_city = i;
        }
    }

    printf("%s %d\n", cities[best_city].name, min_cost);

    return 0;
}