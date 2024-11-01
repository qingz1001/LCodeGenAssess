#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 3

void sort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main() {
    int start[MAX_N], end[MAX_N];
    
    // 读取输入
    for (int i = 0; i < MAX_N; i++) {
        scanf("%d", &start[i]);
    }
    for (int i = 0; i < MAX_N; i++) {
        scanf("%d", &end[i]);
    }
    
    // 排序
    sort(start, MAX_N);
    sort(end, MAX_N);
    
    // 检查是否可能
    int diff1 = start[1] - start[0];
    int diff2 = start[2] - start[1];
    int end_diff1 = end[1] - end[0];
    int end_diff2 = end[2] - end[1];
    
    if (diff1 != end_diff1 || diff2 != end_diff2) {
        printf("NO\n");
        return 0;
    }
    
    // 计算最少步数
    int steps = 0;
    for (int i = 0; i < MAX_N; i++) {
        steps += abs(start[i] - end[i]) / diff1;
    }
    steps /= 2;  // 每次移动会改变两个位置
    
    printf("YES\n%d\n", steps);
    
    return 0;
}