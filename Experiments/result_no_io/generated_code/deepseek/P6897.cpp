#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define MAXN 50000
#define EPS 1e-9

typedef struct {
    double x, y;
} Point;

typedef struct {
    Point p1, p2;
} Segment;

int n, m;
Point pathA[MAXN], pathB[MAXN];

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double dot(Point a, Point b) {
    return a.x * b.x + a.y * b.y;
}

double cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}

Point subtract(Point a, Point b) {
    Point result = {a.x - b.x, a.y - b.y};
    return result;
}

double segmentDist(Point p, Segment s) {
    Point v = subtract(s.p2, s.p1);
    Point w = subtract(p, s.p1);

    double c1 = dot(w, v);
    if (c1 <= 0) return dist(p, s.p1);

    double c2 = dot(v, v);
    if (c2 <= c1) return dist(p, s.p2);

    double b = c1 / c2;
    Point pb = {s.p1.x + b * v.x, s.p1.y + b * v.y};
    return dist(p, pb);
}

double minTime(double tA, double tB) {
    double minTime = DBL_MAX;
    Point A = pathA[0];
    Point B = pathB[0];
    double timeA = 0, timeB = 0;
    int i = 0, j = 0;

    while (i < n - 1 && j < m - 1) {
        Segment segA = {pathA[i], pathA[i + 1]};
        Segment segB = {pathB[j], pathB[j + 1]};

        double lenA = dist(segA.p1, segA.p2);
        double lenB = dist(segB.p1, segB.p2);
        double timeToMoveA = lenA / (tA - timeA);
        double timeToMoveB = lenB / (tB - timeB);
        double timeToMove = fmin(timeToMoveA, timeToMoveB);

        Point newA = {A.x + (segA.p2.x - segA.p1.x) / lenA * timeToMove,
                      A.y + (segA.p2.y - segA.p1.y) / lenA * timeToMove};
        Point newB = {B.x + (segB.p2.x - segB.p1.x) / lenB * timeToMove,
                      B.y + (segB.p2.y - segB.p1.y) / lenB * timeToMove};

        double d = segmentDist(newA, segB);
        if (d < EPS) {
            return tB - tA;
        }

        if (timeToMoveA < timeToMoveB) {
            A = segA.p2;
            timeA += lenA;
            i++;
        } else {
            B = segB.p2;
            timeB += lenB;
            j++;
        }
    }

    return minTime;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &pathA[i].x, &pathA[i].y);
    }
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%lf %lf", &pathB[i].x, &pathB[i].y);
    }

    double totalTimeA = 0, totalTimeB = 0;
    for (int i = 1; i < n; i++) {
        totalTimeA += dist(pathA[i], pathA[i - 1]);
    }
    for (int i = 1; i < m; i++) {
        totalTimeB += dist(pathB[i], pathB[i - 1]);
    }

    double left = 0, right = totalTimeA;
    double bestTime = DBL_MAX;

    while (right - left > EPS) {
        double mid1 = left + (right - left) / 3;
        double mid2 = right - (right - left) / 3;
        double time1 = minTime(mid1, totalTimeB);
        double time2 = minTime(mid2, totalTimeB);

        if (time1 < time2) {
            right = mid2;
            bestTime = fmin(bestTime, time1);
        } else {
            left = mid1;
            bestTime = fmin(bestTime, time2);
        }
    }

    if (bestTime == DBL_MAX) {
        printf("impossible\n");
    } else {
        printf("%.9lf\n", bestTime);
    }

    return 0;
}