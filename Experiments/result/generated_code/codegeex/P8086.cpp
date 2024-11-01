#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    int songs[10000001] = {0}; // 用于记录每首歌是否已经被计算过
    long long total_time = 0;  // 总听歌时间
    
    for (int i = 0; i < n; i++) {
        int x, t;
        scanf("%d %d", &x, &t);
        
        if (t > 1 && songs[x] == 0) { // 如果记录有效且该歌曲尚未被计算过
            total_time += t;
            songs[x] = 1; // 标记该歌曲已被计算
        }
    }
    
    printf("%lld\n", total_time);
    return 0;
}