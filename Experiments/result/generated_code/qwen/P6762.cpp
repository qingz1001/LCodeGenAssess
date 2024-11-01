#include <stdio.h>
#include <stdlib.h>

#define MAX_H 6

int main() {
    int H;
    scanf("%d", &H);

    char front[MAX_H][MAX_H + 1];
    char back[MAX_H][MAX_H + 1];

    for (int i = 0; i < H; ++i) {
        scanf("%s", front[i]);
    }

    for (int i = 0; i < H; ++i) {
        scanf("%s", back[i]);
    }

    long long count = 0;

    for (int a = 0; a <= 6 - H; ++a) {
        for (int b = 0; b <= 6 - H; ++b) {
            int valid = 1;
            for (int i = 0; i < H && valid; ++i) {
                for (int j = 0; j < H && valid; ++j) {
                    if (front[i][j] == 'W' || front[i][j] == 'G') {
                        if (back[H - 1 - i][H - 1 - j] != front[i][j]) {
                            valid = 0;
                        }
                    }
                }
            }
            if (valid) {
                count++;
            }
        }
    }

    printf("%lld\n", count);

    return 0;
}