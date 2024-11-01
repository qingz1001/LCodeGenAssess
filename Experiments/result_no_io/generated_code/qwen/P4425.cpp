#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int T[MAXN];
int n, m, p;
int LastAns = -1;

void update(int x, int y) {
    if (p == 0) {
        T[x] = y;
    } else {
        x ^= LastAns;
        y ^= LastAns;
        T[x] = y;
    }
}

int find_last_marked() {
    for (int i = 0; i < n; i++) {
        if (T[i] <= LastAns) {
            return i + 1;
        }
    }
    return -1;
}

int main() {
    scanf("%d %d %d", &n, &m, &p);
    for (int i = 0; i < n; i++) {
        scanf("%d", &T[i]);
    }

    // Initial answer
    LastAns = find_last_marked();
    printf("%d\n", LastAns);

    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        update(x, y);
        LastAns = find_last_marked();
        printf("%d\n", LastAns);
    }

    return 0;
}