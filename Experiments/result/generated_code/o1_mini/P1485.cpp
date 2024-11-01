#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef long long ll;

// Maximum n
#define MAXN 500005

ll n, k;
ll m[MAXN];

// Fenwick Trees
ll FT1_arr[MAXN];
ll FT2_arr[MAXN];
ll FT3_arr[MAXN];
ll *FT1 = FT1_arr;
ll *FT2 = FT2_arr;
ll *FT3 = FT3_arr;

// Update function for Fenwick Tree
void update(ll *FT, int idx, ll val) {
    while(idx <= n){
        FT[idx] += val;
        idx += idx & -idx;
    }
}

// Query prefix sum for Fenwick Tree
ll query(ll *FT, int idx){
    ll res = 0;
    while(idx >0){
        res += FT[idx];
        idx -= idx & -idx;
    }
    return res;
}

int main(){
    // Fast IO
    scanf("%lld %lld", &n, &k);
    for(int i=1;i<=n;i++) scanf("%lld", &m[i]);

    ll left =1, right =0;
    for(int i=1;i<=n;i++) if(m[i] > right) right = m[i];
    right += (ll)(1e10); // Upper limit
    ll answer = right;

    while(left <= right){
        ll mid = left + (right - left)/2;
        ll p = mid;
        // Calculate D = floor(sqrt(p))
        ll D = (ll)sqrt((double)p);
        // Reset Fenwick Trees
        memset(FT1, 0, sizeof(ll)*(n+1));
        memset(FT2, 0, sizeof(ll)*(n+1));
        memset(FT3, 0, sizeof(ll)*(n+1));
        ll shots =0;
        int over =0;
        for(int i=n;i>=1;i--){
            // j1 = max(1, i - D)
            int j1 = i - D;
            if(j1 <1) j1 =1;
            int j2 = i;
            // sum_x
            ll sum_x = query(FT1, j2) - query(FT1, j1 -1);
            // sum_xj
            ll sum_xj = query(FT2, j2) - query(FT2, j1 -1);
            // sum_xj2
            ll sum_xj2 = query(FT3, j2) - query(FT3, j1 -1);
            // current_damage = p * sum_x - i*i * sum_x + 2*i * sum_xj - sum_xj2
            ll current_damage = p * sum_x - ( (ll)i * (ll)i ) * sum_x + 2LL * i * sum_xj - sum_xj2;
            if(current_damage < m[i]){
                ll need = (m[i] - current_damage + p -1)/p;
                shots += need;
                if(shots >k){
                    over =1;
                    break;
                }
                // Assign 'need' shots at position i
                update(FT1, i, need);
                update(FT2, i, need * (ll)i);
                update(FT3, i, need * (ll)i * (ll)i);
            }
        }
        if(over){
            left = mid +1;
        }
        else{
            answer = mid;
            right = mid -1;
        }
    }
    printf("%lld\n", answer);
    return 0;
}