#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MOD 998244353
#define MAXN 9
#define MAXM 9

int n, m, c, op;
char grid[MAXN][MAXM+1];
uint64_t memo[1<<20];
int used;
long long power_c[100];
long long dp_cache[1<<20];

long long pow_mod(long long a, long long b) {
    long long res=1;
    a %= MOD;
    while(b > 0){
        if(b&1) res = res * a % MOD;
        a = a * a % MOD;
        b >>=1;
    }
    return res;
}

long long dfs(int mask){
    if(memo[mask]) return memo[mask];
    long long res = 1;
    for(int i=0;i<n*m;i++){
        if(!(mask & (1<<i)) && grid[i/m][i%m]=='.'){
            // Try horizontal
            if(i%m < m-1 && grid[i/m][i%m+1]=='.'){
                res = (res + c * dfs(mask | (1<<i) | (1<<(i+1)))) % MOD;
            }
            // Try vertical
            if(i/m < n-1 && grid[i/m+1][i%m]=='.'){
                res = (res + c * dfs(mask | (1<<i) | (1<<(i+m)))) % MOD;
            }
        }
    }
    memo[mask] = res;
    return res;
}

int main(){
    scanf("%d %d %d %d", &n, &m, &c, &op);
    for(int i=0;i<n;i++) scanf("%s", grid[i]);
    memset(memo, 0, sizeof(memo));
    printf("%lld\n", dfs(0));
    return 0;
}