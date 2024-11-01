#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int num_students;
    int distance;
    char name[50];
} City;

int main() {
    City cities[150];
    int count = 0;

    // Read input
    while (1) {
        scanf("%d %d %s", &cities[count].num_students, &cities[count].distance, cities[count].name);
        if (cities[count].distance == 0) {
            break;
        }
        count++;
    }

    // Calculate the total travel cost for each city
    int min_cost = INT_MAX;
    int min_index = -1;
    for (int i = 0; i <= count; i++) {
        int total_cost = 0;
        for (int j = 0; j <= count; j++) {
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