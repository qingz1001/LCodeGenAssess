#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

#define MAX 100005

ll BIT[MAX];
int n;

// Function to update the BIT
void updateBIT(int idx, ll val){
    while(idx <= n){
        BIT[idx] += val;
        idx += idx & -idx;
    }
}

// Function to get prefix sum up to idx
ll queryBIT(int idx){
    ll res = 0;
    while(idx > 0){
        res += BIT[idx];
        idx -= idx & -idx;
    }
    return res;
}

int main(){
    int w;
    char op;
    int a, b;
    ll val;
    
    // Read n
    if(scanf("%d", &n)!=1){
        return 0;
    }
    
    // Read w
    if(scanf("%d", &w)!=1){
        return 0;
    }
    
    for(int i = 0; i < w; i++){
        // Read operation type
        if(scanf(" %c", &op)!=1){
            return 0;
        }
        
        if(op == 'x'){
            // Read a and b for update
            if(scanf("%d %lld", &a, &val)!=2){
                return 0;
            }
            updateBIT(a, val);
        }
        else if(op == 'y'){
            // Read a and b for query
            if(scanf("%d %d", &a, &b)!=2){
                return 0;
            }
            ll res = queryBIT(b) - queryBIT(a-1);
            printf("%lld\n", res);
        }
    }
    
    return 0;
}