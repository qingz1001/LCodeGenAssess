#include <stdio.h>
#include <limits.h>

int main() {
    int n;
    scanf("%d", &n);
    int a[200001];
    int total_sum = 0;
    int max_sum1 = INT_MIN, max_sum2 = INT_MIN;
    int min_sum1 = INT_MAX, min_sum2 = INT_MAX;
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        total_sum += a[i];
        max_sum1 = (max_sum1 > a[i]) ? max_sum1 : a[i];
        min_sum1 = (min_sum1 < a[i]) ? min_sum1 : a[i];
    }
    
    // 计算环状序列的最大两段子段和
    for (int i = 0; i < n; i++) {
        int left_sum = 0, right_sum = 0;
        // 计算左段和
        for (int j = 0; j < i; j++) {
            left_sum += a[j];
        }
        // 计算右段和
        for (int j = i; j < n; j++) {
            right_sum += a[j];
        }
        // 更新最大和
        max_sum2 = (max_sum2 > left_sum + right_sum) ? max_sum2 : left_sum + right_sum;
    }
    
    // 计算非环状序列的最大两段子段和
    for (int i = 0; i < n; i++) {
        int max_left_sum = INT_MIN, max_right_sum = INT_MIN;
        int min_left_sum = INT_MAX, min_right_sum = INT_MAX;
        int left_sum = 0, right_sum = 0;
        
        // 计算左段和
        for (int j = 0; j <= i; j++) {
            left_sum += a[j];
            max_left_sum = (max_left_sum > left_sum) ? max_left_sum : left_sum;
            min_left_sum = (min_left_sum < left_sum) ? min_left_sum : left_sum;
        }
        
        // 计算右段和
        for (int j = i; j < n; j++) {
            right_sum += a[j];
            max_right_sum = (max_right_sum > right_sum) ? max_right_sum : right_sum;
            min_right_sum = (min_right_sum < right_sum) ? min_right_sum : right_sum;
        }
        
        // 更新最大和
        max_sum1 = (max_sum1 > max_left_sum + max_right_sum) ? max_sum1 : max_left_sum + max_right_sum;
        min_sum1 = (min_sum1 < min_left_sum + min_right_sum) ? min_sum1 : min_left_sum + min_right_sum;
    }
    
    // 结果
    int result = (max_sum1 > max_sum2) ? max_sum1 : max_sum2;
    printf("%d\n", result);
    
    return 0;
}