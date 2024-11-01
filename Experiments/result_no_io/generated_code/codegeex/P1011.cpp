#include <stdio.h>

int main() {
    int a, n, m, x;
    scanf("%d %d %d %d", &a, &n, &m, &x);

    int on[] = {a, a, a + a};
    int off[] = {0, 0, a};
    int in_car[] = {a, a, a};

    for (int i = 3; i < n - 1; i++) {
        on[i] = on[i - 1] + on[i - 2];
        off[i] = on[i - 1];
        in_car[i] = in_car[i - 1] + on[i] - off[i];
    }

    printf("%d\n", in_car[x - 1]);

    return 0;
}