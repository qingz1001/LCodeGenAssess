#include <stdio.h>
#include <stdlib.h>

#define MAXN 500005

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    long long a[MAXN];
    for (int i = 0; i < n; ++i) {
        scanf("%lld", &a[i]);
    }

    long long b[m];
    for (int i = 0; i < m; ++i) {
        scanf("%lld", &b[i]);
    }

    // Create a set to store the positions of elements in b within a
    int pos[n + 1];
    for (int i = 0; i <= n; ++i) {
        pos[i] = -1;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i] == b[j]) {
                pos[i] = j;
                break;
            }
        }
    }

    // Count the number of segments after cutting
    int segments = 0;
    for (int i = 0; i < n; ++i) {
        if (pos[i] != -1 && (i == 0 || pos[i - 1] == -1)) {
            segments++;
        }
    }

    printf("%d\n", segments);
    return 0;
}