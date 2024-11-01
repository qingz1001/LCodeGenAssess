#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000
#define MAX_POS 1000000000

typedef struct {
    int pos;
    int delta;
} Event;

int cmp(const void *a, const void *b) {
    return ((Event *)a)->pos - ((Event *)b)->pos;
}

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    Event events[2 * MAX_N];
    int event_count = 0;

    for (int i = 0; i < N; i++) {
        int dist;
        char dir;
        scanf("%d %c", &dist, &dir);
        int delta = (dir == 'R') ? 1 : -1;
        events[event_count++] = (Event){dist, delta};
        events[event_count++] = (Event){dist + 1, -delta};
    }

    qsort(events, event_count, sizeof(Event), cmp);

    int current_coats = 0;
    int last_pos = 0;
    int painted_area = 0;

    for (int i = 0; i < event_count; i++) {
        if (current_coats >= K) {
            painted_area += events[i].pos - last_pos;
        }
        current_coats += events[i].delta;
        last_pos = events[i].pos;
    }

    printf("%d\n", painted_area);

    return 0;
}