#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MOD 65521
#define MAXN 1000

// Function to compute a^b mod m
int modpow_func(int a, int b, int m){
    int res = 1;
    a = a % m;
    while(b > 0){
        if(b & 1){
            res = (int)((long long)res * a % m);
        }
        a = (int)((long long)a * a % m);
        b >>=1;
    }
    return res;
}

// Function to compute modular inverse of a mod m
int modinv_func(int a, int m){
    return modpow_func(a, m-2, m);
}

int main(){
    int k, n;
    scanf("%d %d", &k, &n);
    if(n > MAXN) return 0;
    int B_matrix[MAXN][MAXN];
    // Initialize B_matrix to 0
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1;j++){
            B_matrix[i][j]=0;
        }
    }
    // Build B_matrix
    for(int i=0;i<n-1;i++){
        int degree =0;
        for(int j=0;j<n;j++){
            if(j ==i) continue;
            int dist = abs((i+1)-(j+1));
            if(dist > n/2){
                dist = n - dist;
            }
            if(dist <=k){
                degree +=1;
                if(j !=n-1){
                    B_matrix[i][j] = MOD -1;
                }
            }
        }
        B_matrix[i][i] = degree;
    }
    // Gaussian Elimination
    int det=1;
    int sign=1;
    for(int i=0;i<n-1;i++){
        // Find pivot
        int pivot_row = -1;
        for(int j=i;j<n-1;j++){
            if(B_matrix[j][i] !=0){
                pivot_row = j;
                break;
            }
        }
        if(pivot_row == -1){
            det =0;
            break;
        }
        if(pivot_row !=i){
            // Swap rows
            for(int l=0;l<n-1;l++){
                int temp = B_matrix[i][l];
                B_matrix[i][l] = B_matrix[pivot_row][l];
                B_matrix[pivot_row][l] = temp;
            }
            sign = -sign;
        }
        int pivot = B_matrix[i][i];
        det = (int)((long long)det * pivot % MOD);
        int inv_pivot = modinv_func(pivot, MOD);
        for(int j=i+1;j<n-1;j++){
            if(B_matrix[j][i]==0) continue;
            int factor = (int)((long long)B_matrix[j][i] * inv_pivot % MOD);
            for(int l=i;l<n-1;l++){
                long long temp = (long long)B_matrix[j][l] - (long long)factor * B_matrix[i][l];
                temp %= MOD;
                if(temp <0) temp += MOD;
                B_matrix[j][l] = (int)temp;
            }
        }
    }
    if(sign ==-1){
        det = (MOD - det) % MOD;
    }
    printf("%d\n", det);
    return 0;
}