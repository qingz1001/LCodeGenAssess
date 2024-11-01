#include <stdio.h>

int count = 0;

void partition(int n, int k, int min, int current_sum, int current_k) {
    if (current_k == k) {
        if (current_sum == n) {
            count++;
        }
        return;
    }
    
    for (int i = min; i <= n - current_sum - (k - current_k - 1); i++) {
        partition(n, k, i, current_sum + i, current_k + 1);
    }
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    partition(n, k, 1, 0, 0);
    
    printf("%d\n", count);
    
    return 0;
}