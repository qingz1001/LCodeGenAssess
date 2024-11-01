#include <stdio.h>
#include <stdlib.h>

// 定义MM结构体，包含花费的金钱、人品和所需时间
typedef struct {
    int rmb;
    int rp;
    int time;
} MM;

// 比较函数，用于qsort排序
int cmp(const void *a, const void *b) {
    MM *mm1 = (MM *)a;
    MM *mm2 = (MM *)b;
    return mm1->time - mm2->time;
}

int main() {
    int n;
    scanf("%d", &n);
    
    MM mm[100];
    for (int i = 0; i < n; i++) {
        scanf("%d %d %d", &mm[i].rmb, &mm[i].rp, &mm[i].time);
    }
    
    int m, r;
    scanf("%d %d", &m, &r);
    
    // 按照时间从小到大排序
    qsort(mm, n, sizeof(MM), cmp);
    
    int count = 0;
    int total_time = 0;
    
    // 遍历所有MM，选择可以泡的MM
    for (int i = 0; i < n; i++) {
        if (mm[i].rmb <= m && mm[i].rp <= r) {
            count++;
            total_time += mm[i].time;
            m -= mm[i].rmb;
            r -= mm[i].rp;
        }
    }
    
    printf("%d\n", total_time);
    return 0;
}