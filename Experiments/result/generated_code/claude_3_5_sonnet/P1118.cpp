#include <stdio.h>
#include <stdbool.h>

#define MAXN 13

int n, sum, a[MAXN];
bool used[MAXN];

bool dfs(int pos, int cur_sum) {
    if (pos == n) {
        return cur_sum == sum;
    }
    
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            used[i] = true;
            a[pos] = i;
            
            int new_sum = cur_sum;
            for (int j = pos; j >= 0; j--) {
                new_sum += a[j];
                if (dfs(pos + 1, new_sum)) {
                    return true;
                }
            }
            
            used[i] = false;
        }
    }
    
    return false;
}

int main() {
    scanf("%d %d", &n, &sum);
    
    if (dfs(0, 0)) {
        for (int i = 0; i < n; i++) {
            printf("%d ", a[i]);
        }
        printf("\n");
    }
    
    return 0;
}