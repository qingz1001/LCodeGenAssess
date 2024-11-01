#include <stdio.h>

int main() {
    int n, L;
    scanf("%d %d", &n, &L);
    
    int start[10000], end[10000];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &start[i], &end[i]);
    }
    
    // 对泥泞路进行排序
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (start[i] > start[j]) {
                int temp = start[i];
                start[i] = start[j];
                start[j] = temp;
                
                temp = end[i];
                end[i] = end[j];
                end[j] = temp;
            }
        }
    }
    
    int boards = 0;
    int current_position = 0;
    
    for (int i = 0; i < n; i++) {
        if (current_position < start[i]) {
            // 如果当前木板不能覆盖泥泞路，则需要新的一块木板
            boards++;
            current_position = start[i];
        }
        
        // 将木板尽可能延伸到泥泞路的终点
        if (current_position + L <= end[i]) {
            current_position += L;
        } else {
            // 如果当前木板不能覆盖剩余的泥泞路，则需要新的一块木板
            boards++;
            current_position = end[i] - (end[i] - current_position) % L;
        }
    }
    
    printf("%d\n", boards);
    return 0;
}