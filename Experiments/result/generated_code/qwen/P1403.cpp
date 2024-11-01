#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        int count = 0;
        for (int j = 1; j * j <= i; ++j) {
            if (i % j == 0) {
                if (j * j == i) {
                    count += 1;
                } else {
                    count += 2;
                }
            }
        }
        sum += count;
    }
    
    printf("%lld\n", sum);
    return 0;
}