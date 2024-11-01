#include <stdio.h>

int main() {
    int n, x;
    scanf("%d %d", &n, &x);
    
    int count = 0;
    for (int i = 1; i <= n; i++) {
        int num = i;
        while (num > 0) {
            if (num % 10 == x) {
                count++;
            }
            num /= 10;
        }
    }
    
    printf("%d\n", count);
    return 0;
}