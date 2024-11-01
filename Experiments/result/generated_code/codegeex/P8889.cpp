#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 500005

long long a[MAX_SIZE], b[MAX_SIZE];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    for (int i = 0; i < m; i++) {
        scanf("%lld", &b[i]);
    }

    int cutPoints[MAX_SIZE] = {0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i] == b[j]) {
                cutPoints[i] = 1;
                break;
            }
        }
    }

    int segments = 0;
    int inSegment = 0;
    for (int i = 0; i < n; i++) {
        if (cutPoints[i]) {
            segments++;
            inSegment = 0;
        } else if (!inSegment) {
            segments++;
            inSegment = 1;
        }
    }

    printf("%d\n", segments);
    return 0;
}