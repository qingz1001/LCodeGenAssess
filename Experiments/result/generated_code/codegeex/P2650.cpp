#include <stdio.h>

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    
    struct {
        int start, end;
    } bullets[n];
    
    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        bullets[i].start = a + 1; // 弹幕开始时间，左开右闭
        bullets[i].end = a + b;   // 弹幕结束时间，左开右开
    }
    
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (bullets[j].start > x + y || bullets[j].end < x) {
                continue; // 弹幕不在查询区间内
            }
            count++;
        }
        
        printf("%d\n", count);
    }
    
    return 0;
}