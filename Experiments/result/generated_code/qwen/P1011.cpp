#include <stdio.h>

int main() {
    int a, n, m, x;
    scanf("%d %d %d %d", &a, &n, &m, &x);
    
    if (x == 1) {
        printf("%d\n", a);
        return 0;
    }
    
    int on[21], off[21];
    on[1] = a;
    for (int i = 2; i <= n - 1; i++) {
        on[i] = on[i - 1] + on[i - 2];
        off[i] = on[i - 1];
    }
    
    int current = a;
    for (int i = 2; i <= x; i++) {
        current += on[i] - off[i];
    }
    
    printf("%d\n", current);
    
    return 0;
}