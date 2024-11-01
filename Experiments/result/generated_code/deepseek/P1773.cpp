#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_LEN 1000

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void calculate(char *num_str, int m) {
    int len = strlen(num_str);
    int dp_min[MAX_LEN][MAX_LEN];
    int dp_max[MAX_LEN][MAX_LEN];
    int min_k[MAX_LEN][MAX_LEN];
    int max_k[MAX_LEN][MAX_LEN];

    // Initialize dp arrays
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            dp_min[i][j] = INT_MAX;
            dp_max[i][j] = INT_MIN;
            min_k[i][j] = INT_MAX;
            max_k[i][j] = INT_MIN;
        }
    }

    // Fill base cases
    for (int i = 0; i < len; i++) {
        dp_min[i][i] = dp_max[i][i] = (num_str[i] - '0') % m;
        min_k[i][i] = max_k[i][i] = 0;
    }

    // Fill dp arrays
    for (int l = 2; l <= len; l++) {
        for (int i = 0; i <= len - l; i++) {
            int j = i + l - 1;
            for (int k = i; k < j; k++) {
                int product = (dp_min[i][k] * dp_min[k+1][j]) % m;
                if (product < dp_min[i][j]) {
                    dp_min[i][j] = product;
                    min_k[i][j] = min_k[i][k] + min_k[k+1][j] + 1;
                } else if (product == dp_min[i][j]) {
                    min_k[i][j] = min(min_k[i][j], min_k[i][k] + min_k[k+1][j] + 1);
                }

                product = (dp_max[i][k] * dp_max[k+1][j]) % m;
                if (product > dp_max[i][j]) {
                    dp_max[i][j] = product;
                    max_k[i][j] = max_k[i][k] + max_k[k+1][j] + 1;
                } else if (product == dp_max[i][j]) {
                    max_k[i][j] = min(max_k[i][j], max_k[i][k] + max_k[k+1][j] + 1);
                }
            }
        }
    }

    printf("%d %d %d %d\n", dp_min[0][len-1], min_k[0][len-1], dp_max[0][len-1], max_k[0][len-1]);
}

int main() {
    char num_str[MAX_LEN + 1];
    int m;

    scanf("%s", num_str);
    scanf("%d", &m);

    calculate(num_str, m);

    return 0;
}