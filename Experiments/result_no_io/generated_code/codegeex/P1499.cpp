#include <stdio.h>
#include <stdlib.h>

#define MAX_N 50
#define MAX_M 300

typedef struct {
    int n; // 出发位置
    int T; // 出发时刻
    int t; // 路上耗费的时间
} PatrolCar;

int cmp(const void *a, const void *b) {
    return ((PatrolCar *)a)->n - ((PatrolCar *)b)->n;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    PatrolCar patrolCars[MAX_M];
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &patrolCars[i].n, &patrolCars[i].T, &patrolCars[i].t);
    }

    qsort(patrolCars, m, sizeof(PatrolCar), cmp);

    int min_meetings = 0;
    int earliest_arrival = 21600; // 6:00:00 in seconds

    for (int i = 0; i < m; i++) {
        int target_time = 21600 + (n - patrolCars[i].n) * 60 * 60; // 6 hours + (n-ni) hours
        if (target_time >= patrolCars[i].T + patrolCars[i].t) {
            continue;
        }
        int meeting_time = target_time + (patrolCars[i].n - 1) * 60 * 60; // 6 hours + (ni-1) hours
        if (meeting_time < patrolCars[i].T + patrolCars[i].t) {
            min_meetings++;
            if (earliest_arrival > meeting_time) {
                earliest_arrival = meeting_time;
            }
        }
    }

    printf("%d\n", min_meetings);
    printf("%02d:%02d:%02d\n", earliest_arrival / 3600, (earliest_arrival % 3600) / 60, earliest_arrival % 60);

    return 0;
}