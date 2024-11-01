#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAXN 4000005
#define MOD 1000000007

typedef long long ll;

// Binary Indexed Tree (Fenwick Tree)
typedef struct {
    ll *tree;
    int size;
} BIT;

// Initialize BIT
BIT* init_BIT(int size){
    BIT *b = (BIT*)malloc(sizeof(BIT));
    b->size = size;
    b->tree = (ll*)calloc(size + 2, sizeof(ll));
    return b;
}

// Update BIT at position idx with value delta
void update_BIT(BIT *b, int idx, ll delta){
    while(idx <= b->size){
        b->tree[idx] += delta;
        idx += idx & -idx;
    }
}

// Query BIT prefix sum up to idx
ll query_BIT(BIT *b, int idx){
    ll res = 0;
    while(idx > 0){
        res += b->tree[idx];
        idx -= idx & -idx;
    }
    return res;
}

// Compute Möbius function up to n
void compute_mobius(int n, int *mu){
    memset(mu, 0, sizeof(int)*(n+1));
    mu[0] = 0;
    mu[1] = 1;
    for(int i=1;i<=n;i++){
        if(mu[i] != 0){
            for(int j=2*i; j<=n; j+=i){
                if(j % (i*i) == 0){
                    mu[j] = 0;
                }
                else{
                    mu[j] -= mu[i];
                }
            }
        }
    }
    // Correct the Möbius function
    for(int i=2;i<=n;i++) {
        if(mu[i] == 0){
            // already zero
            continue;
        }
        // if mu[i] is not set by above, set to 1 or -1
        if(mu[i] != 1 && mu[i] != -1){
            // compute correctly
            int cnt = 0;
            int square = 0;
            int x = i;
            for(int p=2; p*p <=x; p++){
                if(x % p ==0){
                    cnt++;
                    if(x % (p*p)==0){
                        square =1;
                        break;
                    }
                    while(x % p ==0){
                        x /=p;
                    }
                }
            }
            if(x >1){
                cnt++;
            }
            if(square){
                mu[i]=0;
            }
            else{
                mu[i]=(cnt%2)? -1:1;
            }
        }
    }
}

// Compute gcd
int gcd_func(int a, int b){
    while(b){
        int tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

int main(){
    int m, n;
    scanf("%d %d", &m, &n);
    
    // Compute Möbius function
    int *mu = (int*)malloc(sizeof(int)*(n+1));
    for(int i=0;i<=n;i++) mu[i]=1;
    mu[0]=0;
    for(int i=2;i<=n;i++){
        if(mu[i]==1 || mu[i]==-1){
            for(int j=2*i; j<=n; j+=i){
                mu[j] -= mu[i];
            }
        }
    }
    // Correct Möbius function
    for(int i=2;i<=n;i++) {
        if(mu[i] >1){
            mu[i]=0;
        }
        else if(mu[i]<-1){
            mu[i]=0;
        }
    }
    
    // Precompute S[m]
    ll *S = (ll*)calloc(n+1, sizeof(ll));
    for(int d=1; d<=n; d++){
        if(mu[d]==0) continue;
        for(int k=1; d*k <=n; k++){
            ll temp = k;
            ll sum = temp * (temp +1) /2;
            S[d*k] += mu[d] * sum * sum;
        }
    }
    
    // Initialize c(d) =1
    ll *c = (ll*)malloc(sizeof(ll)*(n+1));
    for(int i=0;i<=n;i++) c[i]=1;
    
    // Initialize BIT with c(d)*d =d
    BIT *bit = init_BIT(n);
    for(int i=1;i<=n;i++) {
        update_BIT(bit, i, i);
    }
    
    // Process operations
    for(int op=0; op<m; op++){
        int a, b, k;
        ll x;
        scanf("%d %d %lld %d", &a, &b, &x, &k);
        int d = gcd_func(a, b);
        ll new_c = (x * (ll)d) / ((ll)a * b);
        ll delta = new_c * d - c[d] * d;
        c[d] = new_c;
        update_BIT(bit, d, delta);
        
        // Calculate the sum
        ll total =0;
        int m_val =1;
        while(m_val <=k){
            ll t = k / m_val;
            int m_low = k / (t +1) +1;
            int m_high = k / t;
            if(m_high >k) m_high =k;
            if(m_low < m_val) m_low = m_val;
            if(m_low > m_high){
                m_val = m_high +1;
                continue;
            }
            ll sum_d = query_BIT(bit, m_high) - query_BIT(bit, m_low -1);
            total += (sum_d % MOD) * (S[t] % MOD);
            total %= MOD;
            m_val = m_high +1;
        }
        printf("%lld\n", total);
    }
    
    // Free memory
    free(mu);
    free(S);
    free(c);
    free(bit->tree);
    free(bit);
    
    return 0;
}