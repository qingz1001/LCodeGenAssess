#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100000
#define MAX_COORD 2000000001

typedef struct {
    int coord;
    int delta;
} Event;

int compare(const void *a, const void *b) {
    Event *ea = (Event *)a;
    Event *eb = (Event *)b;
    return ea->coord - eb->coord;
}

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    Event events[MAX_N * 2];
    int eventCount = 0;
    int currentPos = 0;

    for (int i = 0; i < N; i++) {
        int distance;
        char direction;
        scanf("%d %c", &distance, &direction);

        int newPos = currentPos + (direction == 'L' ? -distance : distance);
        
        if (currentPos < newPos) {
            events[eventCount++] = (Event){currentPos, 1};
            events[eventCount++] = (Event){newPos, -1};
        } else {
            events[eventCount++] = (Event){newPos, 1};
            events[eventCount++] = (Event){currentPos, -1};
        }

        currentPos = newPos;
    }

    qsort(events, eventCount, sizeof(Event), compare);

    int result = 0;
    int count = 0;
    int lastCoord = -1;

    for (int i = 0; i < eventCount; i++) {
        if (count >= K && events[i].coord > lastCoord) {
            result += events[i].coord - lastCoord;
        }
        
        count += events[i].delta;
        lastCoord = events[i].coord;
    }

    printf("%d\n", result);

    return 0;
}