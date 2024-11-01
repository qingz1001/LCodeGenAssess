#include <stdio.h>

int n, max_i, count;
int sectors[8];
int used[65];

void fillSectors(int index, int sum) {
    if (index == n) {
        if (sum >= max_i) {
            if (sum > max_i) {
                max_i = sum;
                count = 0;
            }
            count++;
            for (int i = 0; i < n; i++) {
                printf("%d ", sectors[i]);
            }
            printf("\n");
        }
        return;
    }
    for (int i = 1; i <= 64; i++) {
        if (!used[i]) {
            used[i] = 1;
            sectors[index] = i;
            fillSectors(index + 1, sum + i);
            used[i] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);
    fillSectors(0, 0);
    printf("%d\n", max_i);
    return 0;
}