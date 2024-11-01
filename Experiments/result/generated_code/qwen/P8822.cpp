#include <stdio.h>

int main() {
    int n, v, m, a;
    scanf("%d %d %d %d", &n, &v, &m, &a);
    
    int total = 0;
    for (int i = 1; i <= n; ++i) {
        total += v + (i - 1) / m * a;
    }
    
    printf("%d\n", total);
    return 0;
}