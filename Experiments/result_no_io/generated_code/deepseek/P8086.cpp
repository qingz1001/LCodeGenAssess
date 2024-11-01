#include <stdio.h>
#include <stdbool.h>

#define MAXN 10000005

int main() {
    int n;
    scanf("%d", &n);
    
    int x, t;
    long long total_time = 0;
    bool visited[MAXN] = {false};
    
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x, &t);
        if (t > 1 && !visited[x]) {
            total_time += t;
            visited[x] = true;
        }
    }
    
    printf("%lld\n", total_time);
    
    return 0;
}