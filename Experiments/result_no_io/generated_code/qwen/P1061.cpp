#include <stdio.h>
#include <string.h>

#define MAX_W 26

void next_jam_number(char *jam_num, int s, int t, int w) {
    for (int i = w - 1; i >= 0; --i) {
        if (jam_num[i] == 'z' || jam_num[i] + 1 > 'a' + t - 1) {
            continue;
        }
        jam_num[i]++;
        for (int j = i + 1; j < w; ++j) {
            jam_num[j] = jam_num[j - 1] + 1;
        }
        return;
    }
}

int main() {
    int s, t, w;
    char jam_num[MAX_W];
    scanf("%d %d %d", &s, &t, &w);
    scanf("%s", jam_num);

    for (int i = 0; i < 5; ++i) {
        next_jam_number(jam_num, s, t, w);
        printf("%s\n", jam_num);
    }

    return 0;
}