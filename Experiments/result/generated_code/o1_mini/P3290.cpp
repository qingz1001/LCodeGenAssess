#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007

typedef long long ll;

// Fast exponentiation: computes (base^exp) % MOD
ll power(ll base, ll exp) {
    ll result = 1;
    base %= MOD;
    while(exp > 0){
        if(exp & 1){
            result = result * base % MOD;
        }
        base = base * base % MOD;
        exp >>= 1;
    }
    return result;
}

int main(){
    int n, m, c, q;
    scanf("%d %d %d %d", &n, &m, &c, &q);
    
    char templates[q][2][7];
    for(int i=0;i<q;i++){
        scanf("%s", templates[i][0]);
        scanf("%s", templates[i][1]);
    }
    
    // Calculate total number of states: 3^m
    ll num_states = 1;
    for(int i=0;i<m;i++) num_states *=3;
    
    // Allocate memory for state representations
    char **state_rows = (char **)malloc(num_states * sizeof(char *));
    for(ll s=0;s<num_states;s++){
        state_rows[s] = (char *)malloc(m * sizeof(char));
        ll tmp = s;
        for(int j=m-1;j>=0;j--){
            int val = tmp % 3;
            tmp /= 3;
            if(val == 0) state_rows[s][j] = 'W';
            else if(val == 1) state_rows[s][j] = 'B';
            else state_rows[s][j] = 'X';
        }
    }
    
    // Precompute total number of grids
    ll total = power(3, (ll)n * m);
    
    for(int qid=0; qid<q; qid++){
        char temp0[7], temp1[7];
        strcpy(temp0, templates[qid][0]);
        strcpy(temp1, templates[qid][1]);
        
        // Initialize DP arrays
        ll *dp_prev = (ll *)calloc(num_states, sizeof(ll));
        ll *dp_curr = (ll *)calloc(num_states, sizeof(ll));
        
        // Base case: first row can be any state
        for(ll s=0;s<num_states;s++) dp_prev[s] = 1;
        
        // Iterate through each row
        for(int row=1; row<n; row++){
            memset(dp_curr, 0, num_states * sizeof(ll));
            for(ll ps=0; ps<num_states; ps++){
                if(dp_prev[ps] == 0) continue;
                for(ll cs=0; cs<num_states; cs++){
                    int match = 0;
                    for(int start=0; start <= m - c; start++){
                        int flag = 1;
                        for(int k=0; k<c; k++){
                            char t0 = temp0[k];
                            char t1 = temp1[k];
                            char g0 = state_rows[ps][start + k];
                            char g1 = state_rows[cs][start + k];
                            if(t0 != 'X' && t0 != g0){
                                flag = 0;
                                break;
                            }
                            if(t1 != 'X' && t1 != g1){
                                flag = 0;
                                break;
                            }
                        }
                        if(flag){
                            match = 1;
                            break;
                        }
                    }
                    if(!match){
                        dp_curr[cs] = (dp_curr[cs] + dp_prev[ps]) % MOD;
                    }
                }
            }
            // Swap dp_prev and dp_curr
            ll *temp_ptr = dp_prev;
            dp_prev = dp_curr;
            dp_curr = temp_ptr;
        }
        
        // Calculate number of grids with no match
        ll no_match = 0;
        for(ll s=0; s<num_states; s++) no_match = (no_match + dp_prev[s]) % MOD;
        
        // Calculate the answer
        ll ans = (total - no_match + MOD) % MOD;
        printf("%lld\n", ans);
        
        // Free DP arrays
        free(dp_prev);
        free(dp_curr);
    }
    
    // Free state representations
    for(ll s=0;s<num_states;s++) free(state_rows[s]);
    free(state_rows);
    
    return 0;
}