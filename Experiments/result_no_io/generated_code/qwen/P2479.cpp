#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

typedef struct {
    long long x, y;
} Point;

Point points[MAXN];
long long n;

long long abs(long long a) {
    return (a >= 0) ? a : -a;
}

long long max(long long a, long long b) {
    return (a > b) ? a : b;
}

long long min(long long a, long long b) {
    return (a < b) ? a : b;
}

long long distance(Point p1, Point p2) {
    return abs(p1.x - p2.x) + abs(p1.y - p2.y);
}

int compare(const void *a, const void *b) {
    Point *p1 = (Point *)a;
    Point *p2 = (Point *)b;
    if (p1->x != p2->x) return (p1->x > p2->x) ? 1 : -1;
    else return (p1->y > p2->y) ? 1 : -1;
}

long long solve() {
    qsort(points, n, sizeof(Point), compare);

    long long ans = 2LL << 60;
    for (long long i = 0; i < n; i++) {
        long long left = 0, right = n - 1;
        while (left <= right) {
            long long mid = (left + right) / 2;
            if (points[mid].x < points[i].x) left = mid + 1;
            else right = mid - 1;
        }
        long long farthest = max(distance(points[i], points[left]), distance(points[i], points[right]));
        long long nearest = min(distance(points[i], points[left]), distance(points[i], points[right]));
        ans = min(ans, farthest - nearest);
    }

    return ans;
}

int main() {
    scanf("%lld", &n);
    for (long long i = 0; i < n; i++) {
        scanf("%lld %lld", &points[i].x, &points[i].y);
    }

    printf("%lld\n", solve());

    return 0;
}