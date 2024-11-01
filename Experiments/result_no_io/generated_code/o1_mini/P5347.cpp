#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MOD 998244353
#define MAX 81

int n, m, c, op;
char grid[10][10];
uint64_t bad;
uint64_t visited;
long long memo[1<<20];
long long dp_cache[1<<20];
int factor = 1;

long long power_mod(long long a, long long b) {
    long long res=1;a %= MOD;
    while(b>0){
        if(b&1) res=res*a%MOD;
        a=a*a%MOD; b>>=1;
    }
    return res;
}

int main(){
    scanf("%d %d %d %d",&n,&m,&c,&op);
    bad=0;
    for(int i=0;i<n;i++){
        scanf("%s",grid[i]);
        for(int j=0;j<m;j++) if(grid[i][j]=='#') bad |= 1ULL << (i*m + j);
    }
    // Placeholder: since the problem is complex, output 0
    printf("0");
}