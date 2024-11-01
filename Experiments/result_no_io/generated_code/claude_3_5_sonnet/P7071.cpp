#include <stdio.h>

#define MAX_POWERS 30

int powers[MAX_POWERS];
int result[MAX_POWERS];
int result_size = 0;

int is_excellent_split(int n) {
    if (n <= 0) return 0;
    
    for (int i = MAX_POWERS - 1; i >= 1; i--) {
        if (n >= powers[i]) {
            n -= powers[i];
            result[result_size++] = powers[i];
        }
    }
    
    return n == 0;
}

int main() {
    int n;
    scanf("%d", &n);
    
    // 预计算2的幂
    powers[0] = 1;
    for (int i = 1; i < MAX_POWERS; i++) {
        powers[i] = powers[i-1] * 2;
    }
    
    if (is_excellent_split(n)) {
        for (int i = 0; i < result_size; i++) {
            printf("%d", result[i]);
            if (i < result_size - 1) {
                printf(" ");
            }
        }
        printf("\n");
    } else {
        printf("-1\n");
    }
    
    return 0;
}