#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000000
#define MAXM 1000000
#define CAPACITY 36

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int *passengers = (int *)calloc(n, sizeof(int));
    if (passengers == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    int max_passengers = 0;

    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        x--; y--; // Convert to 0-based index

        if (y >= x) {
            passengers[x] += z;
            if (y + 1 < n) passengers[y + 1] -= z;
        } else {
            passengers[x] += z;
            passengers[0] += z;
            if (y + 1 < n) passengers[y + 1] -= z;
        }
    }

    int current_passengers = 0;
    for (int i = 0; i < n; i++) {
        current_passengers += passengers[i];
        if (current_passengers > max_passengers) {
            max_passengers = current_passengers;
        }
    }

    int required_cars = (max_passengers + CAPACITY - 1) / CAPACITY;
    printf("%d\n", required_cars);

    free(passengers);
    return 0;
}