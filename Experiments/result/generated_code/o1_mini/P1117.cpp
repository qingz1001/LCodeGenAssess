#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define MAXN 30005
typedef long long ll;

// Define two moduli for double hashing
const ll MOD1 = 1000000007;
const ll MOD2 = 1000000009;
const ll BASE = 911382629;

// Precompute powers
ll power1[MAXN];
ll power2[MAXN];

// Precompute prefix hashes
ll hash1[MAXN];
ll hash2[MAXN];

// Function to initialize powers
void init_powers(int n) {
    power1[0] = 1;
    power2[0] = 1;
    for(int i = 1; i <= n; i++) {
        power1[i] = (power1[i-1] * BASE) % MOD1;
        power2[i] = (power2[i-1] * BASE) % MOD2;
    }
}

// Function to compute prefix hashes
void compute_hashes(char *s, int n) {
    hash1[0] = 0;
    hash2[0] = 0;
    for(int i = 0; i < n; i++) {
        hash1[i+1] = (hash1[i] * BASE + (s[i] - 'a' + 1)) % MOD1;
        hash2[i+1] = (hash2[i] * BASE + (s[i] - 'a' + 1)) % MOD2;
    }
}

// Function to get hash of substring [l, r)
ll get_hash1(int l, int r){
    return (hash1[r] - (hash1[l] * power1[r - l])%MOD1 + MOD1) % MOD1;
}

ll get_hash2(int l, int r){
    return (hash2[r] - (hash2[l] * power2[r - l])%MOD2 + MOD2) % MOD2;
}

// Function to check equality of two substrings
int equal(int l1, int r1, int l2, int r2){
    if(r1 - l1 != r2 - l2) return 0;
    return (get_hash1(l1, r1) == get_hash1(l2, r2))&&(get_hash2(l1, r1) == get_hash2(l2, r2));
}

int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        char S[MAXN];
        scanf("%s", S);
        int n = strlen(S);
        init_powers(n);
        compute_hashes(S, n);
        ll total = 0;
        for(int i = 0; i < n; i++){
            // Maximum possible a
            for(int a = 1; a <= (n - i)/2; a++){
                if(i + 2*a > n) break;
                if(equal(i, i + a, i + a, i + 2*a)){
                    // Now find b
                    for(int b = 1; b <= (n - i - 2*a)/2; b++){
                        if(i + 2*a + 2*b > n) break;
                        if(equal(i + 2*a, i + 2*a + b, i + 2*a + b, i + 2*a + 2*b)){
                            total++;
                        }
                    }
                }
            }
        }
        printf("%lld\n", total);
    }
    return 0;
}