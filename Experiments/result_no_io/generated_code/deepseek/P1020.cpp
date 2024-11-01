#include <stdio.h>
#include <stdlib.h>

#define MAXN 100005

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int binary_search(int *arr, int len, int val) {
    int left = 0, right = len - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] >= val) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

int main() {
    int heights[MAXN];
    int n = 0;
    while (scanf("%d", &heights[n]) != EOF) {
        n++;
    }

    // 计算最多能拦截多少导弹
    int dp[MAXN];
    int len = 0;
    for (int i = 0; i < n; i++) {
        int pos = binary_search(dp, len, heights[i]);
        if (pos == len) {
            dp[len++] = heights[i];
        } else {
            dp[pos] = heights[i];
        }
    }
    printf("%d\n", len);

    // 计算最少要配备多少套系统
    int dp2[MAXN];
    int len2 = 0;
    for (int i = 0; i < n; i++) {
        int pos = binary_search(dp2, len2, heights[i]);
        if (pos == len2) {
            dp2[len2++] = heights[i];
        } else {
            dp2[pos] = heights[i];
        }
    }
    printf("%d\n", len2);

    return 0;
}