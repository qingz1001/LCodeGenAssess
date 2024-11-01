#include <stdio.h>
#include <stdlib.h>

#define MAXN 40000
#define MAX_COORD 1000000000

typedef struct {
    int x, h;
} Event;

int cmp(const void *a, const void *b) {
    return ((Event *)a)->x - ((Event *)b)->x;
}

int main() {
    int N;
    scanf("%d", &N);

    Event events[2 * MAXN];
    int idx = 0;

    for (int i = 0; i < N; i++) {
        int a, b, h;
        scanf("%d %d %d", &a, &b, &h);
        events[idx++] = (Event){a, h};
        events[idx++] = (Event){b, -h};
    }

    qsort(events, idx, sizeof(Event), cmp);

    long long area = 0;
    int current_height = 0;
    int last_x = events[0].x;

    for (int i = 0; i < idx; i++) {
        int x = events[i].x;
        int h = events[i].h;

        if (x != last_x) {
            area += (long long)current_height * (x - last_x);
            last_x = x;
        }

        if (h > 0) {
            current_height += h;
        } else {
            current_height -= -h;
        }
    }

    printf("%lld\n", area);

    return 0;
}