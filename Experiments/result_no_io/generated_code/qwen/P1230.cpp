#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500
#define MAX_M 500000
#define MAX_W 1000

int main() {
    int m, n;
    scanf("%d %d", &m, &n);

    int t[MAX_N];
    int w[MAX_N];

    for (int i = 0; i < n; ++i) {
        scanf("%d", &t[i]);
    }

    for (int i = 0; i < n; ++i) {
        scanf("%d", &w[i]);
    }

    // Sort games by their deadlines in ascending order
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            if (t[j] > t[j + 1]) {
                int temp_t = t[j];
                t[j] = t[j + 1];
                t[j + 1] = temp_t;

                int temp_w = w[j];
                w[j] = w[j + 1];
                w[j + 1] = temp_w;
            }
        }
    }

    int result = m;
    for (int i = 0; i < n; ++i) {
        if (result >= w[i]) {
            result -= w[i];
        } else {
            break;
        }
    }

    printf("%d\n", result);
    return 0;
}