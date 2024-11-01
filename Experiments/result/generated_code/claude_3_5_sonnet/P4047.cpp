#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_N 1000
#define INF 1e9

typedef struct {
    int x, y;
} Point;

Point points[MAX_N];
int n, k;
int parent[MAX_N];

double dist(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

void unite(int x, int y) {
    parent[find(x)] = find(y);
}

int count_groups() {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (parent[i] == i) count++;
    }
    return count;
}

double solve() {
    double left = 0, right = INF;
    
    while (right - left > 1e-6) {
        double mid = (left + right) / 2;
        
        for (int i = 0; i < n; i++) parent[i] = i;
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (dist(points[i], points[j]) <= mid) {
                    unite(i, j);
                }
            }
        }
        
        if (count_groups() <= k) {
            left = mid;
        } else {
            right = mid;
        }
    }
    
    return left;
}

int main() {
    scanf("%d %d", &n, &k);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }
    
    double result = solve();
    printf("%.2f\n", result);
    
    return 0;
}