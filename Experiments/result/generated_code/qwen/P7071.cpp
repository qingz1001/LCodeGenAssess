#include <stdio.h>
#include <stdbool.h>

bool isPowerOfTwo(int num) {
    return (num > 0) && ((num & (num - 1)) == 0);
}

void findOptimalPartition(int n) {
    for (int i = n / 2; i >= 1; i--) {
        if (isPowerOfTwo(i)) {
            int remaining = n - i;
            if (remaining == 0 || isPowerOfTwo(remaining)) {
                printf("%d ", i);
                if (remaining != 0) {
                    printf("%d", remaining);
                }
                printf("\n");
                return;
            }
        }
    }
    printf("-1\n");
}

int main() {
    int n;
    scanf("%d", &n);
    findOptimalPartition(n);
    return 0;
}