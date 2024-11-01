#include <stdio.h>
#include <string.h>

#define MAXN 1000
#define MAXALPHA 52

int n;
char pairs[MAXN][3];
int graph[MAXALPHA][MAXALPHA];
int visited[MAXALPHA];
int path[MAXALPHA];

void add_edge(char a, char b) {
    int x = a - 'A', y = b - 'A';
    graph[x][y] = graph[y][x] = 1;
}

int is_valid(int x, int pos) {
    if (visited[x]) return 0;
    if (pos > 0 && !graph[path[pos-1]][x]) return 0;
    return 1;
}

int solve(int pos) {
    if (pos == n + 1) return 1;
    for (int i = 0; i < MAXALPHA; i++) {
        if (is_valid(i, pos)) {
            path[pos] = i;
            visited[i] = 1;
            if (solve(pos + 1)) return 1;
            visited[i] = 0;
        }
    }
    return 0;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", pairs[i]);
        add_edge(pairs[i][0], pairs[i][1]);
    }

    if (!solve(0)) {
        printf("No Solution\n");
    } else {
        for (int i = 1; i <= n; i++) {
            printf("%c", 'A' + path[i-1]);
        }
        printf("\n");
    }

    return 0;
}