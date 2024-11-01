#include <stdio.h>
#include <string.h>

#define MAX_LEN 5001

int main() {
    char S[MAX_LEN];
    long long T;
    int x = 0, y = 0;
    int len;

    scanf("%s", S);
    scanf("%lld", &T);

    len = strlen(S);
    T %= len;  // 处理循环

    for (int i = 0; i < T; i++) {
        switch (S[i]) {
            case 'E':
                x++;
                break;
            case 'S':
                y--;
                break;
            case 'W':
                x--;
                break;
            case 'N':
                y++;
                break;
        }
    }

    // 处理完整循环
    long long full_cycles = T / len;
    for (int i = 0; i < len; i++) {
        switch (S[i]) {
            case 'E':
                x += full_cycles;
                break;
            case 'S':
                y -= full_cycles;
                break;
            case 'W':
                x -= full_cycles;
                break;
            case 'N':
                y += full_cycles;
                break;
        }
    }

    printf("%d %d\n", x, y);

    return 0;
}