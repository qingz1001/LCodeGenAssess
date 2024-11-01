#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000000

int n, s;
int distances[MAX_N];
int flight_ranges[MAX_N];

void min_landings(int flight_range) {
    int i, j, min_landings = 0;
    int visited[MAX_N] = {0};

    for (i = 0; i < n; i++) {
        visited[i] = 1;
        int current_distance = 0;

        for (j = i; j < n && current_distance + distances[j] <= flight_range; j++) {
            visited[j] = 1;
            current_distance += distances[j];
        }

        if (current_distance >= flight_range) {
            min_landings = j - i;
            break;
        }

        for (j = 0; j < i && current_distance + distances[j] <= flight_range; j++) {
            visited[j] = 1;
            current_distance += distances[j];
        }

        if (current_distance >= flight_range) {
            min_landings = j + n - i;
            break;
        }
    }

    if (min_landings == 0) {
        printf("NIE\n");
    } else {
        printf("%d\n", min_landings);
    }
}

int main() {
    scanf("%d %d", &n, &s);
    for (int i = 0; i < n; i++) {
        scanf("%d", &distances[i]);
    }
    for (int i = 0; i < s; i++) {
        scanf("%d", &flight_ranges[i]);
        min_landings(flight_ranges[i]);
    }
    return 0;
}