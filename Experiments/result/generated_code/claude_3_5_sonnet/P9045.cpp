#include <stdio.h>
#include <stdlib.h>

#define MAX_N 500000

int n, k;
int a[MAX_N];
int visited[MAX_N + 1];

int main() {
    scanf("%d %d", &n, &k);
    
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    int cost = 0;
    int unique = 0;

    for (int i = 0; i < n; i++) {
        if (unique == k) break;
        
        if (!visited[a[i]]) {
            visited[a[i]] = 1;
            unique++;
            cost += i - (unique - 1);
        }
    }

    if (unique < k) {
        printf("-1\n");
    } else {
        printf("%d\n", cost);
    }

    return 0;
}