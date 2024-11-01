#include <stdio.h>
#include <stdlib.h>

#define MAX_N 80000

typedef struct {
    long long pos;
    int height;
    int type;
} Event;

int cmp(const void* a, const void* b) {
    Event* e1 = (Event*)a;
    Event* e2 = (Event*)b;
    if (e1->pos != e2->pos) return e1->pos - e2->pos;
    return e2->type - e1->type;
}

int main() {
    int n;
    scanf("%d", &n);

    Event events[MAX_N];
    int event_count = 0;

    for (int i = 0; i < n; i++) {
        long long a, b;
        int h;
        scanf("%lld %lld %d", &a, &b, &h);
        events[event_count++] = (Event){a, h, 1};
        events[event_count++] = (Event){b, h, -1};
    }

    qsort(events, event_count, sizeof(Event), cmp);

    long long result = 0;
    long long last_pos = 0;
    int max_height = 0;

    for (int i = 0; i < event_count; i++) {
        result += (events[i].pos - last_pos) * max_height;
        
        if (events[i].type == 1) {
            if (events[i].height > max_height) {
                max_height = events[i].height;
            }
        } else {
            int new_max = 0;
            for (int j = i + 1; j < event_count; j++) {
                if (events[j].type == 1 && events[j].height > new_max) {
                    new_max = events[j].height;
                }
                if (events[j].pos > events[i].pos) break;
            }
            max_height = new_max;
        }

        last_pos = events[i].pos;
    }

    printf("%lld\n", result);

    return 0;
}