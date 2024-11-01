#include <stdio.h>
#include <string.h>

#define MAX_STEP 4
#define MAX_COUNT 40
#define BASE 41
#define MAX_INDEX 2825761
#define NEG_INF -1

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    
    int a[N+1];
    for(int i=1;i<=N;i++) scanf("%d", &a[i]);
    
    int b[M];
    int count1=0, count2=0, count3=0, count4=0;
    for(int i=0;i<M;i++){
        scanf("%d", &b[i]);
        if(b[i]==1) count1++;
        else if(b[i]==2) count2++;
        else if(b[i]==3) count3++;
        else if(b[i]==4) count4++;
    }
    
    // Initialize DP array
    // Using short since max score is 120*100 +100 =12100 < 32767
    short *dp = (short*)malloc(sizeof(short)*MAX_INDEX);
    for(int i=0;i<MAX_INDEX;i++) dp[i] = -1;
    
    // Starting state: c1=0, c2=0, c3=0, c4=0
    int start_index = 0;
    dp[start_index] = a[1];
    
    // Iterate through all possible counts
    for(int c4_used=0; c4_used<=count4; c4_used++){
        for(int c3_used=0; c3_used<=count3; c3_used++){
            for(int c2_used=0; c2_used<=count2; c2_used++){
                for(int c1_used=0; c1_used<=count1; c1_used++){
                    // Compute current index
                    int index = c1_used + c2_used*BASE + c3_used*BASE*BASE + c4_used*BASE*BASE*BASE;
                    if(dp[index]==-1) continue;
                    
                    // Current position
                    int pos = 1 + c1_used*1 + c2_used*2 + c3_used*3 + c4_used*4;
                    
                    // Try all step types
                    // Step 1
                    if(c1_used < count1){
                        int new_pos = pos +1;
                        if(new_pos <= N){
                            int new_c1 = c1_used +1;
                            int new_c2 = c2_used;
                            int new_c3 = c3_used;
                            int new_c4 = c4_used;
                            int new_index = new_c1 + new_c2*BASE + new_c3*BASE*BASE + new_c4*BASE*BASE*BASE;
                            int new_score = dp[index] + a[new_pos];
                            if(new_score > dp[new_index]){
                                dp[new_index] = new_score;
                            }
                        }
                    }
                    // Step 2
                    if(c2_used < count2){
                        int new_pos = pos +2;
                        if(new_pos <= N){
                            int new_c1 = c1_used;
                            int new_c2 = c2_used +1;
                            int new_c3 = c3_used;
                            int new_c4 = c4_used;
                            int new_index = new_c1 + new_c2*BASE + new_c3*BASE*BASE + new_c4*BASE*BASE*BASE;
                            int new_score = dp[index] + a[new_pos];
                            if(new_score > dp[new_index]){
                                dp[new_index] = new_score;
                            }
                        }
                    }
                    // Step 3
                    if(c3_used < count3){
                        int new_pos = pos +3;
                        if(new_pos <= N){
                            int new_c1 = c1_used;
                            int new_c2 = c2_used;
                            int new_c3 = c3_used +1;
                            int new_c4 = c4_used;
                            int new_index = new_c1 + new_c2*BASE + new_c3*BASE*BASE + new_c4*BASE*BASE*BASE;
                            int new_score = dp[index] + a[new_pos];
                            if(new_score > dp[new_index]){
                                dp[new_index] = new_score;
                            }
                        }
                    }
                    // Step 4
                    if(c4_used < count4){
                        int new_pos = pos +4;
                        if(new_pos <= N){
                            int new_c1 = c1_used;
                            int new_c2 = c2_used;
                            int new_c3 = c3_used;
                            int new_c4 = c4_used +1;
                            int new_index = new_c1 + new_c2*BASE + new_c3*BASE*BASE + new_c4*BASE*BASE*BASE;
                            int new_score = dp[index] + a[new_pos];
                            if(new_score > dp[new_index]){
                                dp[new_index] = new_score;
                            }
                        }
                    }
                }
            }
        }
    }
    
    // Compute final index
    int final_index = count1 + count2*BASE + count3*BASE*BASE + count4*BASE*BASE*BASE;
    printf("%d\n", dp[final_index]);
    
    free(dp);
    return 0;
}