#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000000
#define MAXQ 25000

int n, q;
int conditions[MAXQ][3];
int min_values[MAXN + 1];

void update(int l, int r, int x) {
    for (int i = l; i <= r && i <= n; i++) {
        min_values[i] = x;
    }
}

int main() {
    scanf("%d %d", &n, &q);
    for (int i = 0; i < q; i++) {
        scanf("%d %d %d", &conditions[i][0], &conditions[i][1], &conditions[i][2]);
    }

    for (int i = 1; i <= n; i++) {
        min_values[i] = INT_MAX;
    }

    for (int i = 0; i < q; i++) {
        int l = conditions[i][0];
        int r = conditions[i][1];
        int x = conditions[i][2];
        if (x > min_values[r]) {
            printf("%d\n", i + 1);
            return 0;
        }
        update(l, r, x);
    }

    printf("0\n");
    return 0;
}