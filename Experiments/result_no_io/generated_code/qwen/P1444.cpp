#include <stdio.h>
#include <stdlib.h>

#define MAX_N 12

int n;
int holes[MAX_N][2];
int visited[MAX_N];

int dfs(int index) {
    if (visited[index]) return 0;
    visited[index] = 1;
    int next = (index + 1) % n;
    while (next != index && !visited[next]) {
        if (dfs(next)) return 1;
        next = (next + 1) % n;
    }
    return 0;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &holes[i][0], &holes[i][1]);
    }

    int count = 0;
    for (int i = 0; i < n; i += 2) {
        for (int j = i + 2; j < n; j += 2) {
            memset(visited, 0, sizeof(visited));
            visited[i] = 1;
            visited[j] = 1;
            if (!dfs((i + 2) % n)) {
                count++;
            }
        }
    }

    printf("%d\n", count);

    return 0;
}