#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int *floors = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &floors[i]);
    }

    int total_time = 0;
    int current_floor = 0;

    for (int i = 0; i < n; i++) {
        if (floors[i] > current_floor) {
            total_time += (floors[i] - current_floor) * 6 + 5 + i;
        } else {
            total_time += (current_floor - floors[i]) * 4 + 5 + i;
        }
        current_floor = floors[i];
    }

    // Return to the ground floor
    if (current_floor > 0) {
        total_time += current_floor * 4 + 5 + n;
    } else if (current_floor < 0) {
        total_time -= current_floor * 6 + 5 + n;
    }

    printf("%d\n", total_time);

    free(floors);
    return 0;
}