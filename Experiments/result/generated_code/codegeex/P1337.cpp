#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 1001

typedef struct {
    double x, y, w;
} Point;

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int main() {
    int n;
    scanf("%d", &n);
    Point holes[MAXN], weights[MAXN];
    
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf", &holes[i].x, &holes[i].y, &holes[i].w);
    }
    
    double x = 0, y = 0, total_weight = 0;
    for (int i = 0; i < n; i++) {
        x += holes[i].x * holes[i].w;
        y += holes[i].y * holes[i].w;
        total_weight += holes[i].w;
    }
    
    x /= total_weight;
    y /= total_weight;
    
    Point equilibrium = {x, y, 0};
    
    for (int i = 0; i < n; i++) {
        double force = holes[i].w / dist(equilibrium, holes[i]);
        double dx = force * (holes[i].x - equilibrium.x);
        double dy = force * (holes[i].y - equilibrium.y);
        
        equilibrium.x += dx;
        equilibrium.y += dy;
    }
    
    printf("%.3lf %.3lf\n", equilibrium.x, equilibrium.y);
    
    return 0;
}