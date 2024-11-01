#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

#define MAXN 1005
const ll base = 1000003;
const ll mod = 1000000007;

ll a[MAXN][MAXN];
ll power_base[MAXN];
ll hash_row_f[MAXN][MAXN];
ll hash_row_r[MAXN][MAXN];
ll hash_col_f[MAXN][MAXN];
ll hash_col_r[MAXN][MAXN];
int pal_row[MAXN][MAXN];
int pal_col[MAXN][MAXN];

ll power_mod(ll base, int exp, ll mod){
    ll res = 1;
    ll b = base;
    while(exp >0){
        if(exp &1){
            res = (res * b) % mod;
        }
        b = (b * b) % mod;
        exp >>=1;
    }
    return res;
}

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            scanf("%lld", &a[i][j]);
        }
    }
    power_base[0] =1;
    for(int i=1;i<=1000;i++) power_base[i] = (power_base[i-1] * base) % mod;
    // Compute row forward and reverse hashes
    for(int i=1;i<=n;i++){
        hash_row_f[i][0] =0;
        for(int j=1;j<=m;j++){
            hash_row_f[i][j] = (hash_row_f[i][j-1] * base + a[i][j]) % mod;
        }
        hash_row_r[i][m+1] =0;
        for(int j=m;j>=1;j--){
            hash_row_r[i][j] = (hash_row_r[i][j+1] * base + a[i][j]) % mod;
        }
    }
    // Compute column forward and reverse hashes
    for(int j=1;j<=m;j++){
        hash_col_f[0][j] =0;
        for(int i=1;i<=n;i++){
            hash_col_f[i][j] = (hash_col_f[i-1][j] * base + a[i][j]) % mod;
        }
        hash_col_r[n+1][j] =0;
        for(int i=n;i>=1;i--){
            hash_col_r[i][j] = (hash_col_r[i+1][j] * base + a[i][j]) % mod;
        }
    }
    // Function to get row hash
    #define GET_ROW_F(i,l,r) (((hash_row_f[i][r] - (hash_row_f[i][l-1] * power_base[r-l+1])%mod)+mod)%mod)
    #define GET_ROW_R(i,l,r) (((hash_row_r[i][l] - (hash_row_r[i][r+1] * power_base[r-l+1])%mod)+mod)%mod)
    #define GET_COL_F(j,l,r) (((hash_col_f[r][j] - (hash_col_f[l-1][j] * power_base[r-l+1])%mod)+mod)%mod)
    #define GET_COL_R(j,l,r) (((hash_col_r[l][j] - (hash_col_r[r+1][j] * power_base[r-l+1])%mod)+mod)%mod)
    // Compute pal_row
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            int low=1, high=m-j+1, res=1;
            while(low <= high){
                int mid = (low + high)/2;
                if(j + mid -1 >m){
                    high = mid -1;
                    continue;
                }
                ll hash_f = GET_ROW_F(i,j,j+mid-1);
                ll hash_r = GET_ROW_R(i,j,j+mid-1);
                if(hash_f == hash_r){
                    res = mid;
                    low = mid +1;
                }
                else{
                    high = mid -1;
                }
            }
            pal_row[i][j] = res;
        }
    }
    // Compute pal_col
    for(int j=1;j<=m;j++){
        for(int i=1;i<=n;i++){
            int low=1, high=n-i+1, res=1;
            while(low <= high){
                int mid = (low + high)/2;
                if(i + mid -1 >n){
                    high = mid -1;
                    continue;
                }
                ll hash_f = GET_COL_F(j,i,i+mid-1);
                ll hash_r = GET_COL_R(j,i,i+mid-1);
                if(hash_f == hash_r){
                    res = mid;
                    low = mid +1;
                }
                else{
                    high = mid -1;
                }
            }
            pal_col[i][j] = res;
        }
    }
    ll ans =0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            ll tmp = pal_row[i][j] < pal_col[i][j] ? pal_row[i][j] : pal_col[i][j];
            ans += tmp;
        }
    }
    printf("%lld", ans);
    return 0;
}