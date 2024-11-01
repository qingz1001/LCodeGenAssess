#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 200005
#define MAX_M 1000005

typedef long long ll;

struct Monster {
    ll normal_attack;
    ll magic_attack;
    int new_monsters_count;
    int new_monsters[MAX_M];
};

struct Monster monsters[MAX_N];
ll dp[MAX_N];
int n;

ll min(ll a, ll b) {
    return a < b ? a : b;
}

ll dfs(int id) {
    if (dp[id] != -1) return dp[id];
    
    ll normal_cost = monsters[id].normal_attack;
    for (int i = 0; i < monsters[id].new_monsters_count; i++) {
        normal_cost += dfs(monsters[id].new_monsters[i]);
    }
    
    ll magic_cost = monsters[id].magic_attack;
    
    dp[id] = min(normal_cost, magic_cost);
    return dp[id];
}

int main() {
    scanf("%d", &n);
    
    for (int i = 1; i <= n; i++) {
        scanf("%lld %lld %d", &monsters[i].normal_attack, &monsters[i].magic_attack, &monsters[i].new_monsters_count);
        for (int j = 0; j < monsters[i].new_monsters_count; j++) {
            scanf("%d", &monsters[i].new_monsters[j]);
        }
    }
    
    memset(dp, -1, sizeof(dp));
    
    ll result = dfs(1);
    printf("%lld\n", result);
    
    return 0;
}