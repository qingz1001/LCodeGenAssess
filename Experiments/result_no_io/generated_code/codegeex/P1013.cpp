#include <stdio.h>
#include <string.h>

int n;
char s[10][10][10];
int num[10];
int base;
int used[10];

int check(int x, int y) {
    int a = num[x], b = num[y], c = num[s[x][y][0]];
    int sum = a + b;
    if (sum == c) return 1;
    if (sum % base == c) {
        int carry = sum / base;
        if (carry == num[s[x][y][1]]) return 1;
    }
    return 0;
}

void dfs(int pos) {
    if (pos == n) {
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < n; j++) {
                if (!check(i, j)) return;
            }
        }
        for (int i = 1; i < n; i++) {
            printf("%c=%d ", 'A' + i - 1, num[i]);
        }
        printf("\n");
        printf("%d\n", base);
        exit(0);
    }
    for (int i = 0; i < base; i++) {
        if (!used[i]) {
            used[i] = 1;
            num[pos] = i;
            dfs(pos + 1);
            used[i] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%s", s[i][j]);
        }
    }
    base = 4;
    dfs(1);
    printf("ERROR!\n");
    return 0;
}