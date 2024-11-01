#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    int *floors = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &floors[i]);
    }

    int current_floor = 0;
    int total_time = 0;

    for (int i = 0; i < n; i++) {
        if (current_floor < floors[i]) {
            total_time += (floors[i] - current_floor) * 6 + 5 + 1;
        } else {
            total_time += (current_floor - floors[i]) * 4 + 5 + 1;
        }
        current_floor = floors[i];
    }

    // Return to ground floor
    if (current_floor > 0) {
        total_time += current_floor * 4 + 5 + 1;
    } else if (current_floor < 0) {
        total_time += -current_floor * 6 + 5 + 1;
    }

    printf("%d\n", total_time);

    free(floors);
    return 0;
}