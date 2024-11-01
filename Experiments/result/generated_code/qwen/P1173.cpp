#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000000001
#define INF 0x3f3f3f3f

typedef struct {
    int x, y;
} Point;

int n, m, c;
Point bugs[100001];
int visited[100001];

void dfs(int idx) {
    if (visited[idx]) return;
    visited[idx] = 1;
    for (int i = 0; i < c; ++i) {
        if (abs(bugs[i].x - bugs[idx].x) + abs(bugs[i].y - bugs[idx].y) == 1 && !visited[i]) {
            dfs(i);
        }
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d %d %d", &n, &m, &c);
        for (int i = 0; i < c; ++i) {
            scanf("%d %d", &bugs[i].x, &bugs[i].y);
            --bugs[i].x, --bugs[i].y; // Convert to zero-based index
        }

        int components = 0;
        for (int i = 0; i < c; ++i) {
            if (!visited[i]) {
                ++components;
                dfs(i);
            }
        }

        if (components > 1) {
            printf("0\n");
        } else {
            int min_replacements = INF;
            for (int i = 0; i < c; ++i) {
                memset(visited, 0, sizeof(visited));
                dfs(i);
                int new_components = 0;
                for (int j = 0; j < c; ++j) {
                    if (!visited[j]) {
                        ++new_components;
                        dfs(j);
                    }
                }
                if (new_components > 1) {
                    min_replacements = fmin(min_replacements, 1);
                }
            }
            printf("%d\n", min_replacements == INF ? -1 : min_replacements);
        }
    }
    return 0;
}