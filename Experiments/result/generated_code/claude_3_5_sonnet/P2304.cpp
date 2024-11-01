#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX_N 100000
#define INF 1e18

typedef struct {
    long long x, y;
} Point;

typedef struct {
    int id;
    double angle;
} TreeAngle;

Point trees[MAX_N + 1];
int n, m;
int path[MAX_N + 1];
bool visited[MAX_N + 1];
TreeAngle angles[MAX_N];

int cmp(const void* a, const void* b) {
    TreeAngle* ta = (TreeAngle*)a;
    TreeAngle* tb = (TreeAngle*)b;
    if (ta->angle < tb->angle) return -1;
    if (ta->angle > tb->angle) return 1;
    return 0;
}

double getAngle(Point p) {
    return atan2(p.y, p.x);
}

long long dist(Point a, Point b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int findNextTree(Point cur) {
    int next_tree = -1;
    long long min_dist = INF;
    
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            long long d = dist(cur, trees[i]);
            if (d < min_dist) {
                min_dist = d;
                next_tree = i;
            }
        }
    }
    
    return next_tree;
}

void dfs(Point cur, int depth) {
    if (depth > m) {
        m = depth;
        for (int i = 1; i <= m; i++) {
            path[i] = visited[i];
        }
    }
    
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            Point vec = {trees[i].x - cur.x, trees[i].y - cur.y};
            double angle = getAngle(vec);
            angles[count++] = (TreeAngle){i, angle};
        }
    }
    
    qsort(angles, count, sizeof(TreeAngle), cmp);
    
    for (int i = 0; i < count; i++) {
        int id = angles[i].id;
        Point vec = {trees[id].x - cur.x, trees[id].y - cur.y};
        
        if (vec.x == 0 || vec.y == 0 || abs(vec.x) == abs(vec.y)) {
            int next = findNextTree(cur);
            if (next != -1 && next == id) {
                visited[id] = depth + 1;
                dfs(trees[id], depth + 1);
                visited[id] = 0;
            }
        }
    }
}

int countMachines() {
    bool used[MAX_N + 1] = {0};
    int machines = 0;
    
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            machines++;
            used[i] = true;
            Point cur = trees[i];
            
            while (true) {
                int next = -1;
                long long min_dist = INF;
                
                for (int j = 1; j <= n; j++) {
                    if (!used[j]) {
                        Point vec = {trees[j].x - cur.x, trees[j].y - cur.y};
                        if (vec.y > 0 && (vec.x == 0 || abs(vec.x) == vec.y)) {
                            long long d = dist(cur, trees[j]);
                            if (d < min_dist) {
                                min_dist = d;
                                next = j;
                            }
                        }
                    }
                }
                
                if (next == -1) break;
                
                used[next] = true;
                cur = trees[next];
            }
        }
    }
    
    return machines;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld %lld", &trees[i].x, &trees[i].y);
    }
    
    dfs((Point){0, 0}, 0);
    
    printf("%d\n", m);
    for (int i = 1; i <= m; i++) {
        printf("%d ", path[i]);
    }
    printf("\n");
    
    int machines = countMachines();
    printf("%d\n", machines);
    
    return 0;
}