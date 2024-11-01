#include <stdio.h>

int main() {
    int k;
    scanf("%d", &k);
    int m = 1;
    while (1) {
        int count = 0;
        int alive = 2 * k;
        for (int i = 1; i <= k; i++) {
            if (alive <= 0) break;
            count++;
            if (count == m) {
                count = 0;
                alive--;
                if (alive <= 0) break;
            }
        }
        if (alive == 0) {
            printf("%d\n", m);
            break;
        }
        m++;
    }
    return 0;
}