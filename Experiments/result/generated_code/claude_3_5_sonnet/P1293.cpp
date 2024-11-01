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
    int n = 0;
    int total_students = 0;

    while (1) {
        scanf("%d %d %s", &cities[n].students, &cities[n].distance, cities[n].name);
        total_students += cities[n].students;
        if (cities[n].distance == 0) break;
        n++;
    }

    long long min_cost = LLONG_MAX;
    int best_city = 0;

    for (int i = 0; i <= n; i++) {
        long long cost = 0;
        for (int j = 0; j <= n; j++) {
            cost += (long long)abs(cities[i].distance - cities[j].distance) * cities[j].students;
        }
        if (cost < min_cost || (cost == min_cost && cities[i].distance < cities[best_city].distance)) {
            min_cost = cost;
            best_city = i;
        }
    }

    printf("%s %lld\n", cities[best_city].name, min_cost);

    return 0;
}