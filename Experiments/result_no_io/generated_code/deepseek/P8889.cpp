#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXN 500005

int a[MAXN];
bool is_cut_point[MAXN];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < m; i++) {
        int b;
        scanf("%d", &b);
        for (int j = 0; j < n; j++) {
            if (a[j] == b) {
                is_cut_point[j] = true;
            }
        }
    }

    int segments = 0;
    bool in_segment = false;

    for (int i = 0; i < n; i++) {
        if (is_cut_point[i]) {
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