#include <stdio.h>

int main() {
    int a, n, m, x;
    scanf("%d %d %d %d", &a, &n, &m, &x);

    int up[21] = {0, a, a};
    int down[21] = {0, 0, 0};
    int people[21] = {0, a, a};

    for (int i = 3; i < n; i++) {
        up[i] = up[i-1] + up[i-2];
        down[i] = up[i-1];
        people[i] = people[i-1] + up[i] - down[i];
    }

    int k = 1;
    while (1) {
        up[n-1] = k;
        down[n-1] = up[n-2];
        people[n-1] = people[n-2] + up[n-1] - down[n-1];
        if (people[n-1] == m) break;
        k++;
    }

    printf("%d\n", people[x]);

    return 0;
}