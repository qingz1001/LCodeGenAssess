#include <stdio.h>
#include <stdbool.h>

typedef long long ll;

// Function to perform modular multiplication
ll mulmod(ll a, ll b, ll mod){
    ll res = 0;
    a %= mod;
    while(b > 0){
        if(b & 1){
            res = (res + a) % mod;
        }
        a = (a << 1) % mod;
        b >>= 1;
    }
    return res;
}

// Function to perform modular exponentiation
ll power(ll a, ll d, ll mod){
    ll res = 1;
    a %= mod;
    while(d > 0){
        if(d & 1){
            res = mulmod(res, a, mod);
        }
        a = mulmod(a, a, mod);
        d >>= 1;
    }
    return res;
}

// Deterministic Miller-Rabin for n < 4,759,123,141
bool is_prime(ll n){
    if(n < 2) return false;
    int r = 0;
    ll d = n - 1;
    while((d & 1) == 0){
        d >>=1;
        r++;
    }
    // Witnesses for n < 4,759,123,141
    ll witnesses[] = {2,7,61};
    int num_witness = sizeof(witnesses)/sizeof(witnesses[0]);
    for(int i=0;i<num_witness;i++){
        if(witnesses[i] >= n) continue;
        ll a = witnesses[i];
        ll x = power(a, d, n);
        if(x ==1 || x == n-1) continue;
        bool cont_outer = false;
        for(int j=0;j<r-1;j++){
            x = mulmod(x, x, n);
            if(x == n-1){
                cont_outer = true;
                break;
            }
        }
        if(cont_outer) continue;
        return false;
    }
    return true;
}

int n, k;
int x[20];
int count_result = 0;

void backtrack(int start, int selected, ll sum){
    if(selected == k){
        if(is_prime(sum)){
            count_result++;
        }
        return;
    }
    for(int i=start;i<n;i++){
        backtrack(i+1, selected+1, sum + x[i]);
    }
}

int main(){
    scanf("%d %d", &n, &k);
    for(int i=0;i<n;i++) scanf("%d", &x[i]);
    backtrack(0, 0, 0);
    printf("%d\n", count_result);
    return 0;
}