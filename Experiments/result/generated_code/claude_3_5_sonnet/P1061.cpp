#include <stdio.h>
#include <string.h>

#define MAX_W 26

void nextJamNumber(char *number, int s, int t, int w) {
    int i = w - 1;
    while (i >= 0) {
        if (number[i] - 'a' + 1 < t - (w - 1 - i)) {
            number[i]++;
            for (int j = i + 1; j < w; j++) {
                number[j] = number[j-1] + 1;
            }
            return;
        }
        i--;
    }
    number[0] = '\0';  // 没有下一个数字
}

int main() {
    int s, t, w;
    char number[MAX_W + 1];

    scanf("%d %d %d", &s, &t, &w);
    scanf("%s", number);

    for (int i = 0; i < 5; i++) {
        nextJamNumber(number, s, t, w);
        if (number[0] == '\0') break;
        printf("%s\n", number);
    }

    return 0;
}