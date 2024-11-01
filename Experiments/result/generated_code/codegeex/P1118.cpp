#include <stdio.h>
#include <stdbool.h>

int n, sum;
bool used[15];

bool dfs(int depth, int current_sum, int last_number) {
    if (depth == 0) {
        return current_sum == sum;
    }
    
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            int new_sum = current_sum + last_number + i;
            if (new_sum <= sum) {
                used[i] = true;
                if (dfs(depth - 1, new_sum, i)) {
                    printf("%d ", i);
                    return true;
                }
                used[i] = false;
            }
        }
    }
    
    return false;
}

int main() {
    scanf("%d %d", &n, &sum);
    
    // Initialize the used array
    for (int i = 1; i <= n; i++) {
        used[i] = false;
    }
    
    // Start the DFS
    if (dfs(n, 0, 0)) {
        printf("\n");
    } else {
        // If no solution found, output nothing
    }
    
    return 0;
}