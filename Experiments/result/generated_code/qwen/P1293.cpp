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
    int n = 0;

    while (scanf("%d %d %s", &cities[n].num_students, &cities[n].distance_from_moscow, cities[n].name) != EOF) {
        if (strcmp(cities[n].name, "Moscow") == 0) {
            break;
        }
        n++;
    }

    int min_cost = INT_MAX;
    char best_city[MAX_NAME_LENGTH];

    for (int i = 0; i < n; i++) {
        int cost = cities[i].num_students * cities[i].distance_from_moscow;
        if (cost < min_cost || (cost == min_cost && strcmp(cities[i].name, best_city) < 0)) {
            min_cost = cost;
            strcpy(best_city, cities[i].name);
        }
    }

    printf("%s %d\n", best_city, min_cost);

    return 0;
}