#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 65
#define MAXLEN 50

int n, sticks[MAXN], sum = 0, maxlen = 0;
int used[MAXN];

int cmp(const void *a, const void *b) {
    return *(int*)b - *(int*)a;
}

int dfs(int cur, int left, int target, int start) {
    if (cur * target == sum) return 1;
    if (left == 0) {
        return dfs(cur + 1, target, target, 0);
    }
    
    int i;
    for (i = start; i < n; i++) {
        if (used[i] || left < sticks[i]) continue;
        if (i > 0 && !used[i-1] && sticks[i] == sticks[i-1]) continue;
        
        used[i] = 1;
        if (dfs(cur, left - sticks[i], target, i + 1)) return 1;
        used[i] = 0;
        
        if (left == target || left == sticks[i]) return 0;
    }
    return 0;
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &sticks[i]);
        sum += sticks[i];
        if (sticks[i] > maxlen) maxlen = sticks[i];
    }
    
    qsort(sticks, n, sizeof(int), cmp);
    
    for (int len = maxlen; len <= sum; len++) {
        if (sum % len == 0) {
            memset(used, 0, sizeof(used));
            if (dfs(0, len, len, 0)) {
                printf("%d\n", len);
                return 0;
            }
        }
    }
    
    return 0;
}