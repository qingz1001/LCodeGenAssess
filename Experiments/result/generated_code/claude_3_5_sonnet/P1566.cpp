#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_M 30
#define MAX_X 1000

int count_equations(int *arr, int m) {
    int count = 0;
    int sum[MAX_X + 1] = {0};
    int max_sum = 0;

    // 计算所有可能的和
    for (int mask = 1; mask < (1 << m); mask++) {
        int s = 0;
        for (int i = 0; i < m; i++) {
            if (mask & (1 << i)) {
                s += arr[i];
            }
        }
        if (s <= MAX_X) {
            sum[s] = 1;
            if (s > max_sum) max_sum = s;
        }
    }

    // 检查每个元素是否可以表示为其他元素之和
    for (int i = 0; i < m; i++) {
        int x = arr[i];
        if (x <= max_sum && sum[x]) {
            // 检查x是否可以由其他元素表示
            int temp_sum[MAX_X + 1] = {0};
            for (int j = 0; j < m; j++) {
                if (j != i) {
                    for (int k = max_sum; k >= arr[j]; k--) {
                        if (temp_sum[k - arr[j]]) {
                            temp_sum[k] = 1;
                        }
                    }
                    temp_sum[arr[j]] = 1;
                }
            }
            if (temp_sum[x]) count++;
        }
    }

    return count;
}

int main() {
    int t, m;
    scanf("%d", &t);

    while (t--) {
        scanf("%d", &m);
        int arr[MAX_M];
        for (int i = 0; i < m; i++) {
            scanf("%d", &arr[i]);
        }
        printf("%d\n", count_equations(arr, m));
    }

    return 0;
}