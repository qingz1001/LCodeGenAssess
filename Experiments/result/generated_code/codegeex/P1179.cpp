#include <stdio.h>

int main() {
    int L, R, count = 0;
    scanf("%d %d", &L, &R);

    for (int i = L; i <= R; i++) {
        int num = i;
        while (num > 0) {
            if (num % 10 == 2) {
                count++;
            }
            num /= 10;
        }
    }

    printf("%d\n", count);
    return 0;
}