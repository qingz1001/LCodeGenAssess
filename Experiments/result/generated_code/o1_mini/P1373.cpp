#include <stdio.h>
#include <stdlib.h>
#define MOD 1000000007

int main(){
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    int *magic = (int*)malloc(n * m * sizeof(int));
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            scanf("%d", &magic[i*m + j]);
        }
    }

    // Calculate the size for each cell's state
    int state_size = 2 * (k+1) * (k+1);
    // Allocate memory for two rows
    unsigned int *dp_prev = (unsigned int*)calloc(m * state_size, sizeof(unsigned int));
    unsigned int *dp_current = (unsigned int*)calloc(m * state_size, sizeof(unsigned int));

    long long res = 0;

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            // Calculate index for current cell in dp_current
            // Reset dp_current[j] to 0 by setting all states to 0
            for(int idx=0; idx < state_size; idx++) {
                dp_current[j * state_size + idx] = 0;
            }

            // Start a new path at (i,j): p=0, a=magic[i][j], u=0
            int a_new = magic[i*m + j] % (k+1);
            int u_new = 0;
            int p_new = 0;
            dp_current[j * state_size + p_new*(k+1)*(k+1) + a_new*(k+1) + u_new] = (dp_current[j * state_size + p_new*(k+1)*(k+1) + a_new*(k+1) + u_new] + 1) % MOD;

            // From up
            if(i > 0){
                for(int p_prev=0; p_prev<2; p_prev++){
                    for(int a_prev=0; a_prev<=k; a_prev++){
                        for(int u_prev=0; u_prev<=k; u_prev++){
                            unsigned int cnt = dp_prev[j * state_size + p_prev*(k+1)*(k+1) + a_prev*(k+1) + u_prev];
                            if(cnt ==0) continue;
                            int p_new_step, a_new_step, u_new_step;
                            if(p_prev ==0){
                                p_new_step =1;
                                a_new_step = a_prev;
                                u_new_step = (u_prev + magic[i*m + j]) % (k+1);
                            }
                            else{
                                p_new_step =0;
                                a_new_step = (a_prev + magic[i*m + j]) % (k+1);
                                u_new_step = u_prev;
                            }
                            int idx_new = p_new_step*(k+1)*(k+1) + a_new_step*(k+1) + u_new_step;
                            dp_current[j * state_size + idx_new] = (dp_current[j * state_size + idx_new] + cnt) % MOD;
                        }
                    }
                }
            }

            // From left
            if(j >0){
                for(int p_prev=0; p_prev<2; p_prev++){
                    for(int a_prev=0; a_prev<=k; a_prev++){
                        for(int u_prev=0; u_prev<=k; u_prev++){
                            unsigned int cnt = dp_current[(j-1) * state_size + p_prev*(k+1)*(k+1) + a_prev*(k+1) + u_prev];
                            if(cnt ==0) continue;
                            int p_new_step, a_new_step, u_new_step;
                            if(p_prev ==0){
                                p_new_step =1;
                                a_new_step = a_prev;
                                u_new_step = (u_prev + magic[i*m + j]) % (k+1);
                            }
                            else{
                                p_new_step =0;
                                a_new_step = (a_prev + magic[i*m + j]) % (k+1);
                                u_new_step = u_prev;
                            }
                            int idx_new = p_new_step*(k+1)*(k+1) + a_new_step*(k+1) + u_new_step;
                            dp_current[j * state_size + idx_new] = (dp_current[j * state_size + idx_new] + cnt) % MOD;
                        }
                    }
                }
            }

            // Accumulate the result: paths ending at (i,j) with p=1 and a_val == u_val
            for(int a=0; a<=k; a++){
                int idx_acc = 1*(k+1)*(k+1) + a*(k+1) + a;
                res = (res + dp_current[j * state_size + idx_acc]) % MOD;
            }
        }
        // Swap dp_prev and dp_current
        unsigned int *temp = dp_prev;
        dp_prev = dp_current;
        dp_current = temp;
    }

    printf("%lld\n", res);

    free(magic);
    free(dp_prev);
    free(dp_current);
    return 0;
}