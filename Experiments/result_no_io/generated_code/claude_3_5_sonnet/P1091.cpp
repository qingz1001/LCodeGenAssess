#include <stdio.h>

#define MAX_N 100

int n;
int height[MAX_N];
int left[MAX_N], right[MAX_N];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &height[i]);
    }
    
    // 计算左边最长上升子序列
    for (int i = 0; i < n; i++) {
        left[i] = 1;
        for (int j = 0; j < i; j++) {
            if (height[i] > height[j]) {
                left[i] = max(left[i], left[j] + 1);
            }
        }
    }
    
    // 计算右边最长下降子序列
    for (int i = n - 1; i >= 0; i--) {
        right[i] = 1;
        for (int j = n - 1; j > i; j--) {
            if (height[i] > height[j]) {
                right[i] = max(right[i], right[j] + 1);
            }
        }
    }
    
    // 找到最大的 k
    int max_k = 0;
    for (int i = 0; i < n; i++) {
        max_k = max(max_k, left[i] + right[i] - 1);
    }
    
    // 计算需要出列的同学数
    int result = n - max_k;
    
    printf("%d\n", result);
    
    return 0;
}