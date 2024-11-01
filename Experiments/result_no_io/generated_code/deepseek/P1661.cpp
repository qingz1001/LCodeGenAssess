#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 50

typedef struct {
    int x, y;
} Point;

int n;
Point points[MAXN];
int parent[MAXN];

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unionSet(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if (rootX != rootY) {
        parent[rootX] = rootY;
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &points[i].x, &points[i].y);
        parent[i] = i;
    }

    int time = 0;
    while (1) {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (find(i) != find(j)) {
                    int dist = abs(points[i].x - points[j].x) + abs(points[i].y - points[j].y);
                    if (dist <= 2 * time) {
                        unionSet(i, j);
                    }
                }
            }
        }

        int root = find(0);
        int connected = 1;
        for (int i = 1; i < n; i++) {
            if (find(i) != root) {
                connected = 0;
                break;
            }
        }

        if (connected) {
            printf("%d\n", time);
            break;
        }

        time++;
    }

    return 0;
}