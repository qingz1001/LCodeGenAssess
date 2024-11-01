#include <stdio.h>
#include <math.h>
#include <float.h>

#define MAX_N 50000
#define EPS 1e-9

typedef struct {
    double x, y;
} Point;

typedef struct {
    Point start, end;
    double len;
} Segment;

int n, m;
Segment pathA[MAX_N], pathB[MAX_N];
double totalLenA, totalLenB;

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

Point getPoint(Segment *path, int segIndex, double t) {
    Point p;
    p.x = path[segIndex].start.x + (path[segIndex].end.x - path[segIndex].start.x) * t / path[segIndex].len;
    p.y = path[segIndex].start.y + (path[segIndex].end.y - path[segIndex].start.y) * t / path[segIndex].len;
    return p;
}

double calcTime(double tA) {
    int segA = 0, segB = 0;
    double remA = tA, remB = 0;
    
    while (segA < n - 1 && remA > pathA[segA].len) {
        remA -= pathA[segA].len;
        segA++;
    }
    
    Point pA = getPoint(pathA, segA, remA);
    
    double left = 0, right = totalLenB;
    
    while (right - left > EPS) {
        double mid = (left + right) / 2;
        double tB = mid;
        
        while (segB < m - 1 && tB > pathB[segB].len) {
            tB -= pathB[segB].len;
            segB++;
        }
        
        Point pB = getPoint(pathB, segB, tB);
        
        if (dist(pA, pB) < mid - tA)
            right = mid;
        else
            left = mid;
    }
    
    return left - tA;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf", &pathA[i].start.x, &pathA[i].start.y);
        if (i > 0) {
            pathA[i-1].end = pathA[i].start;
            pathA[i-1].len = dist(pathA[i-1].start, pathA[i-1].end);
            totalLenA += pathA[i-1].len;
        }
    }
    
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        scanf("%lf %lf", &pathB[i].start.x, &pathB[i].start.y);
        if (i > 0) {
            pathB[i-1].end = pathB[i].start;
            pathB[i-1].len = dist(pathB[i-1].start, pathB[i-1].end);
            totalLenB += pathB[i-1].len;
        }
    }
    
    double left = 0, right = totalLenA;
    double ans = DBL_MAX;
    
    while (right - left > EPS) {
        double m1 = left + (right - left) / 3;
        double m2 = right - (right - left) / 3;
        double t1 = calcTime(m1);
        double t2 = calcTime(m2);
        
        ans = fmin(ans, fmin(t1, t2));
        
        if (t1 < t2)
            right = m2;
        else
            left = m1;
    }
    
    if (ans > totalLenB)
        printf("impossible\n");
    else
        printf("%.5f\n", ans);
    
    return 0;
}