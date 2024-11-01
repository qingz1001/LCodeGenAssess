#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 50

typedef struct {
    long long x, y;
} Point;

Point points[MAX_N];
int parent[MAX_N];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    int root_x = find(x);
    int root_y = find(y);
    if (root_x != root_y) {
        parent[root_x] = root_y;
    }
}

int all_connected(int n) {
    int root = find(0);
    for (int i = 1; i < n; i++) {
        if (find(i) != root) {
            return 0;
        }
    }
    return 1;
}

int is_connected(Point a, Point b, double time) {
    long long dx = llabs(a.x - b.x);
    long long dy = llabs(a.y - b.y);
    return dx * dx + dy * dy <= 4 * time * time;
}

double min_time_to_connect(int n) {
    double left = 0, right = 2e9;
    while (right - left > 1e-6) {
        double mid = (left + right) / 2;
        
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (is_connected(points[i], points[j], mid)) {
                    unite(i, j);
                }
            }
        }
        
        if (all_connected(n)) {
            right = mid;
        } else {
            left = mid;
        }
    }
    
    return left;
}

int main() {
    int n;
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%lld %lld", &points[i].x, &points[i].y);
    }
    
    double result = min_time_to_connect(n);
    printf("%.6f\n", result);
    
    return 0;
}