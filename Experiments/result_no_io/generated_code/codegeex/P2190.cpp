#include <stdio.h>
#include <stdlib.h>

#define MAX_STATIONS 1000000

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    int station[MAX_STATIONS + 1] = {0};

    for (int i = 0; i < m; i++) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        if (x < y) {
            station[x] += z;
            station[y] -= z;
        } else {
            station[1] += z;
            station[x] += z;
            station[y] -= z;
        }
    }

    int passengers = 0, max_passengers = 0;
    for (int i = 1; i <= n; i++) {
        passengers += station[i];
        if (passengers > max_passengers) {
            max_passengers = passengers;
        }
    }

    printf("%d\n", (max_passengers + 35) / 36);

    return 0;
}