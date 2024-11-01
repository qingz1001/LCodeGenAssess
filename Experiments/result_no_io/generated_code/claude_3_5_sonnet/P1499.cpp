#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 50
#define MAX_M 300

typedef struct {
    int start;
    int time;
    int duration;
} Patrol;

int n, m;
Patrol patrols[MAX_M];

int timeToSeconds(char *time) {
    int h, m, s;
    sscanf(time, "%2d%2d%2d", &h, &m, &s);
    return h * 3600 + m * 60 + s;
}

void secondsToTime(int seconds, char *time) {
    int h = seconds / 3600;
    int m = (seconds % 3600) / 60;
    int s = seconds % 60;
    sprintf(time, "%02d%02d%02d", h, m, s);
}

int comparePatrols(const void *a, const void *b) {
    return ((Patrol*)a)->start - ((Patrol*)b)->start;
}

int calculateMeetings(int departure) {
    int position = 1;
    int time = departure;
    int meetings = 0;

    for (int i = 0; i < m; i++) {
        if (patrols[i].start >= n) continue;

        int meetTime = (patrols[i].start - position) * 600;
        int carTime = time + meetTime;
        int patrolTime = patrols[i].time;

        if (carTime <= patrolTime) {
            time = patrolTime;
            position = patrols[i].start;
            meetings++;
        } else if (carTime < patrolTime + patrols[i].duration) {
            time = carTime;
            position = patrols[i].start + 1;
            meetings++;
        }
    }

    return meetings;
}

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        char timeStr[7];
        scanf("%d %s %d", &patrols[i].start, timeStr, &patrols[i].duration);
        patrols[i].time = timeToSeconds(timeStr);
    }

    qsort(patrols, m, sizeof(Patrol), comparePatrols);

    int minMeetings = m;
    int bestDeparture = 21600;  // 6:00:00

    for (int departure = 21600; departure <= 82800; departure++) {  // 6:00:00 to 23:00:00
        int meetings = calculateMeetings(departure);
        if (meetings < minMeetings) {
            minMeetings = meetings;
            bestDeparture = departure;
        }
    }

    char arrivalTime[7];
    secondsToTime(bestDeparture + (n - 1) * 600, arrivalTime);

    printf("%d\n%s\n", minMeetings, arrivalTime);

    return 0;
}