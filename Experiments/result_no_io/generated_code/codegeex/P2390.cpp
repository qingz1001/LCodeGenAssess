#include <stdio.h>
#include <stdlib.h>

// 比较函数，用于qsort排序
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int main() {
    int t, n;
    scanf("%d %d", &t, &n);
    
    int *landmarks = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        scanf("%d", &landmarks[i]);
    }
    
    // 对地标进行排序
    qsort(landmarks, n, sizeof(int), compare);
    
    int max_landmarks = 0;
    int left = 0, right = n - 1;
    
    while (left <= right) {
        // 计算向左和向右走的步数
        int left_steps = (left > 0) ? landmarks[left] - landmarks[left - 1] : landmarks[left];
        int right_steps = (right < n - 1) ? landmarks[right + 1] - landmarks[right] : t;
        
        // 计算两种方案能访问的地标数
        int landmarks_left = left + (t - left_steps) / 2;
        int landmarks_right = right - (t - right_steps) / 2;
        
        // 取两种方案中能访问的地标数的最大值
        int current_max = landmarks_left + landmarks_right + 1;
        if (current_max > max_landmarks) {
            max_landmarks = current_max;
        }
        
        // 根据步数选择前进方向
        if (left_steps <= right_steps) {
            left++;
        } else {
            right--;
        }
    }
    
    printf("%d\n", max_landmarks);
    
    free(landmarks);
    return 0;
}