#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y, peanuts;
} Plant;

int compare(const void *a, const void *b) {
    return ((Plant *)b)->peanuts - ((Plant *)a)->peanuts;
}

int main() {
    int M, N, K;
    scanf("%d %d %d", &M, &N, &K);

    Plant plants[400];
    int plant_count = 0;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            int peanuts;
            scanf("%d", &peanuts);
            if (peanuts > 0) {
                plants[plant_count].x = i + 1;
                plants[plant_count].y = j + 1;
                plants[plant_count].peanuts = peanuts;
                plant_count++;
            }
        }
    }

    qsort(plants, plant_count, sizeof(Plant), compare);

    int total_peanuts = 0;
    int current_x = 0, current_y = plants[0].y;

    for (int i = 0; i < plant_count; i++) {
        int time_to_plant = abs(plants[i].x - current_x) + abs(plants[i].y - current_y);
        int time_to_return = plants[i].x;

        if (K >= time_to_plant + time_to_return + 1) {
            K -= time_to_plant + 1;
            total_peanuts += plants[i].peanuts;
            current_x = plants[i].x;
            current_y = plants[i].y;
        } else {
            break;
        }
    }

    printf("%d\n", total_peanuts);

    return 0;
}