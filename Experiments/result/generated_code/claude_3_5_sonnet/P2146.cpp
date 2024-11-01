#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 100005

int n, q;
int dep[MAXN], fa[MAXN];
bool installed[MAXN];

int dfs(int x) {
    if (installed[x]) return 0;
    installed[x] = true;
    return dfs(fa[x]) + 1;
}

int un_dfs(int x) {
    if (!installed[x]) return 0;
    installed[x] = false;
    int cnt = 1;
    for (int i = 1; i < n; i++) {
        if (fa[i] == x && installed[i]) {
            cnt += un_dfs(i);
        }
    }
    return cnt;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf("%d", &fa[i]);
        dep[i] = dep[fa[i]] + 1;
    }

    scanf("%d", &q);
    char op[10];
    int x;
    while (q--) {
        scanf("%s %d", op, &x);
        if (op[0] == 'i') {
            printf("%d\n", dfs(x));
        } else {
            printf("%d\n", un_dfs(x));
        }
    }

    return 0;
}