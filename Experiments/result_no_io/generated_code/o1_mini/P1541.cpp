#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF -1000000000

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    
    int *a = (int*)malloc((N+1) * sizeof(int));
    for(int i=1;i<=N;i++) scanf("%d", &a[i]);
    
    int cnt1=0, cnt2=0, cnt3=0, cnt4=0;
    for(int i=0;i<M;i++){
        int s;
        scanf("%d", &s);
        if(s==1) cnt1++;
        else if(s==2) cnt2++;
        else if(s==3) cnt3++;
        else if(s==4) cnt4++;
    }
    
    // Compute multipliers
    long long mul1 = 1;
    long long mul2 = mul1 * (N+1);
    long long mul3 = mul2 * (cnt1+1);
    long long mul4 = mul3 * (cnt2+1);
    long long mul5 = mul4 * (cnt3+1);
    
    // Total size
    long long size = (N+1) * (cnt1+1) * (cnt2+1) * (cnt3+1) * (cnt4+1);
    int *dp = (int*)malloc(size * sizeof(int));
    for(long long i=0;i<size;i++) dp[i] = INF;
    
    // Initial state
    // pos=1, c1=cnt1, c2=cnt2, c3=cnt3, c4=cnt4
    long long initial_index = 1 + cnt1 * mul1 + cnt2 * mul2 + cnt3 * mul3 + cnt4 * mul4;
    dp[initial_index] = a[1];
    
    // Iterate over all possible states
    for(int pos=1; pos<=N; pos++){
        for(int c1=0; c1<=cnt1; c1++){
            for(int c2=0; c2<=cnt2; c2++){
                for(int c3=0; c3<=cnt3; c3++){
                    for(int c4=0; c4<=cnt4; c4++){
                        long long index = pos + c1 * mul1 + c2 * mul2 + c3 * mul3 + c4 * mul4;
                        if(dp[index] == INF) continue;
                        // Try step size 1
                        if(c1 >0 && pos +1 <=N){
                            int new_c1 = c1 -1;
                            int new_c2 = c2;
                            int new_c3 = c3;
                            int new_c4 = c4;
                            int new_pos = pos +1;
                            long long new_index = new_pos + new_c1 * mul1 + new_c2 * mul2 + new_c3 * mul3 + new_c4 * mul4;
                            if(dp[new_index] < dp[index] + a[new_pos]){
                                dp[new_index] = dp[index] + a[new_pos];
                            }
                        }
                        // Try step size 2
                        if(c2 >0 && pos +2 <=N){
                            int new_c1 = c1;
                            int new_c2 = c2 -1;
                            int new_c3 = c3;
                            int new_c4 = c4;
                            int new_pos = pos +2;
                            long long new_index = new_pos + new_c1 * mul1 + new_c2 * mul2 + new_c3 * mul3 + new_c4 * mul4;
                            if(dp[new_index] < dp[index] + a[new_pos]){
                                dp[new_index] = dp[index] + a[new_pos];
                            }
                        }
                        // Try step size 3
                        if(c3 >0 && pos +3 <=N){
                            int new_c1 = c1;
                            int new_c2 = c2;
                            int new_c3 = c3 -1;
                            int new_c4 = c4;
                            int new_pos = pos +3;
                            long long new_index = new_pos + new_c1 * mul1 + new_c2 * mul2 + new_c3 * mul3 + new_c4 * mul4;
                            if(dp[new_index] < dp[index] + a[new_pos]){
                                dp[new_index] = dp[index] + a[new_pos];
                            }
                        }
                        // Try step size 4
                        if(c4 >0 && pos +4 <=N){
                            int new_c1 = c1;
                            int new_c2 = c2;
                            int new_c3 = c3;
                            int new_c4 = c4 -1;
                            int new_pos = pos +4;
                            long long new_index = new_pos + new_c1 * mul1 + new_c2 * mul2 + new_c3 * mul3 + new_c4 * mul4;
                            if(dp[new_index] < dp[index] + a[new_pos]){
                                dp[new_index] = dp[index] + a[new_pos];
                            }
                        }
                    }
                }
            }
        }
    }
    
    // The answer is dp[N][0][0][0][0]
    long long final_index = N + 0 * mul1 + 0 * mul2 + 0 * mul3 + 0 * mul4;
    printf("%d\n", dp[final_index]);
    
    free(a);
    free(dp);
    return 0;
}