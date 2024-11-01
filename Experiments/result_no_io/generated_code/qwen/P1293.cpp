#include <stdio.h>
#include <string.h>

#define MAX_CITIES 150
#define MAX_NAME_LENGTH 50

typedef struct {
    int num_students;
    int distance_from_moscow;
    char name[MAX_NAME_LENGTH];
} City;

int main() {
    City cities[MAX_CITIES];
    int n, i;
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        scanf("%d %d %s", &cities[i].num_students, &cities[i].distance_from_moscow, cities[i].name);
    }

    int min_cost = 10000 * 50; // Maximum possible cost
    int best_city_index = -1;

    for (i = 0; i < n; i++) {
        if (cities[i].distance_from_moscow == 0) continue; // Skip Moscow itself

        int total_cost = cities[i].distance_from_moscow * cities[i].num_students;
        if (total_cost < min_cost || (total_cost == min_cost && strcmp(cities[i].name, "Moscow") < 0)) {
            min_cost = total_cost;
            best_city_index = i;
        }
    }

    printf("%s %d\n", cities[best_city_index].name, min_cost);

    return 0;
}