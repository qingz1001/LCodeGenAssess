#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007

typedef long long ll;

int main(){
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    
    // Allocate grid
    int **grid = (int **)malloc(n * sizeof(int *));
    for(int i=0;i<n;i++){
        grid[i] = (int *)malloc(m * sizeof(int));
        for(int j=0;j<m;j++){
            scanf("%d", &grid[i][j]);
        }
    }
    
    // Allocate DP arrays
    ll *dp_prev = (ll *)calloc(m * 2 * (k+1) * (k+1), sizeof(ll));
    ll *dp_curr = (ll *)calloc(m * 2 * (k+1) * (k+1), sizeof(ll));
    
    ll result =0;
    
    for(int i=0;i<n;i++){
        // Reset dp_curr
        memset(dp_curr, 0, m * 2 * (k+1) * (k+1) * sizeof(ll));
        for(int j=0; j<m; j++){
            int magic = grid[i][j];
            int sa_init = magic % (k+1);
            int su_init =0;
            // Start a new path at (i,j)
            int idx = j*2*(k+1)*(k+1) + 0*(k+1)*(k+1) + sa_init*(k+1) + su_init;
            dp_curr[idx] = (dp_curr[idx] +1) % MOD;
            
            // From top
            if(i >0){
                ll *src = dp_prev + j*2*(k+1)*(k+1);
                for(int p=0; p<2; p++){
                    for(int sa=0; sa<=k; sa++){
                        for(int su=0; su<=k; su++){
                            ll cnt = src[p*(k+1)*(k+1) + sa*(k+1) + su];
                            if(cnt ==0) continue;
                            int new_p, new_sa, new_su;
                            if(p ==0){
                                new_p =1;
                                new_su = (su + magic) % (k+1);
                                new_sa = sa;
                            }
                            else{
                                new_p =0;
                                new_sa = (sa + magic) % (k+1);
                                new_su = su;
                            }
                            int dest_idx = j*2*(k+1)*(k+1) + new_p*(k+1)*(k+1) + new_sa*(k+1) + new_su;
                            dp_curr[dest_idx] = (dp_curr[dest_idx] + cnt) % MOD;
                        }
                    }
                }
            }
            
            // From left
            if(j >0){
                ll *src = dp_curr + (j-1)*2*(k+1)*(k+1);
                for(int p=0; p<2; p++){
                    for(int sa=0; sa<=k; sa++){
                        for(int su=0; su<=k; su++){
                            ll cnt = src[p*(k+1)*(k+1) + sa*(k+1) + su];
                            if(cnt ==0) continue;
                            int new_p, new_sa, new_su;
                            if(p ==0){
                                new_p =1;
                                new_su = (su + magic) % (k+1);
                                new_sa = sa;
                            }
                            else{
                                new_p =0;
                                new_sa = (sa + magic) % (k+1);
                                new_su = su;
                            }
                            int dest_idx = j*2*(k+1)*(k+1) + new_p*(k+1)*(k+1) + new_sa*(k+1) + new_su;
                            dp_curr[dest_idx] = (dp_curr[dest_idx] + cnt) % MOD;
                        }
                    }
                }
            }
            
            // Accumulate result
            ll *current = dp_curr + j*2*(k+1)*(k+1);
            for(int su=0; su<=k; su++){
                ll cnt = current[1*(k+1)*(k+1) + su*(k+1) + su];
                if(cnt >0){
                    result = (result + cnt) % MOD;
                }
            }
        }
        // Swap dp_prev and dp_curr
        ll *temp = dp_prev;
        dp_prev = dp_curr;
        dp_curr = temp;
    }
    
    printf("%lld\n", result);
    
    // Free memory
    for(int i=0;i<n;i++) free(grid[i]);
    free(grid);
    free(dp_prev);
    free(dp_curr);
    
    return 0;
}