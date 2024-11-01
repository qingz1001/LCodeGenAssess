#include <stdio.h>
#include <string.h>

#define MAX_N 20

int N;
int edges[MAX_N];
int memo[MAX_N][31][31];

int dfs(int pos, int left, int right) {
    if (left == 0 && right == 0) return 0;
    
    if (memo[pos][left][right] != -1) return memo[pos][left][right];
    
    int result = 0;
    
    // Try left edge
    if (left > 0) {
        int win = 0;
        for (int i = 0; i < left; i++) {
            if (!dfs((pos - 1 + N) % N, edges[(pos - 1 + N) % N], i)) {
                win = 1;
                break;
            }
        }
        result |= win;
    }
    
    // Try right edge
    if (right > 0 && !result) {
        int win = 0;
        for (int i = 0; i < right; i++) {
            if (!dfs((pos + 1) % N, i, edges[(pos + 1) % N])) {
                win = 1;
                break;
            }
        }
        result |= win;
    }
    
    memo[pos][left][right] = result;
    return result;
}

int main() {
    scanf("%d", &N);
    
    for (int i = 0; i < N; i++) {
        scanf("%d", &edges[i]);
    }
    
    memset(memo, -1, sizeof(memo));
    
    int result = dfs(0, edges[N-1], edges[0]);
    
    printf("%s\n", result ? "YES" : "NO");
    
    return 0;
}