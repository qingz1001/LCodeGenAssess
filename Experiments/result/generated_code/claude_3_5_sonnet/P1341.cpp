#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 2600
#define MAX_CHAR 256

int n;
char pairs[MAX_N][2];
int graph[MAX_CHAR][MAX_CHAR];
char in_degree[MAX_CHAR], out_degree[MAX_CHAR];
char result[MAX_N + 2];
int result_len;

void dfs(char c) {
    for (int i = 0; i < MAX_CHAR; i++) {
        if (graph[c][i]) {
            graph[c][i]--;
            graph[i][c]--;
            dfs(i);
        }
    }
    result[result_len++] = c;
}

int main() {
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf(" %c%c", &pairs[i][0], &pairs[i][1]);
        char a = pairs[i][0], b = pairs[i][1];
        graph[a][b]++;
        graph[b][a]++;
        in_degree[a]++;
        in_degree[b]++;
        out_degree[a]++;
        out_degree[b]++;
    }

    char start = 0;
    for (int i = 0; i < MAX_CHAR; i++) {
        if (in_degree[i] & 1) {
            start = i;
            break;
        }
    }
    if (!start) {
        for (int i = 0; i < MAX_CHAR; i++) {
            if (in_degree[i]) {
                start = i;
                break;
            }
        }
    }

    dfs(start);

    if (result_len != n + 1) {
        printf("No Solution\n");
    } else {
        for (int i = result_len - 1; i >= 0; i--) {
            printf("%c", result[i]);
        }
        printf("\n");
    }

    return 0;
}