#include <stdio.h>
#include <stdlib.h>

#define MAX 25

int visited[MAX][MAX];
int results[MAX * MAX];

void dfs(int a, int b, int c, int n) {
    if (visited[a][b]) return;
    visited[a][b] = 1;
    results[n++] = c;

    if (a > 0) dfs(0, b, c, n);
    if (b > 0) dfs(a, 0, c, n);
    if (a < MAX && c >= b - a) dfs(a + b - a, b, c - (b - a), n);
    if (b < MAX && c >= a) dfs(a, b + a - c, c - a, n);
}

int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);

    dfs(0, 0, c, 0);

    for (int i = 0; i < MAX * MAX; i++) {
        if (results[i] == 0) break;
        printf("%d ", results[i]);
    }
    printf("\n");

    return 0;
}