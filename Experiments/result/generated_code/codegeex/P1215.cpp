#include <stdio.h>

int a, b, c;
int visited[21][21][21] = {0};
int milk[21][21][21] = {0};
int possible = 0;

void dfs(int a, int b, int c) {
    if (visited[a][b][c] == 0) {
        visited[a][b][c] = 1;
        if (a == 0) {
            milk[c] = 1;
            possible = 1;
        }
        if (a > 0) {
            if (b < c) {
                dfs(a - (c - b), b + a, c);
            }
            if (c < a) {
                dfs(a - c, b, c + a);
            }
        }
        if (b > 0) {
            if (a < b) {
                dfs(a + b, b - a, c);
            }
            if (c < b) {
                dfs(a, b - c, c + b);
            }
        }
        if (c > 0) {
            if (a < c) {
                dfs(a + c, b, c - a);
            }
            if (b < c) {
                dfs(a, b + c, c - b);
            }
        }
    }
}

int main() {
    scanf("%d%d%d", &a, &b, &c);
    dfs(0, 0, c);
    for (int i = 0; i <= c; i++) {
        if (milk[i] == 1) {
            printf("%d ", i);
        }
    }
    return 0;
}