#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000

int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int main() {
    int n, floors[MAX_N];
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &floors[i]);
    }
    
    qsort(floors, n, sizeof(int), compare);
    
    int current_floor = 0;
    int total_time = 0;
    
    // 上行
    for (int i = 0; i < n; i++) {
        if (floors[i] > current_floor) {
            total_time += (floors[i] - current_floor) * 6;
            current_floor = floors[i];
        }
        total_time += 5;  // 开门时间
        total_time += 1;  // 下人时间
    }
    
    // 下行回到0层
    total_time += current_floor * 4;
    
    printf("%d\n", total_time);
    
    return 0;
}