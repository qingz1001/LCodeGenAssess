#include <stdio.h>
#include <string.h>

int main() {
    char S[5001];
    int T;
    scanf("%s", S);
    scanf("%d", &T);

    int len = strlen(S);
    int x = 0, y = 0;

    // 计算一个周期内的位移
    for (int i = 0; i < len; i++) {
        switch (S[i]) {
            case 'E': x++; break;
            case 'S': y--; break;
            case 'W': x--; break;
            case 'N': y++; break;
        }
    }

    // 计算完整周期的次数
    int full_cycles = T / len;
    x *= full_cycles;
    y *= full_cycles;

    // 计算剩余时间的位移
    int remaining_seconds = T % len;
    for (int i = 0; i < remaining_seconds; i++) {
        switch (S[i]) {
            case 'E': x++; break;
            case 'S': y--; break;
            case 'W': x--; break;
            case 'N': y++; break;
        }
    }

    printf("%d %d\n", x, y);
    return 0;
}