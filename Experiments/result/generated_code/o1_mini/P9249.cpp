#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MOD 998244353
#define MAX_N 64
#define MAX_M 20000

typedef unsigned long long ull;
typedef unsigned int uint;

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    uint A[MAX_N][MAX_N];
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            scanf("%u", &A[i][j]);
        }
    }
    // Initialize M_current as A
    uint M_prev[MAX_N][MAX_N];
    memcpy(M_prev, A, sizeof(A));
    // Initialize C[z][k] and F[z][k]
    ull C[64][20001];
    memset(C, 0, sizeof(C));
    ull F[64][20001];
    memset(F, 0, sizeof(F));
    // Temporary matrix for multiplication
    uint M_current[MAX_N][MAX_N];
    memcpy(M_current, A, sizeof(A));
    for(int k=1; k<=m; k++){
        // Count C[z][k]
        for(int s=0; s<n; s++){
            for(int t=0; t<n; t++){
                int z = s & t;
                C[z][k] += M_current[s][t];
                if(C[z][k] >= MOD) C[z][k] -= MOD;
            }
        }
        // Compute F[z][k} using Fast Zeta Transform (superset sum)
        for(int z=0; z<(1<<6); z++) { // assuming n<=64
            F[z][k] = C[z][k];
        }
        for(int bit=0; bit<6; bit++){
            for(int z=0; z<(1<<6); z++){
                if( (z & (1 << bit)) ==0 ){
                    F[z][k] += F[z | (1 << bit)][k];
                    if(F[z][k] >= MOD) F[z][k] -= MOD;
                }
            }
        }
        // Multiply M_current = M_prev * A
        uint temp[MAX_N][MAX_N];
        memset(temp, 0, sizeof(temp));
        for(int i=0; i<n; i++){
            for(int k1=0; k1<n; k1++){
                if(M_prev[i][k1]==0) continue;
                for(int j=0; j<n; j++){
                    temp[i][j] += (ull)M_prev[i][k1] * A[k1][j];
                    if(temp[i][j] >= MOD) temp[i][j] %= MOD;
                }
            }
        }
        // Update M_prev
        for(int i=0; i<n; i++) {
            for(int j=0; j<n; j++) {
                M_prev[i][j] = temp[i][j] % MOD;
            }
        }
        memcpy(M_current, M_prev, sizeof(M_prev));
    }
    // Compute G[z][x} for all z and x
    ull G[64][20001];
    memset(G, 0, sizeof(G));
    for(int z=0; z<(1<<6); z++){
        G[z][0] = 0;
        for(int x=1; x<=m; x++){
            G[z][x] = F[z][x];
            for(int k=1; k<x; k++){
                G[z][x] += (G[z][x -k] * F[z][k]) % MOD;
                if(G[z][x] >= MOD) G[z][x] -= MOD;
            }
            G[z][x] %= MOD;
        }
    }
    // Compute f[y][x} using Möbius Inversion
    ull f[64][20001];
    memset(f, 0, sizeof(f));
    for(int x=1; x<=m; x++){
        for(int y=0; y<(1<<6); y++){
            ull res = 0;
            int extra = (~y) & ((1<<6)-1);
            for(int s = extra; ; s = (s-1) & extra){
                int z = y | s;
                int bits = __builtin_popcount(s);
                if(bits & 1){
                    res += (MOD - G[z][x]);
                }
                else{
                    res += G[z][x];
                }
                if(res >= MOD) res -= MOD;
                if(s ==0) break;
            }
            f[y][x] = res % MOD;
        }
    }
    // Compute XOR of all f[y][x} % MOD
    ull result =0;
    for(int y=0; y<(1<<6); y++){
        for(int x=1; x<=m; x++){
            ull val = f[y][x] % MOD;
            result ^= val;
        }
    }
    printf("%llu\n", result);
    return 0;
}