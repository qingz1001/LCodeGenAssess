#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000000
#define MAXS 100

int n, s;
int distances[MAXN];
int ranges[MAXS];

int min_landings(int range) {
    int landings = 0;
    int current_fuel = 0;
    for (int i = 0; i < n; i++) {
        if (current_fuel < distances[i]) {
            if (range < distances[i]) return -1; // Impossible to complete the journey
            landings++;
            current_fuel = range;
        }
        current_fuel -= distances[i];
    }
    return landings;
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
        if (result == -1) {
            printf("NIE\n");
        } else {
            printf("%d\n", result);
        }
    }

    return 0;
}