#include <stdio.h>
#include <stdbool.h>

#define MAX_N 12

int n, sum;
int arr[MAX_N];
bool used[MAX_N + 1];

bool dfs(int pos, int current_sum) {
    if (pos == n) {
        return current_sum == sum;
    }
    
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            used[i] = true;
            arr[pos] = i;
            
            int new_sum = current_sum;
            for (int j = pos; j >= 0; j--) {
                new_sum += arr[j];
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
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
    
    return 0;
}