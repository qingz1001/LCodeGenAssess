#include <stdio.h>

int sramoc(int k, int m) {
    for (int i = 0; ; ++i) {
        int num = 0;
        for (int j = 0; j < k; ++j) {
            num = num * 10 + i % k;
            i /= k;
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