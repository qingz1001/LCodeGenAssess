#include <stdio.h>

int main() {
    int n, m, type;
    scanf("%d %d %d", &n, &m, &type);

    int t[101], q[101];
    for (int i = 0; i < n; i++) {
        scanf("%d", &t[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%d", &q[i]);
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (t[i] == 1 && q[i] == 1) {
            count++;
        }
    }

    int bottles = (count >= m) ? m : count;
    bottles += (n - count);

    printf("%d\n", bottles);
    return 0;
}