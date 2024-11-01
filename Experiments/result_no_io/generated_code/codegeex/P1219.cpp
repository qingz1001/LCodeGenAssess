#include <stdio.h>

int n;
int cnt = 0;
int col[15], dg[15], udg[15];

void print() {
    if (cnt < 3) {
        for (int i = 1; i <= n; i++) {
            printf("%d ", col[i]);
        }
        printf("\n");
    }
    cnt++;
}

void dfs(int x) {
    if (x == n + 1) {
        print();
        return;
    }
    for (int i = 1; i <= n; i++) {
        if (!col[i] && !dg[x + i] && !udg[x - i + n]) {
            col[i] = dg[x + i] = udg[x - i + n] = 1;
            dfs(x + 1);
            col[i] = dg[x + i] = udg[x - i + n] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);
    dfs(1);
    printf("%d", cnt);
    return 0;
}