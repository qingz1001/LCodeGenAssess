#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y, count;
} Peanut;

int cmp(const void *a, const void *b) {
    return ((Peanut *)b)->count - ((Peanut *)a)->count;
}

int main() {
    int M, N, K;
    scanf("%d %d %d", &M, &N, &K);

    Peanut peanuts[400];
    int idx = 0;

    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            int count;
            scanf("%d", &count);
            if (count > 0) {
                peanuts[idx].x = i + 1;
                peanuts[idx].y = j + 1;
                peanuts[idx].count = count;
                idx++;
            }
        }
    }

    qsort(peanuts, idx, sizeof(Peanut), cmp);

    int total_peanuts = 0;
    int current_x = 0, current_y = peanuts[0].y;

    for (int i = 0; i < idx; i++) {
        int time_to_plant = abs(peanuts[i].x - current_x) + abs(peanuts[i].y - current_y);
        int time_to_return = peanuts[i].x;
        int total_time = time_to_plant + time_to_return + 1;

        if (K >= total_time) {
            K -= time_to_plant + 1;
            total_peanuts += peanuts[i].count;
            current_x = peanuts[i].x;
            current_y = peanuts[i].y;
        } else {
            break;
        }
    }

    printf("%d\n", total_peanuts);

    return 0;
}