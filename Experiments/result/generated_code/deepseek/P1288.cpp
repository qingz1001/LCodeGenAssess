#include <stdio.h>

int main() {
    int N;
    scanf("%d", &N);
    int edges[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &edges[i]);
    }

    // Check if there is any non-zero edge
    int hasNonZero = 0;
    for (int i = 0; i < N; i++) {
        if (edges[i] != 0) {
            hasNonZero = 1;
            break;
        }
    }

    if (hasNonZero) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}