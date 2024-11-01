#include <stdio.h>

void findNumbers(int N, int M) {
    int num = 3;
    int remaining = N - M;
    
    for (int i = 0; i < M; i++) {
        if (remaining > M - i - 1) {
            printf("%d ", num);
            remaining -= (num - 1);
        } else if (remaining > 0) {
            printf("%d ", 2);
            remaining--;
        } else {
            printf("1 ");
        }
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    findNumbers(N, M);
    return 0;
}