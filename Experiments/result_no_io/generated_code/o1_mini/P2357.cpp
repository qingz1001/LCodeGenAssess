#include <stdio.h>
#include <stdlib.h>

#define MAXN 200005

typedef long long ll;

ll B1[MAXN], B2[MAXN];
int n, f;

// Function to update the BIT
void updateBIT(ll BIT[], int idx, ll val){
    while(idx < MAXN){
        BIT[idx] += val;
        idx += idx & (-idx);
    }
}

// Function to query the BIT
ll queryBIT(ll BIT[], int idx){
    ll res = 0;
    while(idx > 0){
        res += BIT[idx];
        idx -= idx & (-idx);
    }
    return res;
}

int main(){
    scanf("%d %d", &n, &f);
    for(int i=1;i<=n;i++){
        ll a;
        scanf("%lld", &a);
        // Initialize the BITs with the initial values
        updateBIT(B1, i, a);
        updateBIT(B1, i+1, -a);
        updateBIT(B2, i, a*(i-1));
        updateBIT(B2, i+1, -a*i);
    }
    for(int i=0;i<f;i++){
        int op;
        scanf("%d", &op);
        if(op == 1){
            int l, r;
            ll k;
            scanf("%d %d %lld", &l, &r, &k);
            // Range add [l, r] += k
            updateBIT(B1, l, k);
            updateBIT(B1, r+1, -k);
            updateBIT(B2, l, k*(l-1));
            updateBIT(B2, r+1, -k*r);
        }
        else if(op == 2){
            ll k;
            scanf("%lld", &k);
            // Add k to [1,1]
            updateBIT(B1, 1, k);
            updateBIT(B1, 2, -k);
            updateBIT(B2, 1, k*0);
            updateBIT(B2, 2, -k*1);
        }
        else if(op == 3){
            ll k;
            scanf("%lld", &k);
            // Subtract k from [1,1]
            updateBIT(B1, 1, -k);
            updateBIT(B1, 2, k);
            updateBIT(B2, 1, -k*0);
            updateBIT(B2, 2, k*1);
        }
        else if(op == 4){
            int l, r;
            scanf("%d %d", &l, &r);
            // Query sum [l, r]
            ll sum_r = queryBIT(B1, r)*r - queryBIT(B2, r);
            ll sum_l_1 = queryBIT(B1, l-1)*(l-1) - queryBIT(B2, l-1);
            ll result = sum_r - sum_l_1;
            printf("%lld\n", result);
        }
        else if(op == 5){
            // Query [1,1]
            ll sum = queryBIT(B1,1)*1 - queryBIT(B2,1);
            printf("%lld\n", sum);
        }
    }
    return 0;
}