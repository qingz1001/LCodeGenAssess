#include <stdio.h>

void countDigits(int M, int N, int *count) {
    for (int i = M; i <= N; i++) {
        int num = i;
        while (num > 0) {
            count[num % 10]++;
            num /= 10;
        }
    }
}

int main() {
    int M, N;
    scanf("%d %d", &M, &N);
    
    int count[10] = {0};
    countDigits(M, N, count);
    
    for (int i = 0; i < 10; i++) {
        printf("%d", count[i]);
        if (i < 9) {
            printf(" ");
        }
    }
    printf("\n");
    
    return 0;
}