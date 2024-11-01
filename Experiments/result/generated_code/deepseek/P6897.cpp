#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

#define MAX_POINTS 50000
#define EPS 1e-9

typedef struct {
    double x, y;
} Point;

typedef struct {
    Point p1, p2;
} Segment;

Point pointsA[MAX_POINTS], pointsB[MAX_POINTS];
int n, m;

double distance(Point p1, Point p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double dotProduct(Point p1, Point p2) {
    return p1.x * p2.x + p1.y * p2.y;
}

Point subtract(Point p1, Point p2) {
    Point result = {p1.x - p2.x, p1.y - p2.y};
    return result;
}

double segmentDistance(Point p, Segment s) {
    Point v = subtract(s.p2, s.p1);
    Point w = subtract(p, s.p1);

    double c1 = dotProduct(w, v);
    if (c1 <= 0) return distance(p, s.p1);

    double c2 = dotProduct(v, v);
    if (c2 <= c1) return distance(p, s.p2);

    double b = c1 / c2;
    Point pb = {s.p1.x + b * v.x, s.p1.y + b * v.y};
    return distance(p, pb);
}

double minTime(Point A, Point B, Point C) {
    double dAB = distance(A, B);
    double dAC = distance(A, C);
    double dBC = distance(B, C);

    if (dAC + dBC < dAB + EPS) {
        return dAC;
    } else {
        return DBL_MAX;
    }
}

double solve() {
    double minDiff = DBL_MAX;

    for (int i = 0; i < n - 1; i++) {
        Segment segA = {pointsA[i], pointsA[i + 1]};
        for (int j = 0; j < m - 1; j++) {
            Segment segB = {pointsB[j], pointsB[j + 1]};

            double tA = 0, tB = 0;
            for (int k = 0; k < i; k++) {
                tA += distance(pointsA[k], pointsA[k + 1]);
            }
            for (int k = 0; k < j; k++) {
                tB += distance(pointsB[k], pointsB[k + 1]);
            }

            Point vA = subtract(pointsA[i + 1], pointsA[i]);
            Point vB = subtract(pointsB[j + 1], pointsB[j]);

            double lenA = distance(pointsA[i], pointsA[i + 1]);
            double lenB = distance(pointsB[j], pointsB[j + 1]);

            for (int k = 0; k <= 100; k++) {
                double t = k / 100.0;
                Point pA = {pointsA[i].x + t * vA.x, pointsA[i].y + t * vA.y};
                Point pB = {pointsB[j].x + t * vB.x, pointsB[j].y + t * vB.y};

                double d = segmentDistance(pA, segB);
                double timeA = tA + t * lenA;
                double timeB = tB + t * lenB;

                if (d < EPS) {
                    minDiff = fmin(minDiff, timeB - timeA);
                }
            }
        }
    }

    return minDiff;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &pointsA[i].x, &pointsA[i].y);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%lf %lf", &pointsB[i].x, &pointsB[i].y);
    }

    double result = solve();
    if (result == DBL_MAX) {
        printf("impossible\n");
    } else {
        printf("%.5f\n", result);
    }

    return 0;
}