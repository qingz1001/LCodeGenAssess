#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;
const int MAX = 1000005;
const int MOD = 19930726;

// Comparison function for qsort
int cmp(const void *a, const void *b){
    ll va = *(ll*)a;
    ll vb = *(ll*)b;
    if(va < vb) return -1;
    if(va > vb) return 1;
    return 0;
}

// Fast exponentiation
ll power_mod(ll a, ll b, int mod){
    ll res = 1;
    a %= mod;
    while(b > 0){
        if(b & 1){
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

int main(){
    ll n;
    ll K;
    scanf("%lld %lld", &n, &K);
    char *s = (char*)malloc((n+2)*sizeof(char));
    scanf("%s", s);
    
    // Manacher's algorithm for odd-length palindromes
    ll *d1 = (ll*)malloc((n+2)*sizeof(ll));
    ll l = 0, r = -1;
    for(ll i=0;i<n;i++){
        if(i > r){
            d1[i] =1;
        }
        else{
            d1[i] = (r - i +1) < d1[l + r - i] ? (r - i +1) : d1[l + r - i];
        }
        while(i - d1[i] >=0 && i + d1[i] <n && s[i - d1[i]] == s[i + d1[i]]){
            d1[i]++;
        }
        if(i + d1[i] -1 > r){
            l = i - d1[i] +1;
            r = i + d1[i] -1;
        }
    }
    
    // Sort d1
    qsort(d1, n, sizeof(ll), cmp);
    
    // Count frequencies
    ll max_l = n %2 ? n : n-1;
    ll *count = (ll*)calloc((n+2), sizeof(ll));
    for(ll l_val=1;l_val<=max_l;l_val+=2){
        ll m = (l_val +1)/2;
        // Binary search for first d1 >= m
        ll left =0, right =n;
        while(left < right){
            ll mid = left + (right - left)/2;
            if(d1[mid] >= m){
                right = mid;
            }
            else{
                left = mid +1;
            }
        }
        count[l_val] = n - left;
    }
    
    // Iterate from max_l to 1
    ll product =1;
    for(ll l_val=max_l;l_val>=1;l_val-=2){
        if(K ==0) break;
        if(count[l_val] ==0) continue;
        ll take = count[l_val] < K ? count[l_val] : K;
        product = (product * power_mod(l_val, take, MOD)) % MOD;
        K -= take;
    }
    
    if(K >0){
        printf("-1\n");
    }
    else{
        printf("%lld\n", product);
    }
    
    free(s);
    free(d1);
    free(count);
    return 0;
}