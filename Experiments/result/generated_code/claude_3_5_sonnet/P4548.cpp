#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_N 100001
#define MAX_T 51
#define MAX_M 100001
#define MOD 10000

typedef long long ll;

int n, t;
int m[MAX_T];
int name[MAX_T][MAX_M];
int fail[MAX_M];
ll dp[MAX_N];

void get_fail(int* pattern, int m) {
    fail[0] = fail[1] = 0;
    for (int i = 1; i < m; i++) {
        int j = fail[i];
        while (j && pattern[i] != pattern[j])
            j = fail[j];
        fail[i + 1] = pattern[i] == pattern[j] ? j + 1 : 0;
    }
}

ll solve(int* pattern, int m) {
    get_fail(pattern, m);
    
    memset(dp, 0, sizeof(dp));
    dp[0] = n;
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int k = i;
            while (k && pattern[k] != j + 1)
                k = fail[k];
            if (pattern[k] == j + 1) k++;
            if (k < m) (dp[k] += dp[i]) %= MOD;
        }
    }
    
    ll sum = 0;
    for (int i = 0; i < m; i++)
        (sum += dp[i]) %= MOD;
    
    return sum;
}

int main() {
    scanf("%d%d", &n, &t);
    
    for (int i = 0; i < t; i++) {
        scanf("%d", &m[i]);
        for (int j = 0; j < m[i]; j++)
            scanf("%d", &name[i][j]);
    }
    
    for (int i = 0; i < t; i++)
        printf("%04lld\n", solve(name[i], m[i]));
    
    return 0;
}