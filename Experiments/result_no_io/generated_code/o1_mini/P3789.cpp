#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MOD 998244353
typedef long long ll;

ll add_mod(ll a, ll b){
    a += b;
    if(a >= MOD) a -= MOD;
    return a;
}

typedef struct {
    ll *cb;
    ll *cw;
    ll *cg;
} State;

int main(){
    ll n, k;
    scanf("%lld %lld", &n, &k);
    
    // Initialize transition matrices for each bit
    // Each transition is a state with cb, cw, cg
    // Precompute powers of transitions
    // Initialize base transition
    State trans;
    trans.cb = (ll*)calloc(k+1, sizeof(ll));
    trans.cw = (ll*)calloc(k+1, sizeof(ll));
    trans.cg = (ll*)calloc(k+1, sizeof(ll));
    // Transition step: one move
    // From black:
    //   to white: weight +1
    //   to gray: weight
    // From white:
    //   to black: weight +1
    //   to gray: weight
    // From gray:
    //   to black: weight
    //   to white: weight
    //   to gray: weight
    // So transition matrices:
    // cb' = cw + cg
    // cw' = cb + cg
    // cg' = cb + cw + cg
    // But need to track weights
    // Instead, handle transitions manually
    // We will handle multiplication later
    // Initialize identity
    State res;
    res.cb = (ll*)calloc(k+1, sizeof(ll));
    res.cw = (ll*)calloc(k+1, sizeof(ll));
    res.cg = (ll*)calloc(k+1, sizeof(ll));
    res.cb[0] = 1;
    res.cw[0] = 1;
    res.cg[0] = 1;
    
    // Precompute transition steps
    // We will use binary exponentiation
    while(n > 0){
        if(n & 1){
            // Multiply res with trans
            // New temporary arrays
            ll *new_cb = (ll*)calloc(k+1, sizeof(ll));
            ll *new_cw = (ll*)calloc(k+1, sizeof(ll));
            ll *new_cg = (ll*)calloc(k+1, sizeof(ll));
            // res.cb * transition to white and gray
            for(ll w = 0; w <= k; w++){
                if(res.cb[w] == 0) continue;
                // To white: weight +1
                if(w + 1 <= k){
                    new_cw[w+1] = add_mod(new_cw[w+1], res.cb[w]);
                }
                // To gray: weight
                new_cg[w] = add_mod(new_cg[w], res.cb[w]);
            }
            // res.cw * transition to black and gray
            for(ll w = 0; w <= k; w++){
                if(res.cw[w] == 0) continue;
                // To black: weight +1
                if(w + 1 <= k){
                    new_cb[w+1] = add_mod(new_cb[w+1], res.cw[w]);
                }
                // To gray: weight
                new_cg[w] = add_mod(new_cg[w], res.cw[w]);
            }
            // res.cg * transition to black, white, gray
            for(ll w = 0; w <= k; w++){
                if(res.cg[w] == 0) continue;
                // To black: weight
                new_cb[w] = add_mod(new_cb[w], res.cg[w]);
                // To white: weight
                new_cw[w] = add_mod(new_cw[w], res.cg[w]);
                // To gray: weight
                new_cg[w] = add_mod(new_cg[w], res.cg[w]);
            }
            // Update res
            // Add new_cb, new_cw, new_cg to res
            for(ll w = 0; w <= k; w++){
                res.cb[w] = new_cb[w];
                res.cw[w] = new_cw[w];
                res.cg[w] = new_cg[w];
            }
            free(new_cb);
            free(new_cw);
            free(new_cg);
        }
        n >>= 1;
        if(n == 0) break;
        // Square the transition
        // Similar to multiplying trans with itself
        // New temporary transition
        ll *t_cb = (ll*)calloc(k+1, sizeof(ll));
        ll *t_cw = (ll*)calloc(k+1, sizeof(ll));
        ll *t_cg = (ll*)calloc(k+1, sizeof(ll));
        // trans.cb to white and gray
        for(ll w = 0; w <= k; w++){
            if(trans.cb[w] == 0) continue;
            // To white: weight +1
            if(w + 1 <= k){
                t_cw[w+1] = add_mod(t_cw[w+1], trans.cb[w]);
            }
            // To gray: weight
            t_cg[w] = add_mod(t_cg[w], trans.cb[w]);
        }
        // trans.cw to black and gray
        for(ll w = 0; w <= k; w++){
            if(trans.cw[w] == 0) continue;
            // To black: weight +1
            if(w + 1 <= k){
                t_cb[w+1] = add_mod(t_cb[w+1], trans.cw[w]);
            }
            // To gray: weight
            t_cg[w] = add_mod(t_cg[w], trans.cw[w]);
        }
        // trans.cg to black, white, gray
        for(ll w = 0; w <= k; w++){
            if(trans.cg[w] == 0) continue;
            // To black: weight
            t_cb[w] = add_mod(t_cb[w], trans.cg[w]);
            // To white: weight
            t_cw[w] = add_mod(t_cw[w], trans.cg[w]);
            // To gray: weight
            t_cg[w] = add_mod(t_cg[w], trans.cg[w]);
        }
        // Update trans
        for(ll w = 0; w <= k; w++){
            trans.cb[w] = t_cb[w];
            trans.cw[w] = t_cw[w];
            trans.cg[w] = t_cg[w];
        }
        free(t_cb);
        free(t_cw);
        free(t_cg);
    }
    // Now, res has the final counts
    // Sum over cb, cw, cg
    ll *final = (ll*)calloc(k+1, sizeof(ll));
    for(ll w = 0; w <= k; w++){
        final[w] = add_mod(res.cb[w], res.cw[w]);
        final[w] = add_mod(final[w], res.cg[w]);
    }
    // Print from 0 to k
    for(ll w = 0; w <= k; w++){
        printf("%lld%c", final[w], (w == k)? '\n' : ' ');
    }
    // Free memory
    free(trans.cb);
    free(trans.cw);
    free(trans.cg);
    free(res.cb);
    free(res.cw);
    free(res.cg);
    free(final);
    return 0;
}