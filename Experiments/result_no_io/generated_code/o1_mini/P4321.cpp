#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MOD 998244353
#define MAXN 20

typedef long long ll;

typedef struct {
    ll num;
    ll den;
} Fraction;

// Function to compute gcd
ll gcd_func(ll a, ll b){
    while(b){
        ll tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

// Function to reduce a fraction
void reduce_fraction(Fraction *f){
    if(f->num ==0){
        f->den =1;
        return;
    }
    ll g = gcd_func(f->num <0 ? -f->num : f->num, f->den <0 ? -f->den : f->den);
    f->num /= g;
    f->den /= g;
    if(f->den <0){
        f->num = -f->num;
        f->den = -f->den;
    }
}

// Fraction addition
Fraction add_frac(Fraction a, Fraction b){
    Fraction res;
    res.num = a.num * b.den + b.num * a.den;
    res.den = a.den * b.den;
    reduce_fraction(&res);
    return res;
}

// Fraction subtraction
Fraction sub_frac(Fraction a, Fraction b){
    Fraction res;
    res.num = a.num * b.den - b.num * a.den;
    res.den = a.den * b.den;
    reduce_fraction(&res);
    return res;
}

// Fraction multiplication
Fraction mul_frac(Fraction a, Fraction b){
    Fraction res;
    res.num = a.num * b.num;
    res.den = a.den * b.den;
    reduce_fraction(&res);
    return res;
}

// Fraction division
Fraction div_frac(Fraction a, Fraction b){
    Fraction res;
    res.num = a.num * b.den;
    res.den = a.den * b.num;
    reduce_fraction(&res);
    return res;
}

// Function to compute inverse modulo
ll power_mod(ll a, ll b){
    ll res =1;
    a %= MOD;
    while(b >0){
        if(b &1){
            res = res * a % MOD;
        }
        a = a * a % MOD;
        b >>=1;
    }
    return res;
}

// Structure for augmented matrix rows
typedef struct {
    Fraction A[MAXN];
    Fraction b;
} Row;

// Function to perform Gaussian elimination for each target
void gaussian_elimination(int t, int N, int adj[][MAXN], int degree, Fraction E_num[][MAXN], Fraction E_den[][MAXN], double E_float[][MAXN]){
    int var = N-1;
    Row mat[MAXN];
    int mapping[MAXN];
    int idx =0;
    for(int s=1;s<=N;s++) {
        if(s == t) continue;
        mapping[s] = idx++;
    }
    // Initialize matrix
    for(int s=1;s<=N;s++) {
        if(s == t) continue;
        int row = mapping[s];
        // Initialize A coefficients
        for(int v=1; v<=N; v++) {
            if(v == t) continue;
            if(v == s){
                mat[row].A[v].num = degree;
                mat[row].A[v].den =1;
            }
            else{
                mat[row].A[v].num =0;
                mat[row].A[v].den =1;
            }
        }
        // Set coefficients for neighbors
        for(int v=0; v<degree; v++){
            int neighbor = adj[s][v];
            if(neighbor == t) continue;
            mat[row].A[neighbor].num = (mat[row].A[neighbor].num -1) % MOD;
            if(mat[row].A[neighbor].num <0) mat[row].A[neighbor].num += MOD;
        }
        // Initialize b
        mat[row].b.num = degree;
        mat[row].b.den =1;
    }
    // Gaussian Elimination
    for(int i=0;i<var;i++){
        // Pivot
        int pivot = i;
        while(pivot < var && mat[pivot].A[mapping[i+1 <= t ? i+1 : i]].num ==0){
            pivot++;
        }
        if(pivot == var){
            continue;
        }
        // Swap rows if needed
        if(pivot != i){
            Row tmp = mat[i];
            mat[i] = mat[pivot];
            mat[pivot] = tmp;
        }
        // Normalize pivot row
        ll inv = power_mod(mat[i].A[i+1 <= t ? i+1 : i].num, MOD-2);
        // Multiply all A and b by inv
        for(int j=1;j<=N;j++) {
            if(j == t) continue;
            ll a_num = mat[i].A[j].num;
            ll a_den = mat[i].A[j].den;
            a_num = a_num * inv % MOD;
            mat[i].A[j].num = a_num;
            mat[i].A[j].den =1;
        }
        ll b_num = mat[i].b.num;
        ll b_den = mat[i].b.den;
        b_num = b_num * inv % MOD;
        mat[i].b.num = b_num;
        mat[i].b.den =1;
        // Eliminate below
        for(int j=0;j<var;j++){
            if(j == i) continue;
            ll factor = mat[j].A[i+1 <= t ? i+1 : i].num;
            if(factor ==0) continue;
            // Subtract factor * pivot row from row j
            for(int k=1;k<=N;k++){
                if(k == t) continue;
                ll a_jk = mat[j].A[k].num;
                mat[j].A[k].num = (a_jk - factor * mat[i].A[k].num) % MOD;
                if(mat[j].A[k].num <0) mat[j].A[k].num += MOD;
            }
            // Update b
            mat[j].b.num = (mat[j].b.num - factor * mat[i].b.num) % MOD;
            if(mat[j].b.num <0) mat[j].b.num += MOD;
        }
    }
    // Back substitution
    Fraction x[MAXN];
    for(int i=var-1;i>=0;i--){
        x[i].num = mat[i].b.num;
        x[i].den =1;
        for(int j=i+1;j<var;j++){
            int s = j < i ? j : j;
            ll coeff = mat[i].A[j+1 <= t ? j+1 : j].num;
            if(coeff) {
                // x[i] = x[i] - coeff * x[j]
                Fraction temp;
                temp.num = coeff;
                temp.den =1;
                Fraction mul = mul_frac(temp, x[j]);
                x[i] = sub_frac(x[i], mul);
            }
        }
    }
    // Store results
    for(int s=1;s<=N;s++) {
        if(s == t) continue;
        int row = mapping[s];
        int var_idx = mapping[s];
        E_num[s][t] = x[var_idx].num;
        E_den[s][t] = x[var_idx].den;
        E_float[s][t] = (double)x[var_idx].num / (double)x[var_idx].den;
    }
}

int main(){
    int N, E;
    scanf("%d %d", &N, &E);
    int adj[MAXN][MAXN];
    int degree[MAXN];
    for(int i=1;i<=N;i++) degree[i]=0;
    for(int i=0;i<E;i++){
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][degree[u]++] = v;
        adj[v][degree[v]++] = u;
    }
    Fraction E_num[MAXN][MAXN];
    Fraction E_den_store[MAXN][MAXN];
    double E_float_store[MAXN][MAXN];
    memset(E_num, 0, sizeof(E_num));
    memset(E_den_store, 0, sizeof(E_den_store));
    memset(E_float_store, 0, sizeof(E_float_store));
    for(int t=1;t<=N;t++){
        gaussian_elimination(t, N, adj, degree[t], E_num, E_den_store, E_float_store);
    }
    // Compute E[s][t}
    // Now read M
    int M;
    scanf("%d", &M);
    for(int q=0; q<M; q++){
        int n;
        scanf("%d", &n);
        int c_list[20];
        for(int i=0;i<n;i++) scanf("%d", &c_list[i]);
        int s;
        scanf("%d", &s);
        double max_val = -1.0;
        int chosen = -1;
        for(int i=0;i<n;i++){
            int ci = c_list[i];
            if(E_float_store[s][ci] > max_val){
                max_val = E_float_store[s][ci];
                chosen = ci;
            }
        }
        ll num = E_num[s][chosen] % MOD;
        ll den = E_den_store[s][chosen] % MOD;
        ll inv_den = power_mod(den, MOD-2);
        ll res = num * inv_den % MOD;
        printf("%lld\n", res);
    }
    return 0;
}