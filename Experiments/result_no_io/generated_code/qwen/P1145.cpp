#include <stdio.h>

int main() {
    int k;
    scanf("%d", &k);
    printf("%d\n", (2 * k + 1) % (3 * k));
    return 0;
}