#include <stdio.h>

int main() {
    int k, day = 1, coins = 0;
    while (day <= k) {
        int n = day;
        for (int i = 0; i < n && day <= k; ++i) {
            coins += n;
            ++day;
        }
    }
    printf("%d\n", coins);
    return 0;
}