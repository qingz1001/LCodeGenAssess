#include <stdio.h>
#include <stdbool.h>

#define MAXN 12

int n, sum;
int a[MAXN];
bool used[MAXN];

// 计算当前排列的最终和
int calculate_sum(int *arr, int len) {
    int temp[MAXN];
    for (int i = 0; i < len; i++) {
        temp[i] = arr[i];
    }
    while (len > 1) {
        for (int i = 0; i < len - 1; i++) {
            temp[i] = temp[i] + temp[i + 1];
        }
        len--;
    }
    return temp[0];
}

// 递归生成排列
bool generate_permutations(int pos) {
    if (pos == n) {
        return calculate_sum(a, n) == sum;
    }
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            a[pos] = i;
            used[i] = true;
            if (generate_permutations(pos + 1)) {
                return true;
            }
            used[i] = false;
        }
    }
    return false;
}

int main() {
    scanf("%d %d", &n, &sum);
    for (int i = 1; i <= n; i++) {
        used[i] = false;
    }
    if (generate_permutations(0)) {
        for (int i = 0; i < n; i++) {
            printf("%d ", a[i]);
        }
        printf("\n");
    }
    return 0;
}