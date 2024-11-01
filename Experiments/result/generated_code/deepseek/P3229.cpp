#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 500005

typedef struct {
    int city;
    int has_attraction;
} City;

City cities[MAXN];
int n, m;

int compare_cities(const void *a, const void *b) {
    return ((City *)a)->city - ((City *)b)->city;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &cities[i].city, &cities[i].has_attraction);
    }

    // Sort cities by city number
    qsort(cities, n, sizeof(City), compare_cities);

    // Initialize variables
    int current_month = 0;
    int current_city_index = 0;
    int current_happiness = 0;
    int current_fatigue = 0;
    int max_diff = INT_MAX;
    int best_start_index = 0;

    // Find the best starting point
    for (int i = 0; i <= n - m; i++) {
        int total_happiness = 0;
        int total_fatigue = 0;
        int max_local_diff = 0;

        for (int j = 0; j < m; j++) {
            if (cities[i + j].has_attraction) {
                total_happiness++;
            } else {
                total_fatigue++;
            }
            int local_diff = abs(total_happiness - total_fatigue);
            if (local_diff > max_local_diff) {
                max_local_diff = local_diff;
            }
        }

        if (max_local_diff < max_diff) {
            max_diff = max_local_diff;
            best_start_index = i;
        }
    }

    // Output the result
    for (int i = 0; i < m; i++) {
        printf("%d ", cities[best_start_index + i].city);
    }
    printf("\n");

    return 0;
}