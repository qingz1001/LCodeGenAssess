#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100

int n;
int graph[MAX_N + 1][MAX_N + 1];
int group[MAX_N + 1];
int group_size[3];

int check_group(int g) {
    for (int i = 1; i <= n; i++) {
        if (group[i] == g) {
            for (int j = i + 1; j <= n; j++) {
                if (group[j] == g && (!graph[i][j] || !graph[j][i])) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

int dfs(int person) {
    if (person > n) {
        if (group_size[1] == 0 || group_size[2] == 0) return 0;
        if (!check_group(1) || !check_group(2)) return 0;
        return 1;
    }

    for (int g = 1; g <= 2; g++) {
        group[person] = g;
        group_size[g]++;
        if (dfs(person + 1)) return 1;
        group_size[g]--;
    }

    return 0;
}

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        int x;
        while (scanf("%d", &x) && x) {
            graph[i][x] = 1;
        }
    }

    if (!dfs(1)) {
        printf("No solution\n");
    } else {
        for (int g = 1; g <= 2; g++) {
            printf("%d", group_size[g]);
            for (int i = 1; i <= n; i++) {
                if (group[i] == g) {
                    printf(" %d", i);
                }
            }
            printf("\n");
        }
    }

    return 0;
}