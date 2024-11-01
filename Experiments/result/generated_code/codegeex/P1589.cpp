#include <stdio.h>
#include <stdlib.h>

// 定义一个结构体来表示每段泥泞路的起点和终点
typedef struct {
    int start;
    int end;
} Road;

// 比较函数，用于qsort排序
int compare(const void *a, const void *b) {
    return ((Road *)a)->start - ((Road *)b)->start;
}

int main() {
    int n, L;
    scanf("%d %d", &n, &L);
    
    Road roads[n];
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &roads[i].start, &roads[i].end);
    }
    
    // 按照泥泞路的起点进行排序
    qsort(roads, n, sizeof(Road), compare);
    
    int board_count = 0;
    int current_end = 0;
    
    for (int i = 0; i < n; i++) {
        // 如果当前木板的终点覆盖不了当前泥泞路的起点，则需要新的木板
        if (current_end < roads[i].start) {
            board_count++;
            current_end = roads[i].end;
        }
        // 如果当前木板的终点覆盖了当前泥泞路的起点，但覆盖不了终点，则更新终点
        else if (current_end < roads[i].end) {
            current_end = roads[i].end;
        }
    }
    
    printf("%d\n", board_count);
    return 0;
}