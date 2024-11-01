#include <stdio.h>
#include <stdbool.h>

#define MAXN 10000000

int main() {
    int n;
    scanf("%d", &n);
    
    int x, t;
    long long total_time = 0;
    bool seen[MAXN + 1] = {false};
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x, &t);
        if (t > 1 && !seen[x]) {
            total_time += t;
            seen[x] = true;
        }
    }
    
    printf("%lld\n", total_time);
    
    return 0;
}