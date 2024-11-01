#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_LEN 1001

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    char num_str[MAX_LEN];
    int m;
    scanf("%s %d", num_str, &m);

    int len = strlen(num_str);
    int dp_min[MAX_LEN][MAX_LEN];
    int dp_max[MAX_LEN][MAX_LEN];

    // Initialize dp arrays
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            dp_min[i][j] = INT_MAX;
            dp_max[i][j] = INT_MIN;
        }
    }

    // Fill dp arrays for single digit numbers
    for (int i = 0; i < len; i++) {
        dp_min[i][i] = dp_max[i][i] = (num_str[i] - '0') % m;
    }

    // Fill dp arrays for multi-digit numbers
    for (int l = 2; l <= len; l++) {
        for (int i = 0; i <= len - l; i++) {
            int j = i + l - 1;
            int num = 0;
            for (int k = i; k <= j; k++) {
                num = num * 10 + (num_str[k] - '0');
            }
            num %= m;
            dp_min[i][j] = dp_max[i][j] = num;
            for (int k = i; k < j; k++) {
                dp_min[i][j] = min(dp_min[i][j], (dp_min[i][k] * dp_min[k+1][j]) % m);
                dp_max[i][j] = max(dp_max[i][j], (dp_max[i][k] * dp_max[k+1][j]) % m);
            }
        }
    }

    int min_val = dp_min[0][len-1];
    int max_val = dp_max[0][len-1];
    int min_k = 0, max_k = 0;

    // Find the minimum k for min_val
    for (int k = 0; k < len - 1; k++) {
        if (dp_min[0][k] * dp_min[k+1][len-1] % m == min_val) {
            min_k = k;
            break;
        }
    }

    // Find the minimum k for max_val
    for (int k = 0; k < len - 1; k++) {
        if (dp_max[0][k] * dp_max[k+1][len-1] % m == max_val) {
            max_k = k;
            break;
        }
    }

    printf("%d %d %d %d\n", min_val, min_k, max_val, max_k);

    return 0;
}