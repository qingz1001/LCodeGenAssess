#include <stdio.h>
#include <string.h>

#define MAX_ROW 15
#define MAX_COL 15
#define MAX_CONFIG 32768
#define MOD 10007

int main(){
    int n, m;
    scanf("%d %d", &n, &m);
    char grid[MAX_ROW][MAX_COL+1];
    for(int i=0;i<n;i++) {
        scanf("%s", grid[i]);
    }
    // For each row, store mask0 and mask1
    unsigned short mask0[n];
    unsigned short mask1[n];
    for(int i=0;i<n;i++){
        mask0[i]=0;
        mask1[i]=0;
        for(int j=0;j<m;j++){
            if(grid[i][j]=='0') mask0[i] |= (1<<j);
            else if(grid[i][j]=='1') mask1[i] |= (1<<j);
        }
    }
    // For each row, store valid configurations
    unsigned short valid_configs[n][MAX_CONFIG];
    int cnt[n];
    for(int i=0;i<n;i++){
        cnt[i]=0;
        for(unsigned int config=0; config<(1U<<m); config++){
            if( (config & mask0[i]) !=0 ) continue;
            if( (config & mask1[i]) != mask1[i] ) continue;
            if( (config & (config <<1)) !=0 ) continue;
            valid_configs[i][cnt[i]++] = config;
        }
    }
    // Initialize DP
    int dp_prev[MAX_CONFIG];
    int dp_curr_arr[MAX_CONFIG];
    memset(dp_prev, 0, sizeof(dp_prev));
    dp_prev[0] =1;
    for(int i=0;i<n;i++){
        memset(dp_curr_arr, 0, sizeof(dp_curr_arr));
        for(int pc=0; pc<cnt[i==0?0:i-1]; pc++){
            // Not used since we iterate current configs first
        }
        for(int c=0; c<cnt[i]; c++){
            unsigned short curr = valid_configs[i][c];
            for(int p=0; p<(i==0?1:cnt[i-1]); p++){
                unsigned short prev = (i==0)?0:valid_configs[i-1][p];
                if( (curr & prev) ==0 ){
                    dp_curr_arr[c] += (i==0?dp_prev[0]:dp_prev[prev]);
                    if(dp_curr_arr[c] >= MOD) dp_curr_arr[c] -= MOD;
                }
            }
        }
        // Update dp_prev
        memset(dp_prev, 0, sizeof(dp_prev));
        for(int c=0; c<cnt[i]; c++){
            unsigned short curr = valid_configs[i][c];
            dp_prev[curr] = dp_curr_arr[c] % MOD;
        }
    }
    // Sum all dp_prev
    int result=0;
    for(int c=0; c<cnt[n-1]; c++){
        result = (result + dp_prev[valid_configs[n-1][c]]) % MOD;
    }
    printf("%d\n", result);
    return 0;
}