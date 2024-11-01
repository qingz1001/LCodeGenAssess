#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 65
#define MAX_LEN 50

int n, sticks[MAX_N], sum = 0, max_len = 0;
int used[MAX_N];

int cmp(const void *a, const void *b) {
    return *(int*)b - *(int*)a;
}

int dfs(int target, int cur_sum, int start, int cnt) {
    if (cnt * target == sum) return 1;
    if (cur_sum == target) return dfs(target, 0, 0, cnt + 1);
    
    int i;
    for (i = start; i < n; i++) {
        if (used[i] || cur_sum + sticks[i] > target) continue;
        
        used[i] = 1;
        if (dfs(target, cur_sum + sticks[i], i + 1, cnt)) return 1;
        used[i] = 0;
        
        if (cur_sum == 0) return 0;
        while (i + 1 < n && sticks[i] == sticks[i + 1]) i++;
    }
    return 0;
}

int main() {
    scanf("%d", &n);
    
    int i;
    for (i = 0; i < n; i++) {
        scanf("%d", &sticks[i]);
        sum += sticks[i];
        if (sticks[i] > max_len) max_len = sticks[i];
    }
    
    qsort(sticks, n, sizeof(int), cmp);
    
    for (i = max_len; i <= sum; i++) {
        if (sum % i == 0) {
            memset(used, 0, sizeof(used));
            if (dfs(i, 0, 0, 0)) {
                printf("%d\n", i);
                return 0;
            }
        }
    }
    
    return 0;
}