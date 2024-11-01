#include <stdio.h>
#include <stdbool.h>

int n;
int x[14], y[14], pair[14];
bool visited[14];

// 判断从位置 i 出发的虫洞是否会导致无限循环
bool cycle_exists(int i) {
    int pos = i;
    for (int count = 0; count < n; count++) {
        pos = pair[pos];
        pos = next_wormhole(pos);
        if (pos == -1) return false;
    }
    return true;
}

// 查找位置 i 右边的下一个虫洞
int next_wormhole(int i) {
    int next = -1;
    for (int j = 0; j < n; j++) {
        if (y[j] == y[i] && x[j] > x[i] && (next == -1 || x[j] < x[next])) {
            next = j;
        }
    }
    return next;
}

// 检查所有可能的虫洞配对
bool check_pairs() {
    for (int i = 1; i <= n; i++) {
        if (pair[i] == 0) return false;
    }
    for (int i = 1; i <= n; i++) {
        if (cycle_exists(i)) return true;
    }
    return false;
}

// 深度优先搜索配对虫洞
void dfs(int pos) {
    if (pos > n) {
        if (check_pairs()) {
            printf("1\n");
            exit(0);
        }
        return;
    }
    if (pair[pos] != 0) {
        dfs(pos + 1);
    } else {
        for (int i = pos + 1; i <= n; i++) {
            if (pair[i] == 0) {
                pair[pos] = i;
                pair[i] = pos;
                dfs(pos + 1);
                pair[pos] = 0;
                pair[i] = 0;
            }
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d %d", &x[i], &y[i]);
    }
    dfs(1);
    printf("0\n");
    return 0;
}