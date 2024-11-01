#include <stdio.h>
#include <string.h>

#define MAXN 1000
#define MAXM 200
#define MAXK 200
#define MOD 1000000007

unsigned long long dp_current[201][201];
unsigned long long dp_next_arr[201][201];
char A_str[MAXN + 1];
char B_str[MAXM + 1];
int match_arr[MAXN][MAXM];

int main(){
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    scanf("%s", A_str);
    scanf("%s", B_str);
    
    // Precompute match array
    for(int i = n -1; i >=0; i--){
        for(int j = m -1; j >=0; j--){
            if(A_str[i] == B_str[j]){
                if(i+1 <n && j+1 <m){
                    match_arr[i][j] = match_arr[i+1][j+1] +1;
                    if(match_arr[i][j] > m - j){
                        match_arr[i][j] = m - j;
                    }
                }
                else{
                    match_arr[i][j] =1;
                }
            }
            else{
                match_arr[i][j] =0;
            }
        }
    }
    
    // Initialize dp_current
    memset(dp_current, 0, sizeof(dp_current));
    dp_current[0][0] =1;
    
    // Iterate over A
    for(int i =0; i <n; i++){
        memset(dp_next_arr, 0, sizeof(dp_next_arr));
        for(int j =0; j <=m; j++){
            for(int l =0; l <=k; l++){
                if(dp_current[j][l] ==0) continue;
                // Skip A[i]
                dp_next_arr[j][l] = (dp_next_arr[j][l] + dp_current[j][l]) % MOD;
                // Try to match
                if(j <m && l <k && match_arr[i][j] >0){
                    int t_max = match_arr[i][j];
                    if(t_max > m - j){
                        t_max = m - j;
                    }
                    for(int t=1; t <=t_max; t++){
                        unsigned long long add = dp_current[j][l];
                        dp_next_arr[j +t][l +1] = (dp_next_arr[j +t][l +1] + add) % MOD;
                    }
                }
            }
        }
        // Swap dp_current and dp_next_arr
        for(int j =0; j <=m; j++){
            for(int l =0; l <=k; l++){
                dp_current[j][l] = dp_next_arr[j][l];
            }
        }
    }
    
    printf("%llu\n", dp_current[m][k] % MOD);
    return 0;
}