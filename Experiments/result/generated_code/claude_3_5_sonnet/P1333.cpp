#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_COLOR 26
#define MAX_STICKS 250000

int in_degree[MAX_COLOR];
int out_degree[MAX_COLOR];
bool used[MAX_COLOR];

void dfs(int node) {
    used[node] = true;
    for (int i = 0; i < MAX_COLOR; i++) {
        if (out_degree[node] > 0 && in_degree[i] > 0 && !used[i]) {
            dfs(i);
        }
    }
}

int main() {
    char color1[11], color2[11];
    int start = -1, end = -1;
    int odd_count = 0;
    memset(in_degree, 0, sizeof(in_degree));
    memset(out_degree, 0, sizeof(out_degree));
    memset(used, false, sizeof(used));

    while (scanf("%s %s", color1, color2) == 2) {
        int c1 = color1[0] - 'a';
        int c2 = color2[0] - 'a';
        out_degree[c1]++;
        in_degree[c2]++;
    }

    for (int i = 0; i < MAX_COLOR; i++) {
        if (in_degree[i] != out_degree[i]) {
            odd_count++;
            if (in_degree[i] == out_degree[i] + 1) {
                end = i;
            } else if (out_degree[i] == in_degree[i] + 1) {
                start = i;
            } else {
                printf("Impossible\n");
                return 0;
            }
        }
    }

    if (odd_count != 0 && odd_count != 2) {
        printf("Impossible\n");
        return 0;
    }

    if (start == -1) {
        for (int i = 0; i < MAX_COLOR; i++) {
            if (in_degree[i] > 0) {
                start = i;
                break;
            }
        }
    }

    dfs(start);

    for (int i = 0; i < MAX_COLOR; i++) {
        if ((in_degree[i] > 0 || out_degree[i] > 0) && !used[i]) {
            printf("Impossible\n");
            return 0;
        }
    }

    printf("Possible\n");
    return 0;
}