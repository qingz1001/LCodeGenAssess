#include <stdio.h>
#include <stdbool.h>

#define MAXN 20

bool canWin(int N, int edges[]) {
    for (int i = 0; i < N; i++) {
        if (edges[i] > 0 && edges[(i + 1) % N] > 0) {
            return true;
        }
    }
    return false;
}

int main() {
    int N;
    int edges[MAXN];

    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &edges[i]);
    }

    if (canWin(N, edges)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}