#include <stdio.h>

int solve(int n) {
    if (n == 1) return 0;
    int count = 0;
    while (n > 1) {
        if (n % 2 == 0) {
            n /= 2;
        } else {
            n = n / 2 + 1;
        }
        count++;
    }
    return count;
}

int main() {
    int t, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        printf("%d\n", solve(n));
    }
    return 0;
}