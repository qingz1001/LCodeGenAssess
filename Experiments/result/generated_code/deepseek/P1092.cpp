#include <stdio.h>
#include <string.h>

#define MAXN 26

int n;
char a[MAXN + 1], b[MAXN + 1], c[MAXN + 1];
int used[MAXN], map[MAXN];

int check() {
    int carry = 0;
    for (int i = n - 1; i >= 0; i--) {
        int x = map[a[i] - 'A'];
        int y = map[b[i] - 'A'];
        int z = map[c[i] - 'A'];
        if ((x + y + carry) % n != z) return 0;
        carry = (x + y + carry) / n;
    }
    return 1;
}

int dfs(int pos) {
    if (pos == n) return check();
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            used[i] = 1;
            map[pos] = i;
            if (dfs(pos + 1)) return 1;
            used[i] = 0;
        }
    }
    return 0;
}

int main() {
    scanf("%d", &n);
    scanf("%s%s%s", a, b, c);

    memset(used, 0, sizeof(used));
    memset(map, -1, sizeof(map));

    dfs(0);

    for (int i = 0; i < n; i++) {
        printf("%d ", map[i]);
    }
    printf("\n");

    return 0;
}