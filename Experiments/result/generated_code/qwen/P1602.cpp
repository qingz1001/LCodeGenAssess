#include <stdio.h>

int sramoc(int k, int m) {
    for (int i = 1; ; i++) {
        int num = 0;
        int multiplier = 1;
        for (int j = 0; j < k; j++) {
            num += (i % 10) * multiplier;
            multiplier *= 10;
            i /= 10;
        }
        if (num % m == 0) {
            return num;
        }
    }
}

int main() {
    int k, m;
    scanf("%d %d", &k, &m);
    printf("%d\n", sramoc(k, m));
    return 0;
}