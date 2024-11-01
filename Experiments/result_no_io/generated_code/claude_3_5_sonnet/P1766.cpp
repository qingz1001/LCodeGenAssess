#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_N 100000

typedef struct {
    long long x1, y1, x2, y2;
} Segment;

int compare(const void *a, const void *b) {
    Segment *s1 = (Segment *)a;
    Segment *s2 = (Segment *)b;
    if (s1->y1 != s2->y1) return s2->y1 - s1->y1;
    return s1->x1 - s2->x1;
}

long long findDropPosition(Segment segments[], int n, long long s) {
    qsort(segments, n, sizeof(Segment), compare);

    for (int i = 0; i < n; i++) {
        if (segments[i].y1 == segments[i].y2) continue;
        
        if ((segments[i].x1 <= s && s <= segments[i].x2) ||
            (segments[i].x2 <= s && s <= segments[i].x1)) {
            double slope = (double)(segments[i].y2 - segments[i].y1) / (segments[i].x2 - segments[i].x1);
            s = (segments[i].y1 > segments[i].y2) ? segments[i].x2 : segments[i].x1;
        }
    }

    return s;
}

int main() {
    int n;
    long long s;
    scanf("%d %lld", &n, &s);

    Segment segments[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld %lld %lld", &segments[i].x1, &segments[i].y1, &segments[i].x2, &segments[i].y2);
        if (segments[i].x1 > segments[i].x2) {
            long long temp = segments[i].x1;
            segments[i].x1 = segments[i].x2;
            segments[i].x2 = temp;
            temp = segments[i].y1;
            segments[i].y1 = segments[i].y2;
            segments[i].y2 = temp;
        }
    }

    long long result = findDropPosition(segments, n, s);
    printf("%lld\n", result);

    return 0;
}