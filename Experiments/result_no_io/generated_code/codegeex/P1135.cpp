#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_N 200

int n, a, b;
int k[MAX_N + 1];
int dist[MAX_N + 1];

bool can_go_up(int floor) {
    return floor + k[floor] <= n;
}

bool can_go_down(int floor) {
    return floor - k[floor] >= 1;
}

int main() {
    scanf("%d %d %d", &n, &a, &b);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &k[i]);
    }

    // 初始化距离数组，所有楼层距离设为无穷大
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
    }

    // 从起点开始
    dist[a] = 0;

    // 使用广度优先搜索（BFS）来寻找最短路径
    bool found = false;
    for (int i = 1; i <= n && !found; i++) {
        for (int j = 1; j <= n; j++) {
            if (dist[j] == i) {
                if (can_go_up(j)) {
                    if (dist[j + k[j]] > i + 1) {
                        dist[j + k[j]] = i + 1;
                    }
                }
                if (can_go_down(j)) {
                    if (dist[j - k[j]] > i + 1) {
                        dist[j - k[j]] = i + 1;
                    }
                }
                if (j == b) {
                    found = true;
                }
            }
        }
    }

    if (dist[b] == INT_MAX) {
        printf("-1\n");
    } else {
        printf("%d\n", dist[b]);
    }

    return 0;
}