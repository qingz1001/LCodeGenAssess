#include <stdio.h>
#include <string.h>
#include <limits.h>

int memo_max[15][15][15];
int memo_computed_table[15][15][15];
int a_values[15];
int n_global, k_global;

int max_val(int i, int j, int k) {
    if (i == j) {
        if (k == 0)
            return a_values[i];
        else
            return INT_MIN;
    }
    if (memo_computed_table[i][j][k])
        return memo_max[i][j][k];
    memo_computed_table[i][j][k] = 1;
    int current_max = INT_MIN;
    for (int s = i; s < j; s++) {
        // Operator '+'
        for (int t = 0; t <= k; t++) {
            int left = max_val(i, s, t);
            int right = max_val(s + 1, j, k - t);
            if (left != INT_MIN && right != INT_MIN) {
                int res = left + right;
                if (res > current_max)
                    current_max = res;
            }
        }
        // Operator '*'
        if (k >=1) {
            for (int t = 0; t <= k -1; t++) {
                int left = max_val(i, s, t);
                int right = max_val(s + 1, j, k -1 - t);
                if (left != INT_MIN && right != INT_MIN) {
                    int res = left * right;
                    if (res > current_max)
                        current_max = res;
                }
            }
        }
    }
    memo_max[i][j][k] = current_max;
    return current_max;
}

int main(){
    scanf("%d %d", &n_global, &k_global);
    for(int i=0;i<n_global;i++) {
        scanf("%d", &a_values[i]);
    }
    memset(memo_computed_table, 0, sizeof(memo_computed_table));
    int result = max_val(0, n_global-1, k_global);
    printf("%d\n", result);
    return 0;
}