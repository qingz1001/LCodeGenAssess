#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 100
#define MOD 65521

typedef long long ll;

// Function to compute a^b mod mod
ll power_mod(ll a, ll b, ll mod_val){
    ll res = 1;
    a %= mod_val;
    while(b > 0){
        if(b & 1){
            res = res * a % mod_val;
        }
        a = a * a % mod_val;
        b >>=1;
    }
    return res;
}

// Function to compute modular inverse of a mod mod_val
ll inverse(ll a, ll mod_val){
    return power_mod(a, mod_val - 2, mod_val);
}

// Function to compute determinant of matrix n x n modulo mod_val
ll determinant(int n, ll mat[][MAXN], ll mod_val){
    ll det = 1;
    int sign = 1;
    for(int i=0;i<n;i++){
        // Find pivot
        int pivot = i;
        while(pivot < n && mat[pivot][i] ==0){
            pivot++;
        }
        if(pivot == n){
            return 0;
        }
        if(pivot != i){
            // Swap rows
            for(int j=0;j<n;j++){
                ll temp = mat[pivot][j];
                mat[pivot][j] = mat[i][j];
                mat[i][j] = temp;
            }
            sign *= -1;
        }
        det = det * mat[i][i] % mod_val;
        if(mat[i][i] ==0){
            return 0;
        }
        ll inv = inverse(mat[i][i], mod_val);
        for(int j=i+1;j<n;j++){
            if(mat[j][i]==0){
                continue;
            }
            ll factor = mat[j][i] * inv % mod_val;
            for(int k=i;k<n;k++){
                mat[j][k] = (mat[j][k] - factor * mat[i][k]) % mod_val;
                if(mat[j][k] <0){
                    mat[j][k] += mod_val;
                }
            }
        }
    }
    if(sign == -1){
        det = (-det) % mod_val;
        if(det <0){
            det += mod_val;
        }
    }
    return det;
}

int main(){
    int k, n;
    scanf("%d %d", &k, &n);
    if(n ==1){
        printf("1\n");
        return 0;
    }
    // Construct A
    ll A[MAXN][MAXN];
    for(int i=0;i<n;i++){
        // Compute degree d_i
        int left = (i < k) ? i : k;
        int right = ((n-1 -i) < k) ? (n-1 -i) : k;
        A[i][i] = (ll)(left + right);
        for(int j=0;j<n;j++){
            if(i == j){
                continue;
            }
            int diff = abs(i - j);
            if(diff >=1 && diff <=k){
                A[i][j] = -1;
            }
            else{
                A[i][j] = 0;
            }
        }
    }
    // Construct B by removing last row and column
    int size = n-1;
    ll B[MAXN][MAXN];
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            B[i][j] = A[i][j];
        }
    }
    // Make a copy of B for determinant calculation
    ll mat[MAXN][MAXN];
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            mat[i][j] = B[i][j];
            // Ensure all entries are positive modulo
            if(mat[i][j] <0){
                mat[i][j] = (mat[i][j] % MOD + MOD) % MOD;
            }
            else{
                mat[i][j] %= MOD;
            }
        }
    }
    ll det = determinant(size, mat, MOD);
    printf("%lld\n", det);
    return 0;
}