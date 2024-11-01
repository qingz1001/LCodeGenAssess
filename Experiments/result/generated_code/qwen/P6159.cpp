#include <stdio.h>

int main() {
    int n, p, k;
    scanf("%d %d %d", &n, &p, &k);
    t = (p + k * 2) % n;
    printf("%d\n", t);
    return 0;
}