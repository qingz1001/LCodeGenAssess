#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

typedef struct {
    long long x1, y1, x2, y2;
} Segment;

int compare(const void* a, const void* b) {
    Segment* s1 = (Segment*)a;
    Segment* s2 = (Segment*)b;
    return (s2->y1 > s1->y1) - (s2->y1 < s1->y1);
}

long long simulate(Segment segments[], int n, long long s) {
    qsort(segments, n, sizeof(Segment), compare);

    long long x = s;
    long long y = 1000000001;

    for (int i = 0; i < n; i++) {
        if (segments[i].y1 >= y) continue;
        if (x >= segments[i].x1 && x <= segments[i].x2) {
            y = segments[i].y1;
            if (segments[i].x1 > segments[i].x2) {
                x = segments[i].x1;
            } else {
                x = segments[i].x2;
            }
        }
    }

    return x;
}

int main() {
    int n;
    long long s;
    scanf("%d %lld", &n, &s);

    Segment segments[MAX_N];
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld %lld %lld", &segments[i].x1, &segments[i].y1, &segments[i].x2, &segments[i].y2);
        if (segments[i].y1 < segments[i].y2) {
            long long temp = segments[i].x1;
            segments[i].x1 = segments[i].x2;
            segments[i].x2 = temp;
            temp = segments[i].y1;
            segments[i].y1 = segments[i].y2;
            segments[i].y2 = temp;
        }
    }

    long long result = simulate(segments, n, s);
    printf("%lld\n", result);

    return 0;
}