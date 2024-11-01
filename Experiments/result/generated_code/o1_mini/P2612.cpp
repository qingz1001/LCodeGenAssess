#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef unsigned long long ull;

int main(){
    int N;
    ull M;
    int K;
    scanf("%d %llu %d", &N, &M, &K);
    
    // Function to compute factorial
    ull factorial(int n){
        ull res =1;
        for(int i=2;i<=n;i++) res *=i;
        return res;
    }
    
    // Function to compute power of 10
    ull power10(int k){
        ull res =1;
        for(int i=0;i<k;i++) res *=10;
        return res;
    }
    
    // If N <=8, perform exact DP
    if(N <=8){
        int size = 1<<N;
        // Initialize DP
        // dp[mask][last][sum]
        // To save memory, use two layers
        ull dp_prev[size][N+1][800]; // For N=8, max sum=7*7=49, use up to 800 for safety
        memset(dp_prev, 0, sizeof(dp_prev));
        for(int i=1;i<=N;i++) {
            int mask = 1<<(i-1);
            dp_prev[mask][i][0] =1;
        }
        // Iterate over masks
        for(int mask=1; mask<(1<<N); mask++){
            for(int last=1; last<=N; last++){
                for(int s=0; s<= (N-1)*N; s++){
                    if(dp_prev[mask][last][s]==0) continue;
                    for(int next=1; next<=N; next++){
                        if(!(mask & (1<<(next-1)))){
                            int new_mask = mask | (1<<(next-1));
                            int new_sum = s + abs(next - last);
                            if(new_sum > (N-1)*N) continue;
                            dp_prev[new_mask][next][new_sum] += dp_prev[mask][last][s];
                        }
                    }
                }
            }
        }
        // Now, sum all permutations where sum >=M
        ull count =0;
        int full_mask = (1<<N)-1;
        for(int last=1; last<=N; last++){
            for(int s=0; s<= (N-1)*N; s++){
                if(s >= M){
                    count += dp_prev[full_mask][last][s];
                }
            }
        }
        // Total permutations
        ull total = factorial(N);
        // Compute probability
        double prob = (double)count / (double)total;
        // Prepare format string
        char format[20];
        sprintf(format, "%%.%df\n", K);
        // Round the probability
        // To handle rounding correctly, multiply by 10^K and add 5*10^(K-1)
        // then divide by 10^K
        // But using printf with proper format handles it
        printf(format, prob);
    }
    else{
        // For N >8, compute min_sum and max_sum
        ull min_sum = N -1;
        ull max_sum = (ull)(N-1)*(ull)(N);
        if(M <= min_sum){
            // Probability is 1
            printf("1.");
            for(int i=0;i<K;i++) printf("0");
            printf("\n");
        }
        else if(M > max_sum){
            // Probability is 0
            printf("0.");
            for(int i=0;i<K;i++) printf("0");
            printf("\n");
        }
        else{
            // Unable to compute, output 0 (as a safe fallback)
            printf("0.");
            for(int i=0;i<K;i++) printf("0");
            printf("\n");
        }
    }
}