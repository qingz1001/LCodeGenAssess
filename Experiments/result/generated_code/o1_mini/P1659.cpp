#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef long long ll;

const int MAX = 1000001;
const ll MOD = 19930726;

// Fast exponentiation
ll pow_mod_func(ll base, ll exp, ll mod_val){
    ll res = 1;
    base %= mod_val;
    while(exp > 0){
        if(exp & 1){
            res = (res * base) % mod_val;
        }
        base = (base * base) % mod_val;
        exp >>=1;
    }
    return res;
}

int main(){
    ll n;
    unsigned long long K;
    scanf("%lld %llu", &n, &K);
    char *s = (char*)malloc((n+1)*sizeof(char));
    scanf("%s", s);
    
    // Manacher's algorithm for odd-length palindromes
    ll *p = (ll*)calloc(n, sizeof(ll));
    ll c =0, r= -1;
    for(ll i=0;i<n;i++){
        if(i < r){
            ll j = 2*c -i;
            if(j >=0){
                if(p[j] < r -i){
                    p[i] = p[j];
                }
                else{
                    p[i] = r -i;
                }
            }
            else{
                p[i] =0;
            }
        }
        else{
            p[i]=0;
        }
        // Expand around center i
        while(i - p[i] -1 >=0 && i + p[i] +1 <n && s[i - p[i] -1] == s[i + p[i] +1]){
            p[i]++;
        }
        if(i + p[i] > r){
            c =i;
            r = i + p[i];
        }
    }
    
    // Counting sort for r_i in descending order
    ll *sorted_r = (ll*)malloc(n * sizeof(ll));
    ll *freq = (ll*)calloc(n+1, sizeof(ll));
    for(ll i=0;i<n;i++) freq[p[i]]++;
    ll idx_sorted=0;
    for(ll r_val =n; r_val>=0; r_val--){
        while(freq[r_val] >0){
            sorted_r[idx_sorted++] = r_val;
            freq[r_val]--;
        }
    }
    free(freq);
    
    // Step 6: Compute cnt[L]
    ll *cnt_L = (ll*)calloc(n+1, sizeof(ll));
    ll idx =0;
    for(ll L = n - (n%2 ==0 ? 1 :0); L >=1; L-=2){
        ll t = (L-1)/2;
        while(idx <n && sorted_r[idx] >= t){
            idx++;
        }
        cnt_L[L] = idx;
    }
    
    // Step 7: Iterate and compute product
    ll res =1;
    for(ll L = n - (n%2 ==0 ? 1 :0); L >=1; L-=2){
        if(K ==0) break;
        ll c_L = cnt_L[L];
        if(K >= c_L){
            res = (res * pow_mod_func(L, c_L, MOD)) % MOD;
            K -=c_L;
        }
        else{
            res = (res * pow_mod_func(L, K, MOD)) % MOD;
            K =0;
            break;
        }
    }
    
    if(K >0){
        printf("-1\n");
    }
    else{
        printf("%lld\n", res);
    }
    
    // Free allocated memory
    free(s);
    free(p);
    free(sorted_r);
    free(cnt_L);
    return 0;
}