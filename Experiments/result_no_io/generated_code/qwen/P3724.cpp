#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100
#define MAX_M 20
#define MAX_MC 100

int main() {
    int n, m, mc;
    scanf("%d %d %d", &n, &m, &mc);

    int a[MAX_N], w[MAX_N];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; ++i) {
        scanf("%d", &w[i]);
    }

    int C[MAX_M];
    for (int k = 0; k < m; ++k) {
        scanf("%d", &C[k]);

        int L = 0;
        int F = 1;
        int current_mc = mc;

        for (int i = 0; i < n; ++i) {
            current_mc -= a[i];
            if (current_mc < 0) {
                break;
            }

            int options[5] = {0};
            options[0] = F - 1;
            options[1] = current_mc + w[i];
            if (options[1] > current_mc) {
                options[1] = current_mc;
            }
            options[2] = L + 1;
            options[3] = F * L;
            options[4] = 0;

            int max_option = 0;
            for (int j = 0; j < 5; ++j) {
                if (options[j] > max_option && options[j] <= current_mc) {
                    max_option = options[j];
                }
            }

            if (max_option == 0) {
                break;
            }

            current_mc = max_option;
        }

        if (current_mc == 0) {
            printf("1\n");
        } else {
            printf("0\n");
        }
    }

    return 0;
}