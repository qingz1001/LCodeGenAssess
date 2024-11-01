#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    
    bool platforms[1001];
    for (int i = 0; i <= n; i++) {
        platforms[i] = false;
    }
    
    for (int i = 0; i < k; i++) {
        int a;
        scanf("%d", &a);
        platforms[a] = true;
    }
    
    int time = 0;
    while (n > 0) {
        if (platforms[n]) {
            m++;
        }
        n -= m;
        time++;
    }
    
    printf("%d\n", time);
    
    return 0;
}