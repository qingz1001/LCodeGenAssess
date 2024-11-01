#include <stdio.h>
#include <stdlib.h>

#define MAXN 40000
#define MAX_COORD 1000000000

typedef struct {
    int x;
    int height;
    int type; // 0 for start, 1 for end
} Event;

int cmp(const void *a, const void *b) {
    Event *e1 = (Event *)a;
    Event *e2 = (Event *)b;
    if (e1->x != e2->x) return e1->x - e2->x;
    return e2->type - e1->type; // end event before start event if at same x
}

int main() {
    int N;
    scanf("%d", &N);

    Event events[2 * MAXN];
    int idx = 0;

    for (int i = 0; i < N; i++) {
        int a, b, h;
        scanf("%d %d %d", &a, &b, &h);
        events[idx++] = (Event){a, h, 0};
        events[idx++] = (Event){b, h, 1};
    }

    qsort(events, idx, sizeof(Event), cmp);

    int current_height = 0;
    long long total_area = 0;
    int last_x = 0;

    for (int i = 0; i < idx; i++) {
        total_area += (long long)current_height * (events[i].x - last_x);
        last_x = events[i].x;

        if (events[i].type == 0) {
            current_height = events[i].height;
        } else {
            current_height = 0;
        }
    }

    printf("%lld\n", total_area);

    return 0;
}