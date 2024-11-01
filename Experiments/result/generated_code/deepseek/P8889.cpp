#include <stdio.h>
#include <stdbool.h>

#define MAXN 500005

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    long long a[MAXN];
    long long b[MAXN];
    bool is_cut[MAXN] = {false};

    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }

    for (int i = 0; i < m; i++) {
        scanf("%lld", &b[i]);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (a[i] == b[j]) {
                is_cut[i] = true;
                break;
            }
        }
    }

    int segments = 0;
    bool in_segment = false;

    for (int i = 0; i < n; i++) {
        if (is_cut[i]) {
            if (in_segment) {
                segments++;
                in_segment = false;
            }
        } else {
            in_segment = true;
        }
    }

    if (in_segment) {
        segments++;
    }

    printf("%d\n", segments);

    return 0;
}