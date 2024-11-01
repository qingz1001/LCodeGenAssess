#include <stdio.h>
#include <string.h>

typedef long long ll;

ll mod_pow(ll base, ll exp, ll mod) {
    ll result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        ll n, k, p;
        scanf("%lld %lld %lld", &n, &k, &p);
        
        // Calculate the number of palindromic strings
        ll total_palindromes = mod_pow(k, n, p);
        
        // Calculate the number of non-palindromic strings
        ll non_palindromes = mod_pow(k - 1, n, p);
        
        // Total number of strings is k^n
        // Subtract non-palindromic strings from total to get palindromic strings
        ll result = (total_palindromes - non_palindromes + p) % p;
        
        printf("%lld\n", result);
    }
    return 0;
}