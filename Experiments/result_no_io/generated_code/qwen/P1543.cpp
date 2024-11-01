#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000001

int main() {
    int n, a[MAXN];
    scanf("%d", &n);
    
    for (int i = 1; i <= n; ++i) {
        scanf("%d", &a[i]);
    }
    
    int visited[MAXN] = {0};
    int count = 0;
    
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            int j = i;
            while (!visited[j]) {
                visited[j] = 1;
                j = a[j];
            }
            count++;
        }
    }
    
    printf("%d\n", n - count);
    
    return 0;
}