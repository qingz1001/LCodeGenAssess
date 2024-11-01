#include <stdio.h>
#include <stdbool.h>

int main() {
    int n;
    scanf("%d", &n);

    bool song_valid[10000001] = {false}; // 用于标记歌曲是否已累计
    long long total_time = 0; // 听歌时间总和

    for (int i = 0; i < n; i++) {
        int x, t;
        scanf("%d %d", &x, &t);

        if (t > 1 && !song_valid[x]) { // 如果记录有效且歌曲未累计
            total_time += t; // 累加听歌时间
            song_valid[x] = true; // 标记该歌曲已累计
        }
    }

    printf("%lld\n", total_time); // 输出听歌时间总和
    return 0;
}