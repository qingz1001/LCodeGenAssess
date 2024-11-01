#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 1000000
#define MAXS 100

int n, s;
int distances[MAXN];
int ranges[MAXS];

int min_landings(int range) {
    int total_distance = 0;
    for (int i = 0; i < n; i++) {
        total_distance += distances[i];
    }

    int min_landings = INT_MAX;
    for (int start = 0; start < n; start++) {
        int current_distance = 0;
        int landings = 0;
        for (int i = 0; i < n; i++) {
            int index = (start + i) % n;
            if (current_distance + distances[index] > range) {
                landings++;
                current_distance = distances[index];
            } else {
                current_distance += distances[index];
            }
        }
        if (current_distance > 0) {
            landings++;
        }
        if (landings < min_landings) {
            min_landings = landings;
        }
    }

    return min_landings;
}

int main() {
    scanf("%d %d", &n, &s);
    for (int i = 0; i < n; i++) {
        scanf("%d", &distances[i]);
    }
    for (int i = 0; i < s; i++) {
        scanf("%d", &ranges[i]);
    }

    for (int i = 0; i < s; i++) {
        int result = min_landings(ranges[i]);
        if (result == INT_MAX) {
            printf("NIE\n");
        } else {
            printf("%d\n", result);
        }
    }

    return 0;
}