#include <stdio.h>
#include <math.h>
#include <float.h>

#define MAX_N 1000
#define MAX_K 1000

typedef struct {
    int x, y;
} Point;

Point points[MAX_N];
int n, k;
int group[MAX_N];
double dist[MAX_N][MAX_N];

double calculate_distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double min_distance_between_groups() {
    double min_dist = DBL_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (group[i] != group[j]) {
                min_dist = fmin(min_dist, dist[i][j]);
            }
        }
    }
    return min_dist;
}

double dfs(int index, int remaining_groups) {
    if (index == n) {
        return remaining_groups == 0 ? min_distance_between_groups() : 0;
    }
    
    if (remaining_groups == 0 || n - index < remaining_groups) {
        return 0;
    }
    
    double max_dist = 0;
    for (int i = 0; i < k && i <= index; i++) {
        group[index] = i;
        max_dist = fmax(max_dist, dfs(index + 1, i == index ? remaining_groups - 1 : remaining_groups));
    }
    return max_dist;
}

int main() {
    scanf("%d %d", &n, &k);
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            dist[i][j] = dist[j][i] = calculate_distance(points[i], points[j]);
        }
    }
    
    double result = dfs(0, k);
    printf("%.2f\n", result);
    
    return 0;
}