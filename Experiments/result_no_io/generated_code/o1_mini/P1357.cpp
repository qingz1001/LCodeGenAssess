#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007

typedef struct {
    int size;
    long long **mat;
} Matrix;

// Function to create a matrix
Matrix create_matrix(int size) {
    Matrix matrix;
    matrix.size = size;
    matrix.mat = (long long **)malloc(size * sizeof(long long *));
    for(int i=0;i<size;i++) {
        matrix.mat[i] = (long long *)calloc(size, sizeof(long long));
    }
    return matrix;
}

// Function to free a matrix
void free_matrix(Matrix matrix) {
    for(int i=0;i<matrix.size;i++) {
        free(matrix.mat[i]);
    }
    free(matrix.mat);
}

// Function to copy a matrix
Matrix copy_matrix(Matrix src) {
    Matrix dest = create_matrix(src.size);
    for(int i=0;i<src.size;i++) {
        for(int j=0;j<src.size;j++) {
            dest.mat[i][j] = src.mat[i][j];
        }
    }
    return dest;
}

// Function to multiply two matrices
Matrix multiply(Matrix a, Matrix b) {
    int size = a.size;
    Matrix result = create_matrix(size);
    for(int i=0;i<size;i++) {
        for(int k=0;k<size;k++) {
            if(a.mat[i][k] == 0) continue;
            for(int j=0;j<size;j++) {
                result.mat[i][j] = (result.mat[i][j] + a.mat[i][k] * b.mat[k][j]) % MOD;
            }
        }
    }
    return result;
}

// Function to perform matrix exponentiation
Matrix matrix_pow(Matrix base, long long power) {
    int size = base.size;
    Matrix result = create_matrix(size);
    // Initialize result as identity matrix
    for(int i=0;i<size;i++) {
        result.mat[i][i] = 1;
    }
    Matrix temp = copy_matrix(base);
    while(power > 0) {
        if(power & 1) {
            Matrix new_result = multiply(result, temp);
            free_matrix(result);
            result = new_result;
        }
        power >>= 1;
        if(power > 0) {
            Matrix new_temp = multiply(temp, temp);
            free_matrix(temp);
            temp = new_temp;
        }
    }
    free_matrix(temp);
    return result;
}

// Function to count number of set bits
int count_bits(int x) {
    int cnt = 0;
    while(x){
        cnt += x & 1;
        x >>=1;
    }
    return cnt;
}

int main(){
    long long n;
    int m, k;
    scanf("%lld %d %d", &n, &m, &k);
    if(n < m){
        // Handle small n separately
        // Since n can be up to 1e15, and m<=5, n>=2
        // Implemented as circular constraints
        // For simplicity, proceed with the main approach
    }
    int s = 1 << (m-1);
    Matrix M = create_matrix(s);
    int mask = (1 << (m-1)) -1;
    for(int S=0; S<s; S++){
        int cnt = count_bits(S);
        for(int X=0; X<2; X++){
            int oldest_bit = (m-1)>=2 ? ((S >> (m-2)) &1) : 0;
            // For m=1, oldest_bit is not defined, assume 0
            long long num_c = cnt + X - oldest_bit;
            if(num_c <= k){
                int S_new = ((S <<1) | X) & mask;
                M.mat[S][S_new] = (M.mat[S][S_new] + 1) % MOD;
            }
        }
    }
    Matrix Mn = matrix_pow(M, n);
    long long trace = 0;
    for(int i=0;i<Mn.size;i++) {
        trace = (trace + Mn.mat[i][i]) % MOD;
    }
    printf("%lld\n", trace);
    free_matrix(Mn);
    free_matrix(M);
    return 0;
}