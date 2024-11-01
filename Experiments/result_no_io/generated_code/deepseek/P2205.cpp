#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000
#define MAX_POS 1000000000

typedef struct {
    int pos;
    int change;
} Event;

int cmp(const void *a, const void *b) {
    return ((Event *)a)->pos - ((Event *)b)->pos;
}

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    Event events[MAX_N * 2];
    int event_count = 0;

    for (int i = 0; i < N; i++) {
        int d;
        char dir;
        scanf("%d %c", &d, &dir);
        if (dir == 'L') {
            events[event_count++] = (Event){-d, 1};
            events[event_count++] = (Event){0, -1};
        } else if (dir == 'R') {
            events[event_count++] = (Event){0, 1};
            events[event_count++] = (Event){d, -1};
        }
    }

    qsort(events, event_count, sizeof(Event), cmp);

    int current_coats = 0;
    int last_pos = -MAX_POS;
    int painted_area = 0;

    for (int i = 0; i < event_count; i++) {
        if (current_coats >= K) {
            painted_area += events[i].pos - last_pos;
        }
        current_coats += events[i].change;
        last_pos = events[i].pos;
    }

    printf("%d\n", painted_area);

    return 0;
}