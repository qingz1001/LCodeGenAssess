#include <stdio.h>

#define MAX_N 10000
#define MAX_M 100

int n, m;
int w[MAX_N];
int taps[MAX_M];

int main() {
    scanf("%d %d", &n, &m);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &w[i]);
    }
    
    int time = 0;
    int finished = 0;
    
    // 初始化前m个同学开始接水
    for (int i = 0; i < m && i < n; i++) {
        taps[i] = i;
    }
    
    while (finished < n) {
        int min_time = 10001;  // 设置一个较大的初始值
        
        // 找出当前接水的同学中，最先完成的时间
        for (int i = 0; i < m && taps[i] < n; i++) {
            if (w[taps[i]] < min_time) {
                min_time = w[taps[i]];
            }
        }
        
        // 更新时间和水量
        time += min_time;
        for (int i = 0; i < m && taps[i] < n; i++) {
            w[taps[i]] -= min_time;
            if (w[taps[i]] == 0) {
                finished++;
                taps[i] = n + finished - 1;  // 安排下一个同学
            }
        }
    }
    
    printf("%d\n", time);
    
    return 0;
}