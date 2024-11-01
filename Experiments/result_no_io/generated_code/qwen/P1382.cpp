#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100005

typedef struct {
    long long x;
    int h;
} Event;

int cmp(const void *a, const void *b) {
    Event e1 = *(Event *)a;
    Event e2 = *(Event *)b;
    if (e1.x != e2.x) return e1.x - e2.x;
    return e2.h - e1.h;
}

long long get_max_height(int n, Event events[]) {
    long long max_height = 0;
    for (int i = 0; i < n; ++i) {
        if (events[i].h > max_height) max_height = events[i].h;
    }
    return max_height;
}

void process_events(int n, Event events[], long long *result, int *result_size) {
    qsort(events, n, sizeof(Event), cmp);
    long long current_height = 0;
    for (int i = 0; i < n; ++i) {
        if (events[i].h != current_height) {
            result[*result_size] = events[i].x;
            result[*result_size + 1] = events[i].h;
            (*result_size) += 2;
            current_height = events[i].h;
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);
    Event events[MAX_N * 2];
    int event_index = 0;

    for (int i = 0; i < n; ++i) {
        long long l, r;
        int h;
        scanf("%lld %lld %d", &l, &r, &h);
        events[event_index++] = (Event){l, -h};
        events[event_index++] = (Event){r, h};
    }

    long long result[MAX_N * 2];
    int result_size = 0;
    process_events(event_index, events, result, &result_size);

    printf("%d\n", result_size / 2);
    for (int i = 0; i < result_size; i += 2) {
        printf("%lld %lld\n", result[i], result[i + 1]);
    }

    return 0;
}