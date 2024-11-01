#include <stdio.h>
#include <string.h>

#define MAX_N 10
#define MAX_ALPHABETS 10

int n;
char table[MAX_N][MAX_N][MAX_ALPHABETS];
int num[MAX_ALPHABETS];
int visited[MAX_ALPHABETS];
int is_valid = 1;

void dfs(int current) {
    if (!is_valid) return;

    if (current == n * n) {
        int sum = 0;
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < n; j++) {
                int val1 = num[table[i][j][0]];
                int val2 = num[table[i][0][j]];
                int val3 = num[table[0][i][j]];
                int res = val1 + val2 + sum;
                sum = res / num[table[0][0][0]];
                if (res % num[table[0][0][0]] != num[val3[0]]) {
                    is_valid = 0;
                    return;
                }
            }
        }
        if (sum != 0) {
            is_valid = 0;
            return;
        }
        return;
    }

    int row = (current - 1) / n + 1;
    int col = (current - 1) % n + 1;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            visited[i] = 1;
            num[table[row][col][0]] = i;
            dfs(current + 1);
            visited[i] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%s", table[i][0]);
    }
    for (int i = 1; i < n; i++) {
        scanf("%s", table[0][i]);
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < n; j++) {
            scanf("%s", table[i][j]);
        }
    }

    dfs(1);

    if (!is_valid) {
        printf("ERROR!\n");
    } else {
        for (int i = 0; i < n; i++) {
            if (visited[i]) {
                printf("%c=%d ", table[0][0][i], i);
            }
        }
        printf("\n");
        printf("%d\n", num[table[0][0][0]]);
    }

    return 0;
}