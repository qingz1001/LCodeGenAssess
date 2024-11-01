#include <stdio.h>
#include <string.h>

#define MOD 1000000007
#define MAXM 6
#define MAXK 5

typedef long long ll;

ll n, m, k;
ll dp[2][1 << MAXM];
ll C[MAXM][MAXM];

void init_C() {
    for (int i = 0; i < MAXM; i++) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; j++) {
            C[i][j] = (C[i-1][j-1] + C[i-1][j]) % MOD;
        }
    }
}

int count_ones(int x) {
    int cnt = 0;
    while (x) {
        cnt += x & 1;
        x >>= 1;
    }
    return cnt;
}

ll quick_pow(ll base, ll exp) {
    ll res = 1;
    while (exp) {
        if (exp & 1) res = res * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

ll solve() {
    init_C();
    
    int now = 0, pre = 1;
    memset(dp, 0, sizeof(dp));
    dp[now][0] = 1;
    
    for (ll i = 1; i <= n; i++) {
        now ^= 1, pre ^= 1;
        memset(dp[now], 0, sizeof(dp[now]));
        
        for (int mask = 0; mask < (1 << m); mask++) {
            if (count_ones(mask) > k) continue;
            
            for (int last = 0; last < 2; last++) {
                int new_mask = ((mask << 1) | last) & ((1 << m) - 1);
                if (count_ones(new_mask) <= k) {
                    dp[now][new_mask] = (dp[now][new_mask] + dp[pre][mask]) % MOD;
                }
            }
        }
    }
    
    ll ans = 0;
    for (int mask = 0; mask < (1 << m); mask++) {
        ans = (ans + dp[now][mask]) % MOD;
    }
    return ans;
}

int main() {
    scanf("%lld%lld%lld", &n, &m, &k);
    
    if (n <= 60) {
        printf("%lld\n", solve());
    } else {
        ll period = 0;
        ll state[2][1 << MAXM];
        memset(state, 0, sizeof(state));
        
        int now = 0, pre = 1;
        state[now][0] = 1;
        
        for (ll i = 1; i <= n; i++) {
            now ^= 1, pre ^= 1;
            memset(state[now], 0, sizeof(state[now]));
            
            for (int mask = 0; mask < (1 << m); mask++) {
                if (count_ones(mask) > k) continue;
                
                for (int last = 0; last < 2; last++) {
                    int new_mask = ((mask << 1) | last) & ((1 << m) - 1);
                    if (count_ones(new_mask) <= k) {
                        state[now][new_mask] = (state[now][new_mask] + state[pre][mask]) % MOD;
                    }
                }
            }
            
            int found = 1;
            for (int mask = 0; mask < (1 << m); mask++) {
                if (state[now][mask] != state[pre][mask]) {
                    found = 0;
                    break;
                }
            }
            
            if (found) {
                period = i - 1;
                break;
            }
        }
        
        ll ans = 0;
        for (int mask = 0; mask < (1 << m); mask++) {
            ans = (ans + state[now][mask]) % MOD;
        }
        
        ll times = n / period;
        ll remain = n % period;
        
        ll final_ans = quick_pow(ans, times);
        if (remain) {
            ll remain_ans = solve();
            final_ans = final_ans * remain_ans % MOD;
        }
        
        printf("%lld\n", final_ans);
    }
    
    return 0;
}