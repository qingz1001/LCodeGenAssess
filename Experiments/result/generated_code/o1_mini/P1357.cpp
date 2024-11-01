#include <stdio.h>
#include <stdint.h>
#define MOD 1000000007

typedef unsigned long long ull;

// Matrix size up to 16x16
typedef struct {
    int size;
    ull mat[16][16];
} Matrix;

// Multiply two matrices
Matrix multiply(Matrix a, Matrix b) {
    Matrix res;
    res.size = a.size;
    for(int i=0;i<a.size;i++) {
        for(int j=0;j<b.size;j++) {
            res.mat[i][j] = 0;
            for(int k=0;k<a.size;k++) {
                res.mat[i][j] = (res.mat[i][j] + a.mat[i][k] * b.mat[k][j]) % MOD;
            }
        }
    }
    return res;
}

// Fast exponentiation of matrix
Matrix power_matrix(Matrix a, ull power) {
    Matrix res;
    res.size = a.size;
    // Initialize res as identity matrix
    for(int i=0;i<a.size;i++) {
        for(int j=0;j<a.size;j++) {
            res.mat[i][j] = (i == j) ? 1 : 0;
        }
    }
    Matrix base = a;
    while(power > 0) {
        if(power & 1) {
            res = multiply(res, base);
        }
        base = multiply(base, base);
        power >>=1;
    }
    return res;
}

int main(){
    ull n;
    int m, k;
    scanf("%llu %d %d", &n, &m, &k);
    if(m > n) m = n;
    int S = 1 << (m-1);
    Matrix A;
    A.size = S;
    for(int i=0;i<S;i++) {
        for(int b=0;b<2;b++) {
            // Build window
            ull window = ((i << 1) | b) & (S-1);
            // Count bits set
            int cnt = 0;
            ull temp = window;
            while(temp){
                cnt += temp &1;
                temp >>=1;
            }
            if(cnt <=k){
                A.mat[i][window] = (A.mat[i][window] +1) % MOD;
            }
        }
    }
    Matrix An = power_matrix(A, n);
    ull trace =0;
    for(int i=0;i<S;i++) {
        trace = (trace + An.mat[i][i]) % MOD;
    }
    printf("%llu\n", trace);
}