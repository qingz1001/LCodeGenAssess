#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 500005

int a[MAXN];
int n, m;

void insert(int i, int k) {
    int j;
    for (j = i; j < n; j++) {
        a[j + 1] = a[j];
    }
    a[i] = k;
    n++;
}

int min_gap() {
    int i, min = INT_MAX;
    for (i = 1; i < n; i++) {
        if (a[i] - a[i - 1] < min) {
            min = a[i] - a[i - 1];
        }
    }
    return min;
}

int min_sort_gap() {
    int i, min = INT_MAX;
    for (i = 1; i < n; i++) {
        if (a[i] - a[i - 1] < min) {
            min = a[i] - a[i - 1];
        }
    }
    return min;
}

int main() {
    int i, x, y;
    char cmd[10];

    scanf("%d%d", &n, &m);
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (i = 0; i < m; i++) {
        scanf("%s %d %d", cmd, &x, &y);
        if (cmd[0] == 'I') {
            insert(x, y);
        } else if (cmd[0] == 'M' && cmd[4] == 'G') {
            printf("%d\n", min_gap());
        } else if (cmd[0] == 'M' && cmd[4] == 'S') {
            printf("%d\n", min_sort_gap());
        }
    }

    return 0;
}