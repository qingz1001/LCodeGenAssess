#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXN 20
#define MOD 998244353

typedef long long ll;

// Fast power for inverse
ll power_mod(ll a, ll b, ll mod){
    ll res=1;a%=mod;
    while(b>0){
        if(b&1) res=res*a%mod;
        a=a*a%mod; b>>=1;
    }
    return res;
}

// Inverse modulo
ll inv(ll a){
    return power_mod(a, MOD-2, MOD);
}

// Adjacency list
int adj[MAXN][MAXN];
int degg[MAXN];
int N, E;

// E_field[s][w] stores E(s,w) as integer mod MOD
ll E_field[MAXN][MAXN];
// E_double[s][w] stores E(s,w) as double
double E_double_val[MAXN][MAXN];

// Temporary mapping
int var_map[MAXN];
int var_cnt;

// Function to solve in field
int solve_field(int w){
    int size = N-1;
    // Initialize augmented matrix
    ll mat[MAXN][MAXN];
    memset(mat, 0, sizeof(mat));
    // Map variables
    var_cnt =0;
    for(int s=1;s<=N;s++) if(s !=w) var_map[s]=var_cnt++;
    // Build matrix
    for(int s=1;s<=N;s++) if(s !=w){
        int row = var_map[s];
        mat[row][var_cnt] = 1; // RHS
        mat[row][var_map[s]] = degg[s];
        for(int v=0; v<degg[s]; v++){
            int neighbor = adj[s][v];
            if(neighbor !=w){
                mat[row][var_map[neighbor]] = (mat[row][var_map[neighbor]] -1 + MOD)%MOD;
            }
        }
    }
    // Gaussian elimination
    for(int i=0;i<size;i++){
        // Find pivot
        int pivot = -1;
        for(int j=i;j<size;j++) if(mat[j][i]!=0){
            pivot = j; break;
        }
        if(pivot == -1){
            // Should not happen
            return -1;
        }
        if(pivot !=i){
            // Swap rows
            for(int k=0;k<=size;k++){
                ll tmp = mat[i][k];
                mat[i][k] = mat[pivot][k];
                mat[pivot][k] = tmp;
            }
        }
        // Normalize pivot
        ll inv_p = inv(mat[i][i]);
        for(int k=i; k<=size; k++) mat[i][k] = mat[i][k] * inv_p % MOD;
        // Eliminate other rows
        for(int j=0;j<size;j++) if(j !=i && mat[j][i]!=0){
            ll factor = mat[j][i];
            for(int k=i; k<=size; k++) {
                mat[j][k] = (mat[j][k] - factor * mat[i][k]%MOD + MOD)%MOD;
            }
        }
    }
    // Now, mat[i][size] is the solution for variable i
    for(int s=1;s<=N;s++) if(s !=w){
        int row = var_map[s];
        E_field[s][w] = mat[row][size];
    }
    return 0;
}

// Function to solve in double
int solve_double(int w){
    int size = N-1;
    // Initialize augmented matrix
    double mat[MAXN][MAXN];
    memset(mat, 0, sizeof(mat));
    // Map variables
    var_cnt =0;
    for(int s=1;s<=N;s++) if(s !=w) var_map[s]=var_cnt++;
    // Build matrix
    for(int s=1;s<=N;s++) if(s !=w){
        int row = var_map[s];
        mat[row][size] = degg[s];
        mat[row][var_map[s]] = degg[s];
        for(int v=0; v<degg[s]; v++){
            int neighbor = adj[s][v];
            if(neighbor !=w){
                mat[row][var_map[neighbor]] -=1.0;
            }
        }
    }
    // Gaussian elimination
    for(int i=0;i<size;i++){
        // Find pivot
        int pivot = -1;
        double max_val = 0.0;
        for(int j=i;j<size;j++) {
            if(fabs(mat[j][i]) > max_val){
                max_val = fabs(mat[j][i]);
                pivot = j;
            }
        }
        if(pivot == -1){
            // Should not happen
            return -1;
        }
        if(pivot !=i){
            // Swap rows
            for(int k=0;k<=size;k++){
                double tmp = mat[i][k];
                mat[i][k] = mat[pivot][k];
                mat[pivot][k] = tmp;
            }
        }
        // Normalize pivot
        double factor = mat[i][i];
        for(int k=i; k<=size; k++) mat[i][k] /= factor;
        // Eliminate other rows
        for(int j=0;j<size;j++) if(j !=i){
            double f = mat[j][i];
            for(int k=i; k<=size; k++) mat[j][k] -= f * mat[i][k];
        }
    }
    // Now, mat[i][size] is the solution
    for(int s=1;s<=N;s++) if(s !=w){
        int row = var_map[s];
        E_double_val[s][w] = mat[row][size];
    }
    return 0;
}

int main(){
    // Read N and E
    scanf("%d %d", &N, &E);
    // Initialize adjacency
    for(int i=1;i<=N;i++) degg[i]=0;
    for(int i=0;i<E;i++){
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][degg[u]++] = v;
        adj[v][degg[v]++] = u;
    }
    // Precompute E_field and E_double
    for(int w=1; w<=N; w++){
        solve_field(w);
        solve_double(w);
    }
    // Read M
    int M;
    scanf("%d", &M);
    // Process M queries
    for(int q=0; q<M; q++){
        int n;
        scanf("%d", &n);
        int C[20];
        for(int i=0;i<n;i++) scanf("%d", &C[i]);
        int s;
        scanf("%d", &s);
        // Find ci with maximum E_double[s][ci]
        double max_val = -1.0;
        int best = C[0];
        for(int i=0;i<n;i++) {
            if(E_double_val[s][C[i]] > max_val){
                max_val = E_double_val[s][C[i]];
                best = C[i];
            }
        }
        // Output E_field[s][best]
        printf("%lld\n", E_field[s][best]);
    }
    return 0;
}