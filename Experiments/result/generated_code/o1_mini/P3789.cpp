#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MOD 998244353
#define ROOT 3
#define MAX_SIZE 262144 // Next power of two >= 2*1e5

typedef long long ll;

// Fast exponentiation
ll power_mod_func(ll a, ll b, ll mod){
    ll res = 1;
    a %= mod;
    while(b > 0){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>=1;
    }
    return res;
}

// NTT implementation for 998244353
void ntt(ll a[], int n, int invert){
    for(int i=1,j=0;i<n;i++){
        int bit = n >>1;
        while(j >= bit){
            j -= bit;
            bit >>=1;
        }
        if(j < bit) j += bit;
        if(i < j){
            ll temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    for(int len=2; len<=n; len <<=1){
        ll wlen = power_mod_func(ROOT, (MOD-1)/len, MOD);
        if(invert) wlen = power_mod_func(wlen, MOD-2, MOD);
        for(int i=0;i<n;i+=len){
            ll w =1;
            for(int j=0; j<len/2; j++){
                ll u = a[i+j];
                ll v = a[i+j+len/2] * w % MOD;
                a[i+j] = (u + v) % MOD;
                a[i+j+len/2] = (u - v + MOD) % MOD;
                w = w * wlen % MOD;
            }
        }
    }

    if(invert){
        ll n_inv = power_mod_func(n, MOD-2, MOD);
        for(int i=0;i<n;i++) a[i] = a[i] * n_inv % MOD;
    }
}

// Multiply two polynomials a and b, result stored in res
void multiply(const ll a[], int na, const ll b[], int nb, ll res[], int k){
    int n =1;
    while(n < na + nb -1 && n < MAX_SIZE) n <<=1;
    ll fa[MAX_SIZE];
    ll fb[MAX_SIZE];
    for(int i=0;i<n;i++) fa[i] = (i < na) ? a[i] : 0;
    for(int i=0;i<n;i++) fb[i] = (i < nb) ? b[i] : 0;
    ntt(fa, n, 0);
    ntt(fb, n, 0);
    for(int i=0;i<n;i++) fa[i] = fa[i] * fb[i] % MOD;
    ntt(fa, n, 1);
    for(int i=0;i<=k;i++) res[i] = (i < na + nb -1 && i < n) ? fa[i] : 0;
}

// Define matrix with 3x3 polynomials
typedef struct {
    ll mat[3][3][100005];
} Matrix;

// Initialize identity matrix
Matrix identity;
void init_identity(int k){
    memset(identity.mat, 0, sizeof(identity.mat));
    for(int i=0;i<3;i++) identity.mat[i][i][0] =1;
}

// Initialize transition matrix
Matrix transition;
void init_transition(int k){
    memset(transition.mat, 0, sizeof(transition.mat));
    // T[0][1] = x
    for(int i=0;i<=k;i++) transition.mat[0][1][i] = (i ==1) ? 1 : 0;
    // T[0][2] =1
    for(int i=0;i<=k;i++) transition.mat[0][2][i] = (i ==0) ? 1 : 0;
    // T[1][0] =x
    for(int i=0;i<=k;i++) transition.mat[1][0][i] = (i ==1) ? 1 : 0;
    // T[1][2] =1
    for(int i=0;i<=k;i++) transition.mat[1][2][i] = (i ==0) ? 1 : 0;
    // T[2][0] =1
    for(int i=0;i<=k;i++) transition.mat[2][0][i] = (i ==0) ? 1 : 0;
    // T[2][1] =1
    for(int i=0;i<=k;i++) transition.mat[2][1][i] = (i ==0) ? 1 : 0;
    // T[2][2] =1
    for(int i=0;i<=k;i++) transition.mat[2][2][i] = (i ==0) ? 1 : 0;
}

// Multiply two matrices A and B, store in res
Matrix multiply_matrix(const Matrix A, const Matrix B, int k){
    Matrix res;
    memset(res.mat, 0, sizeof(res.mat));
    ll tmp[100005];
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            for(int l=0;l<3;l++){
                // Multiply A.mat[i][l] and B.mat[l][j]
                multiply(A.mat[i][l], 100005, B.mat[l][j], 100005, tmp, k);
                // Add to res.mat[i][j]
                for(int m=0;m<=k;m++) {
                    res.mat[i][j][m] += tmp[m];
                    if(res.mat[i][j][m] >= MOD) res.mat[i][j][m] -= MOD;
                }
            }
        }
    }
    return res;
}

// Exponentiate matrix A to power e, store in res
Matrix matrix_power(Matrix A, ll e, int k){
    Matrix res;
    init_identity(k);
    res = identity;
    while(e >0){
        if(e &1){
            res = multiply_matrix(res, A, k);
        }
        A = multiply_matrix(A, A, k);
        e >>=1;
    }
    return res;
}

int main(){
    ll n;
    int k;
    scanf("%lld %d", &n, &k);
    if(n ==0){
        for(int i=0;i<=k;i++) printf("%lld%c", (i==0)?1:0, i==k?'\n':' ');
        return 0;
    }
    init_identity(k);
    init_transition(k);
    Matrix T = transition;
    Matrix final = matrix_power(T, n-1, k);
    // Initial state [1,1,1]
    // Compute f_black, f_white, f_gray
    ll f_black[100005];
    ll f_white[100005];
    ll f_gray[100005];
    memset(f_black, 0, sizeof(f_black));
    memset(f_white, 0, sizeof(f_white));
    memset(f_gray, 0, sizeof(f_gray));
    for(int i=0;i<=k;i++) f_black[i] = final.mat[0][0][i];
    for(int i=0;i<=k;i++) {
        f_black[i] = (f_black[i] + final.mat[0][1][i]) % MOD;
        f_black[i] = (f_black[i] + final.mat[0][2][i]) % MOD;
    }
    for(int i=0;i<=k;i++) f_white[i] = final.mat[1][0][i];
    for(int i=0;i<=k;i++) {
        f_white[i] = (f_white[i] + final.mat[1][1][i]) % MOD;
        f_white[i] = (f_white[i] + final.mat[1][2][i]) % MOD;
    }
    for(int i=0;i<=k;i++) f_gray[i] = final.mat[2][0][i];
    for(int i=0;i<=k;i++) {
        f_gray[i] = (f_gray[i] + final.mat[2][1][i]) % MOD;
        f_gray[i] = (f_gray[i] + final.mat[2][2][i]) % MOD;
    }
    // Sum f_black, f_white, f_gray
    ll result[100005];
    memset(result, 0, sizeof(result));
    for(int i=0;i<=k;i++) {
        result[i] = (f_black[i] + f_white[i]) % MOD;
        result[i] = (result[i] + f_gray[i]) % MOD;
    }
    // If n ==1
    if(n ==1){
        memset(result, 0, sizeof(result));
        result[0] =3;
    }
    // Print the result
    for(int i=0;i<=k;i++) printf("%lld%c", result[i], (i==k)?'\n':' ');
    return 0;
}