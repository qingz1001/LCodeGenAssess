#include <stdio.h>
#include <stdint.h>

typedef long long ll;

// Function to perform modular multiplication (a * b) % mod
ll mulmod(ll a, ll b, ll mod){
    ll res = 0;
    a = a % mod;
    while(b > 0){
        if(b & 1){
            res = (__int128(res) + a) % mod;
        }
        a = (__int128(a) * 2) % mod;
        b >>= 1;
    }
    return res;
}

// Function to perform modular exponentiation (base^exponent) % mod
ll power(ll base, ll exponent, ll mod){
    ll result = 1;
    base = base % mod;
    while(exponent > 0){
        if(exponent & 1){
            result = mulmod(result, base, mod);
        }
        base = mulmod(base, base, mod);
        exponent >>= 1;
    }
    return result;
}

// Deterministic Miller-Rabin primality test for n < 4759123141
int is_prime(ll n){
    if(n < 2) return 0;
    int r = 0;
    ll d = n -1;
    while((d & 1) == 0){
        d >>= 1;
        r++;
    }
    // Bases for n < 4759123141
    int bases[] = {2,7,61};
    int num_bases = sizeof(bases)/sizeof(bases[0]);
    for(int i=0;i<num_bases;i++){
        if(bases[i] >= n) continue;
        ll a = bases[i];
        ll x = power(a, d, n);
        if(x ==1 || x == n-1) continue;
        int cont = 0;
        for(int j=0;j<r-1;j++){
            x = mulmod(x, x, n);
            if(x == n-1){
                cont =1;
                break;
            }
        }
        if(cont) continue;
        return 0;
    }
    return 1;
}

int n, k;
int arr[20];
int count_prime = 0;

void combine(int start, int selected, ll sum){
    if(selected == k){
        if(is_prime(sum)) count_prime++;
        return;
    }
    for(int i=start;i <= n - (k - selected);i++){
        combine(i+1, selected+1, sum + arr[i]);
    }
}

int main(){
    scanf("%d %d", &n, &k);
    for(int i=0;i<n;i++) scanf("%d", &arr[i]);
    combine(0, 0, 0);
    printf("%d\n", count_prime);
    return 0;
}