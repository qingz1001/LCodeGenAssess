#include <stdio.h>
#include <stdlib.h>

#define MAXN 53280
#define MAXM 150960

int n, m, x;
int points[MAXN];
int edges[MAXM][3];

void read_input() {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &points[i]);
    }
    scanf("%d %d %d", &m, &x);
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &edges[i][0], &edges[i][1], &edges[i][2]);
    }
}

void print_output(int k, int operations[][3]) {
    printf("%d\n", k);
    for (int i = 0; i < k; ++i) {
        printf("%d %d %d\n", operations[i][0], operations[i][1], operations[i][2]);
    }
}

int main() {
    read_input();
    // 这里添加你的解决方案代码
    int operations[10000][3];
    int k = 0;

    // 示例操作：将连接 2 号折跃点的隧道能量增加 2
    if (edges[0][0] == 1 && edges[0][1] == 2) {
        operations[k][0] = 1;
        operations[k][1] = 2;
        operations[k][2] = 2;
        k++;
    }

    print_output(k, operations);
    return 0;
}