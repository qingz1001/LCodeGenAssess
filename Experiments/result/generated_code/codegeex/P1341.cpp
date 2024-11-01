#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CHARS 52

char graph[MAX_CHARS][MAX_CHARS];
char result[1000];
bool visited[MAX_CHARS];
int n;

bool dfs(int depth) {
    if (depth == n + 1) {
        return true;
    }
    for (int i = 0; i < MAX_CHARS; i++) {
        if (!visited[i] && graph[result[depth - 1]][i]) {
            visited[i] = true;
            result[depth] = i + 'A';
            if (dfs(depth + 1)) {
                return true;
            }
            visited[i] = false;
        }
    }
    return false;
}

int main() {
    scanf("%d", &n);
    memset(graph, 0, sizeof(graph));
    memset(visited, 0, sizeof(visited));
    for (int i = 0; i < n; i++) {
        char a, b;
        scanf(" %c%c", &a, &b);
        graph[a - 'A'][b - 'A'] = 1;
        graph[b - 'A'][a - 'A'] = 1;
    }
    result[0] = 'A';
    visited[result[0] - 'A'] = true;
    if (dfs(1)) {
        printf("%s\n", result);
    } else {
        printf("No Solution\n");
    }
    return 0;
}