#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double x, y;
} Point;

typedef struct {
    Point p;
    double w;
} WeightedPoint;

int main() {
    int n;
    scanf("%d", &n);
    
    WeightedPoint weights[n];
    for (int i = 0; i < n; i++) {
        scanf("%lf %lf %lf", &weights[i].p.x, &weights[i].p.y, &weights[i].w);
    }
    
    double totalWeight = 0.0;
    Point centerOfMass = {0.0, 0.0};
    
    for (int i = 0; i < n; i++) {
        totalWeight += weights[i].w;
        centerOfMass.x += weights[i].p.x * weights[i].w;
        centerOfMass.y += weights[i].p.y * weights[i].w;
    }
    
    centerOfMass.x /= totalWeight;
    centerOfMass.y /= totalWeight;
    
    printf("%.3f %.3f\n", centerOfMass.x, centerOfMass.y);
    
    return 0;
}