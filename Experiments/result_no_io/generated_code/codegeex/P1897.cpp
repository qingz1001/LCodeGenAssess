#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int *floors = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) {
        scanf("%d", &floors[i]);
    }
    
    // 对楼层进行排序
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(floors[i] > floors[j]) {
                int temp = floors[i];
                floors[i] = floors[j];
                floors[j] = temp;
            }
        }
    }
    
    int total_time = 0;
    for(int i = 0; i < n; i++) {
        total_time += (floors[i] - floors[i-1]) * 2 + 5 + 1; // 2*(up time + down time) + open door time + person leave time
    }
    
    // 加上最后回到0层的时间
    total_time += floors[n-1] * 2;
    
    printf("%d\n", total_time);
    
    free(floors);
    return 0;
}