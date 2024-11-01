#include <stdio.h>

int count = 0;

void partition(int n, int k, int min, int level) {
    if (k == 1 && n >= min) {
        count++;
        return;
    }
    
    for (int i = min; i <= n / k; i++) {
        partition(n - i, k - 1, i, level + 1);
    }
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    partition(n, k, 1, 1);
    
    printf("%d\n", count);
    
    return 0;
}