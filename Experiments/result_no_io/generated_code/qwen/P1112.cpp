#include <stdio.h>
#include <stdbool.h>

bool isWaveNumber(int num) {
    if (num < 10) return true;
    int prev = num % 10;
    num /= 10;
    while (num > 0) {
        int current = num % 10;
        if (current == prev || (prev != -1 && current == prev)) return false;
        prev = current;
        num /= 10;
    }
    return true;
}

bool isDoubleWaveNumber(int num, int base) {
    char str[20];
    sprintf(str, "%d", num);
    for (int i = 0; i < strlen(str); i++) {
        if ((i + 1) % 2 == 0 && str[i] == str[i - 1]) return false;
    }
    return true;
}

void findKWaveNumbers(int l, int r, int L, int R, int k) {
    for (int i = L; i <= R; i++) {
        bool valid = true;
        for (int j = l; j <= r; j++) {
            if (!isDoubleWaveNumber(i, j)) {
                valid = false;
                break;
            }
        }
        if (valid) printf("%d\n", i);
    }
}

int main() {
    int l, r, L, R, k;
    scanf("%d %d %d %d %d", &l, &r, &L, &R, &k);
    if (k == 2) findKWaveNumbers(l, r, L, R, k);
    else printf("No such number exists.\n");
    return 0;
}