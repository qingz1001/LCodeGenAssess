#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define EPS 1e-9

typedef struct {
    double x, y;
} Point;

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double solve(int na, Point* pa, int nb, Point* pb) {
    if (na == 1 && nb == 1) {
        if (dist(pa[0], pb[0]) > 2) return -1;
        return dist(pa[0], pb[0]);
    }
    
    double ans = -1;
    for (int i = 0; i < na - 1; ++i) {
        for (int j = 0; j < nb - 1; ++j) {
            Point p1 = pa[i], q1 = pa[i + 1];
            Point p2 = pb[j], q2 = pb[j + 1];
            
            double d1 = dist(p1, q1), d2 = dist(p2, q2);
            double t1 = dist(p1, p2), t2 = dist(q1, q2);
            
            double t = 0;
            if (d1 >= d2) {
                if (t1 >= d2) {
                    t = d2 / d1 * t1;
                } else {
                    t = -1;
                }
            } else {
                if (t2 >= d1) {
                    t = d1 / d2 * t2;
                } else {
                    t = -1;
                }
            }
            
            if (t >= 0) {
                double dt = dist(p1 + t * (q1 - p1) / d1, p2 + t * (q2 - p2) / d2);
                if (ans == -1 || dt < ans) {
                    ans = dt;
                }
            }
        }
    }
    
    return ans;
}

int main() {
    int na, nb;
    scanf("%d", &na);
    Point* pa = (Point*)malloc(na * sizeof(Point));
    for (int i = 0; i < na; ++i) {
        scanf("%lf %lf", &pa[i].x, &pa[i].y);
    }
    
    scanf("%d", &nb);
    Point* pb = (Point*)malloc(nb * sizeof(Point));
    for (int i = 0; i < nb; ++i) {
        scanf("%lf %lf", &pb[i].x, &pb[i].y);
    }
    
    double res = solve(na, pa, nb, pb);
    if (res == -1) {
        printf("impossible\n");
    } else {
        printf("%.3f\n", res);
    }
    
    free(pa);
    free(pb);
    return 0;
}