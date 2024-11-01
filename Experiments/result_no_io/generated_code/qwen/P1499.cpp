#include <stdio.h>
#include <string.h>

#define MAX_N 50
#define MAX_M 300
#define TIME_FORMAT "hhmmss"

typedef struct {
    int position;
    char time[TIME_FORMAT];
    int duration;
} PatrolCar;

int compare(const void *a, const void *b) {
    return ((PatrolCar *)a)->position - ((PatrolCar *)b)->position;
}

void convertTime(char *timeStr, int *hours, int *minutes, int *seconds) {
    sscanf(timeStr, "%2d%2d%2d", hours, minutes, seconds);
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    PatrolCar patrolCars[MAX_M];
    for (int i = 0; i < m; i++) {
        scanf("%d %s %d", &patrolCars[i].position, patrolCars[i].time, &patrolCars[i].duration);
    }

    qsort(patrolCars, m, sizeof(PatrolCar), compare);

    int targetPosition = n;
    int targetDuration = 600 * (targetPosition - 1); // 10 km per hour
    int encounters = 0;
    int earliestArrivalHour = 24, earliestArrivalMinute = 60, earliestArrivalSecond = 60;

    for (int i = 0; i < m; i++) {
        int patrolPosition = patrolCars[i].position;
        int patrolHours, patrolMinutes, patrolSeconds;
        convertTime(patrolCars[i].time, &patrolHours, &patrolMinutes, &patrolSeconds);
        int patrolTotalSeconds = patrolHours * 3600 + patrolMinutes * 60 + patrolSeconds;
        int patrolTravelTime = patrolCars[i].duration * 10; // 10 km per second
        int patrolArrivalTime = patrolTotalSeconds + patrolTravelTime;

        if (patrolArrivalTime <= targetArrivalTime) {
            encounters++;
        }

        int targetArrivalTime = targetDuration;
        int targetArrivalHours = targetArrivalTime / 3600;
        int targetArrivalMinutes = (targetArrivalTime % 3600) / 60;
        int targetArrivalSeconds = targetArrivalTime % 60;

        if (patrolArrivalTime < earliestArrivalTime) {
            earliestArrivalTime = patrolArrivalTime;
            earliestArrivalHours = patrolArrivalTime / 3600;
            earliestArrivalMinutes = (patrolArrivalTime % 3600) / 60;
            earliestArrivalSeconds = patrolArrivalTime % 60;
        }
    }

    printf("%d\n", encounters);
    printf("%02d%02d%02d\n", earliestArrivalHours, earliestArrivalMinutes, earliestArrivalSeconds);

    return 0;
}