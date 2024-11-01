#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CITIES 150
#define MAX_NAME_LEN 100

typedef struct {
    int num_students;
    int distance;
    char name[MAX_NAME_LEN];
} City;

int main() {
    City cities[MAX_CITIES];
    int city_count = 0;

    // Read input
    while (1) {
        scanf("%d", &cities[city_count].num_students);
        scanf("%d", &cities[city_count].distance);
        scanf("%s", cities[city_count].name);

        if (cities[city_count].distance == 0) {
            break;
        }
        city_count++;
    }

    // Calculate the total travel cost and find the minimum
    int min_cost = INT_MAX;
    int min_index = -1;

    for (int i = 0; i < city_count; i++) {
        int total_cost = 0;
        for (int j = 0; j < city_count; j++) {
            total_cost += cities[j].num_students * abs(cities[i].distance - cities[j].distance);
        }

        if (total_cost < min_cost || (total_cost == min_cost && cities[i].distance < cities[min_index].distance)) {
            min_cost = total_cost;
            min_index = i;
        }
    }

    // Output the result
    printf("%s %d\n", cities[min_index].name, min_cost);

    return 0;
}