#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int m = 0;
    while (1 << (m + 2) < n) {
        m += 2;
    }
    printf("%d\n", m);
    return 0;
}