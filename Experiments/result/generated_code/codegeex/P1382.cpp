#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int h;
    int type; // 0 for start of rectangle, 1 for end of rectangle
} Event;

int compare(const void *a, const void *b) {
    Event *eventA = (Event *)a;
    Event *eventB = (Event *)b;
    if (eventA->x != eventB->x) {
        return eventA->x - eventB->x;
    } else {
        return eventA->type - eventB->type;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    Event events[2 * n];

    for (int i = 0; i < n; i++) {
        int h, l, r;
        scanf("%d%d%d", &h, &l, &r);
        events[2 * i].x = l;
        events[2 * i].h = h;
        events[2 * i].type = 0;
        events[2 * i + 1].x = r;
        events[2 * i + 1].h = h;
        events[2 * i + 1].type = 1;
    }

    qsort(events, 2 * n, sizeof(Event), compare);

    int m = 0;
    int heights[2 * n];
    heights[m++] = events[0].h;

    for (int i = 1; i < 2 * n; i++) {
        if (events[i].type == 0) {
            // Start of a rectangle
            int j = i;
            while (j < 2 * n && events[j].type == 0) {
                j++;
            }
            int max_height = 0;
            for (int k = i; k < j; k++) {
                max_height = (events[k].h > max_height) ? events[k].h : max_height;
            }
            heights[m++] = max_height;
            i = j - 1;
        } else {
            // End of a rectangle
            int j = i;
            while (j < 2 * n && events[j].type == 1) {
                j++;
            }
            int max_height = 0;
            for (int k = i; k < j; k++) {
                max_height = (events[k].h > max_height) ? events[k].h : max_height;
            }
            heights[m++] = max_height;
            i = j - 1;
        }
    }

    printf("%d\n", m);
    for (int i = 0; i < m; i++) {
        if (i == 0 || heights[i] != heights[i - 1]) {
            printf("%d %d\n", events[i].x, heights[i]);
        }
    }
    printf("%d 0\n", events[2 * n - 1].x);

    return 0;
}