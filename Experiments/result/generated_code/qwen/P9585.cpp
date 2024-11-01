#include <stdio.h>

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    
    int min_anger = 0;
    if (n <= m / 2) {
        min_anger = n - 1;
    } else {
        min_anger = m - n;
    }
    
    printf("%d\n", min_anger);
    
    return 0;
}