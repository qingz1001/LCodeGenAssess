#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

typedef long long ll;

ll tree[MAXN];
ll pre_sum_arr[MAXN];
int flag_arr[MAXN];
int n, opt;
ll mod_val, min_val, max_val;

// Function to add value to Fenwick Tree
void add_ft(int idx, ll val) {
    while(idx <= n){
        tree[idx] += val;
        idx += idx & -idx;
    }
}

// Function to get prefix sum from Fenwick Tree
ll sum_ft(int idx){
    ll res = 0;
    while(idx > 0){
        res += tree[idx];
        idx -= idx & -idx;
    }
    return res;
}

int main(){
    // Fast IO
    // Read n, opt, mod, min, max
    if(scanf("%d %d %lld %lld %lld", &n, &opt, &mod_val, &min_val, &max_val)!=5){
        return 0;
    }

    char op[2];
    int L, R;
    ll X;

    for(int i=0;i<opt;i++){
        if(scanf("%s", op)!=1){
            break;
        }
        if(op[0]=='A'){
            if(scanf("%d %d %lld", &L, &R, &X)!=3){
                break;
            }
            add_ft(L, X);
            add_ft(R+1, -X);
        }
        else if(op[0]=='Q'){
            if(scanf("%d %d", &L, &R)!=2){
                break;
            }
            int count =0;
            for(int j=L; j<=R; j++){
                ll a_j = sum_ft(j);
                ll t_j = (a_j * (ll)j) % mod_val;
                if(t_j < 0){
                    // Adjust to match C's modulo behavior
                }
                if(t_j >= min_val && t_j <= max_val){
                    count++;
                }
            }
            printf("%d\n", count);
        }
    }

    // Read Final
    int Final;
    if(scanf("%d", &Final)!=1){
        return 0;
    }

    // Compute final a[i] and pre_sum
    for(int i=1;i<=n;i++){
        ll a_i = sum_ft(i);
        ll t_i = (a_i * (ll)i) % mod_val;
        // In C, modulo with negative numbers keeps the sign of the dividend
        if(t_i < 0){
            // t_i remains negative
        }
        flag_arr[i] = (t_i >= min_val && t_i <= max_val) ? 1 : 0;
        pre_sum_arr[i] = pre_sum_arr[i-1] + flag_arr[i];
    }

    // Process Final queries
    for(int i=0;i<Final;i++){
        if(scanf("%d %d", &L, &R)!=2){
            break;
        }
        ll res = pre_sum_arr[R] - pre_sum_arr[L-1];
        printf("%lld\n", res);
    }

    return 0;
}