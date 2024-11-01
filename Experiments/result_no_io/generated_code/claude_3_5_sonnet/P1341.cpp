#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 26 * 26
#define MAX_CHAR 52

int n;
char pairs[MAX_N][2];
int graph[MAX_CHAR][MAX_CHAR];
int degree[MAX_CHAR];
char result[MAX_N + 2];
int result_len = 0;

int char_to_index(char c) {
    return (c >= 'a' && c <= 'z') ? (c - 'a') : (c - 'A' + 26);
}

char index_to_char(int i) {
    return (i < 26) ? ('a' + i) : ('A' + i - 26);
}

void dfs(int v) {
    for (int i = 0; i < MAX_CHAR; i++) {
        if (graph[v][i]) {
            graph[v][i]--;
            graph[i][v]--;
            dfs(i);
        }
    }
    result[result_len++] = index_to_char(v);
}

int main() {
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf(" %c %c", &pairs[i][0], &pairs[i][1]);
        int a = char_to_index(pairs[i][0]);
        int b = char_to_index(pairs[i][1]);
        graph[a][b]++;
        graph[b][a]++;
        degree[a]++;
        degree[b]++;
    }
    
    int start = -1;
    int odd_count = 0;
    for (int i = 0; i < MAX_CHAR; i++) {
        if (degree[i] % 2 == 1) {
            odd_count++;
            if (start == -1) start = i;
        }
    }
    
    if (odd_count > 2) {
        printf("No Solution\n");
        return 0;
    }
    
    if (start == -1) {
        for (int i = 0; i < MAX_CHAR; i++) {
            if (degree[i] > 0) {
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