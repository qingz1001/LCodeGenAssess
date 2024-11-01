#include <stdio.h>

int countPartitions(int n, int k, int start) {
    if (k == 1) return 1;
    int count = 0;
    for (int i = start; i <= n / k; i++) {
        count += countPartitions(n - i, k - 1, i);
    }
    return count;
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    printf("%d\n", countPartitions(n, k, 1));
    return 0;
}