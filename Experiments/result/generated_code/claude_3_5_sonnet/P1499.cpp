#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_N 50
#define MAX_M 300
#define MAX_TIME 86400

typedef struct {
    int start;
    int time;
    int duration;
} Patrol;

int n, m;
Patrol patrols[MAX_M];

int timeToSeconds(char* timeStr) {
    int h, m, s;
    sscanf(timeStr, "%2d%2d%2d", &h, &m, &s);
    return h * 3600 + m * 60 + s;
}

void secondsToTime(int seconds, char* timeStr) {
    int h = seconds / 3600;
    int m = (seconds % 3600) / 60;
    int s = seconds % 60;
    sprintf(timeStr, "%02d%02d%02d", h, m, s);
}

int compare(const void* a, const void* b) {
    return ((Patrol*)a)->start - ((Patrol*)b)->start;
}

int meetPatrol(int startTime, int speed) {
    int count = 0;
    int position = 0;
    int time = startTime;

    for (int i = 0; i < m; i++) {
        int patrolStart = patrols[i].start * 10;
        int patrolTime = patrols[i].time;
        int patrolDuration = patrols[i].duration;
        int patrolEnd = patrolStart + 10;
        int patrolSpeed = 10 * 3600 / patrolDuration;

        if (patrolStart <= position && position < patrolEnd) {
            int meetTime = (patrolTime > time) ? patrolTime : time;
            int meetPosition = position + (meetTime - time) * speed / 3600;
            
            if (meetPosition >= patrolStart && meetPosition <= patrolEnd &&
                (meetTime > time || meetTime > patrolTime)) {
                count++;
            }
        }
    }

    return count;
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        char timeStr[7];
        scanf("%d %s %d", &patrols[i].start, timeStr, &patrols[i].duration);
        patrols[i].time = timeToSeconds(timeStr);
    }

    qsort(patrols, m, sizeof(Patrol), compare);

    int minMeetings = INT_MAX;
    int bestArrivalTime = 0;

    for (int speed = 60; speed <= 120; speed++) {
        int travelTime = (n - 1) * 10 * 3600 / speed;
        int arrivalTime = 6 * 3600 + travelTime;
        int meetings = meetPatrol(6 * 3600, speed);

        if (meetings < minMeetings || (meetings == minMeetings && arrivalTime < bestArrivalTime)) {
            minMeetings = meetings;
            bestArrivalTime = arrivalTime;
        }
    }

    printf("%d\n", minMeetings);

    char arrivalTimeStr[7];
    secondsToTime(bestArrivalTime, arrivalTimeStr);
    printf("%s\n", arrivalTimeStr);

    return 0;
}