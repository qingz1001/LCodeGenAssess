#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100005
#define MAX_COLOR 1000005

int parent[MAX_COLOR];
int size[MAX_COLOR];
int color[MAX_N];
int segments;

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) {
        parent[x] = y;
        size[y] += size[x];
        size[x] = 0;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < MAX_COLOR; i++) {
        parent[i] = i;
        size[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        scanf("%d", &color[i]);
        size[color[i]]++;
    }

    segments = 0;
    for (int i = 1; i < n; i++) {
        if (color[i] != color[i-1]) {
            segments++;
        }
    }
    segments++;

    for (int i = 0; i < m; i++) {
        int op;
        scanf("%d", &op);

        if (op == 1) {
            int x, y;
            scanf("%d %d", &x, &y);
            if (x != y) {
                x = find(x);
                y = find(y);
                if (x != y) {
                    if (size[x] > 0 && size[y] > 0) {
                        segments--;
                    }
                    unite(x, y);
                }
            }
        } else if (op == 2) {
            printf("%d\n", segments);
        }
    }

    return 0;
}