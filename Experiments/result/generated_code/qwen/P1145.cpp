#include <stdio.h>

int josephus(int k) {
    int m = 1;
    while ((m - 1) % (k * 2) != k - 1) {
        m++;
    }
    return m;
}

int main() {
    int k;
    scanf("%d", &k);
    printf("%d\n", josephus(k));
    return 0;
}