#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int n, k;
int a[15];
long memo_max[15][15][15];
int memo_computed_flag[15][15][15];

long max_val(int i, int j, int c) {
    if (i == j) {
        if (c == 0)
            return a[i];
        else
            return LONG_MIN;
    }
    if (memo_computed_flag[i][j][c])
        return memo_max[i][j][c];
    memo_computed_flag[i][j][c] = 1;
    long res = LONG_MIN;
    for (int m = i; m < j; m++) {
        // Operator '+'
        for (int c1 = 0; c1 <= c; c1++) {
            int c2 = c - c1;
            long left = max_val(i, m, c1);
            long right = max_val(m + 1, j, c2);
            if (left != LONG_MIN && right != LONG_MIN) {
                long temp = left + right;
                if (temp > res)
                    res = temp;
            }
        }
        // Operator '*'
        if (c >= 1) {
            for (int c1 = 0; c1 <= c -1; c1++) {
                int c2 = c -1 - c1;
                long left = max_val(i, m, c1);
                long right = max_val(m + 1, j, c2);
                if (left != LONG_MIN && right != LONG_MIN) {
                    long temp = left * right;
                    if (temp > res)
                        res = temp;
                }
            }
        }
    }
    memo_max[i][j][c] = res;
    return res;
}

int main(){
    scanf("%d %d", &n, &k);
    for(int i=0;i<n;i++) scanf("%d", &a[i]);
    // Initialize memo_computed_flag to 0
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            for(int c=0;c<=k;c++) {
                memo_computed_flag[i][j][c] = 0;
            }
        }
    }
    long result = max_val(0, n-1, k);
    printf("%ld\n", result);
    return 0;
}