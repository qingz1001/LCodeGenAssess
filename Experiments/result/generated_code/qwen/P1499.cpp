#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 50
#define MAX_M 300
#define TIME_FORMAT "%02d%02d%02d"

typedef struct {
    int position;
    int time[3];
    int duration;
} PatrolCar;

int compare(const void *a, const void *b) {
    return ((PatrolCar *)a)->time[0] - ((PatrolCar *)b)->time[0] ||
           ((PatrolCar *)a)->time[1] - ((PatrolCar *)b)->time[1] ||
           ((PatrolCar *)a)->time[2] - ((PatrolCar *)b)->time[2];
}

void parseTime(char *timeStr, int *result) {
    sscanf(timeStr, TIME_FORMAT, &result[0], &result[1], &result[2]);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    PatrolCar patrolCars[MAX_M];
    for (int i = 0; i < m; i++) {
        scanf("%d %s %d", &patrolCars[i].position, patrolCars[i].time, &patrolCars[i].duration);
        parseTime(patrolCars[i].time, patrolCars[i].time);
    }

    qsort(patrolCars, m, sizeof(PatrolCar), compare);

    int meetings = 0;
    int earliestArrival[3] = {24, 0, 0};

    for (int i = 0; i < m; i++) {
        int startHour = patrolCars[i].time[0];
        int startMinute = patrolCars[i].time[1];
        int startSecond = patrolCars[i].time[2];
        int endHour = startHour + (startMinute * 60 + startSecond + patrolCars[i].duration) / 3600;
        int endMinute = (startMinute * 60 + startSecond + patrolCars[i].duration) / 60 % 60;
        int endSecond = (startMinute * 60 + startSecond + patrolCars[i].duration) % 60;

        if (endHour > 23 || (endHour == 23 && (endMinute > 59 || (endMinute == 59 && endSecond > 59)))) {
            continue;
        }

        if (patrolCars[i].position != 1) {
            meetings++;
        }

        if (endHour < earliestArrival[0] ||
            (endHour == earliestArrival[0] && endMinute < earliestArrival[1]) ||
            (endHour == earliestArrival[0] && endMinute == earliestArrival[1] && endSecond < earliestArrival[2])) {
            earliestArrival[0] = endHour;
            earliestArrival[1] = endMinute;
            earliestArrival[2] = endSecond;
        }
    }

    printf("%d\n", meetings);
    printf(TIME_FORMAT "\n", earliestArrival[0], earliestArrival[1], earliestArrival[2]);

    return 0;
}