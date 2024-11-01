#include <stdio.h>
#include <string.h>

#define MAX_N 20

int N;
int edge[MAX_N];
int memo[MAX_N][31][31];

int dfs(int pos, int left, int right) {
    if (left == 0 && right == 0) return 0;
    if (memo[pos][left][right] != -1) return memo[pos][left][right];

    int result = 0;
    
    if (left > 0) {
        for (int i = 0; i < left; i++) {
            if (dfs((pos - 1 + N) % N, edge[(pos - 1 + N) % N], i) == 0) {
                result = 1;
                break;
            }
        }
    }
    
    if (result == 0 && right > 0) {
        for (int i = 0; i < right; i++) {
            if (dfs((pos + 1) % N, i, edge[(pos + 1) % N]) == 0) {
                result = 1;
                break;
            }
        }
    }
    
    memo[pos][left][right] = result;
    return result;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &edge[i]);
    }
    
    memset(memo, -1, sizeof(memo));
    
    int result = dfs(0, edge[N-1], edge[0]);
    
    if (result) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    
    return 0;
}