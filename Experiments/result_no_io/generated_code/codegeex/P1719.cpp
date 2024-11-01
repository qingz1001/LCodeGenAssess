#include <stdio.h>

#define MAX_N 121

int matrix[MAX_N][MAX_N];
int max_sum;

void find_max_rect(int n) {
    int i, j, k, l;
    int curr_sum;

    for (i = 1; i <= n; i++) {
        for (j = i; j <= n; j++) {
            int temp[MAX_N] = {0};
            for (k = 1; k <= n; k++) {
                for (l = i; l <= j; l++) {
                    temp[k] += matrix[l][k];
                }
                curr_sum = temp[k];
                for (l = k - 1; l > 0; l--) {
                    if (temp[l] > 0) {
                        curr_sum += temp[l];
                    } else {
                        temp[l] = 0;
                    }
                }
                if (curr_sum > max_sum) {
                    max_sum = curr_sum;
                }
            }
        }
    }
}

int main() {
    int n, i, j;
    scanf("%d", &n);
    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    max_sum = matrix[1][1];
    find_max_rect(n);
    printf("%d\n", max_sum);
    return 0;
}