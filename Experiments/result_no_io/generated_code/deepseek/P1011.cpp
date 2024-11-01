#include <stdio.h>

int main() {
    int a, n, m, x;
    scanf("%d %d %d %d", &a, &n, &m, &x);

    int up[21], down[21], total[21];
    up[1] = a;
    down[1] = 0;
    total[1] = a;
    total[2] = a;

    for (int b = 0; b <= m; b++) {
        up[2] = b;
        down[2] = b;
        for (int i = 3; i < n; i++) {
            up[i] = up[i-1] + up[i-2];
            down[i] = up[i-1];
            total[i] = total[i-1] + up[i] - down[i];
        }
        if (total[n-1] == m) {
            printf("%d\n", total[x]);
            break;
        }
    }

    return 0;
}