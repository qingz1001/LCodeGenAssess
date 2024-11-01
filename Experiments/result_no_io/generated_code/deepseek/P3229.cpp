#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 500005
#define MAXM 200005

typedef struct {
    int city;
    int has_attraction;
} City;

City cities[MAXN];
int n, m;
int result[MAXM];

int compare(const void *a, const void *b) {
    return ((City *)a)->city - ((City *)b)->city;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &cities[i].city, &cities[i].has_attraction);
    }

    // Sort cities by city number
    qsort(cities, n, sizeof(City), compare);

    // Initialize variables
    int current_month = 0;
    int current_city_index = 0;
    int current_happiness = 0;
    int current_fatigue = 0;
    int max_difference = 0;

    // Calculate the optimal travel plan
    while (current_month < m) {
        int next_city_index = current_city_index;
        int next_happiness = current_happiness;
        int next_fatigue = current_fatigue;
        int next_max_difference = max_difference;

        while (next_city_index < n) {
            if (cities[next_city_index].has_attraction) {
                next_happiness++;
            } else {
                next_fatigue++;
            }

            int difference = abs(next_happiness - next_fatigue);
            if (difference > next_max_difference) {
                next_max_difference = difference;
            }

            // Check if we can end the month here
            if (next_max_difference > max_difference) {
                break;
            }

            next_city_index++;
        }

        // If we can't find a better plan, end the month here
        if (next_city_index == current_city_index) {
            break;
        }

        // Update the current month's result
        result[current_month] = cities[next_city_index - 1].city;
        current_month++;
        current_city_index = next_city_index;
        current_happiness = next_happiness;
        current_fatigue = next_fatigue;
        max_difference = next_max_difference;
    }

    // Output the result
    for (int i = 0; i < m; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}