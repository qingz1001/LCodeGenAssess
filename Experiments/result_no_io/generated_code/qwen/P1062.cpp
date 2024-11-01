#include <stdio.h>

int main() {
    int k, N;
    scanf("%d %d", &k, &N);
    
    int result = 0;
    for (int i = 0; i <= N; i++) {
        int sum = 0;
        int num = i;
        while (num > 0) {
            sum += (num % 2) * (k << (i - 1));
            num /= 2;
        }
        if (sum != 0) {
            result++;
        }
        if (result == N) {
            printf("%d\n", sum);
            break;
        }
    }
    
    return 0;
}