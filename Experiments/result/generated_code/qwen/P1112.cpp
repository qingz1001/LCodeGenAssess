#include <stdio.h>
#include <stdlib.h>

int isWaveNumber(int num, int base) {
    char str[100];
    sprintf(str, "%d", num);
    int len = strlen(str);
    if (len % 2 == 0) return 0;
    for (int i = 1; i < len; i += 2) {
        if (str[i] != str[i - 1]) return 0;
    }
    return 1;
}

int main() {
    int l, r, L, R, k;
    scanf("%d %d %d %d %d", &l, &r, &L, &R, &k);

    for (int i = L; i <= R; i++) {
        int waveCount = 0;
        for (int j = l; j <= r; j++) {
            if (isWaveNumber(i, j)) {
                waveCount++;
            }
        }
        if (waveCount == k) {
            printf("%d\n", i);
        }
    }

    return 0;
}