#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_SUM 1600
#define WORDS 26

typedef unsigned long long ull;

int main(){
    int n;
    scanf("%d", &n);
    if(n <3){
        printf("-1");
        return 0;
    }
    int l[n];
    int S=0;
    for(int i=0;i<n;i++){
        scanf("%d", &l[i]);
        S += l[i];
    }
    // Initialize dp
    ull dp[MAX_SUM+1][WORDS];
    memset(dp, 0, sizeof(dp));
    dp[0][0] |= 1ULL;
    for(int i=0;i<n;i++){
        int li = l[i];
        for(int a=S; a>=0; a--){
            if(a + li > S) continue;
            // Assign to A: dp[a + li] |= dp[a]
            for(int w=0; w<WORDS; w++) {
                dp[a + li][w] |= dp[a][w];
            }
            // Assign to B: shifted dp[a] by li bits and OR to dp[a]
            ull shifted[WORDS] = {0};
            int bits = li;
            for(int w=WORDS-1; w>=0; w--){
                if(w ==0){
                    shifted[w] |= (dp[a][w] << bits);
                }
                else{
                    shifted[w] |= (dp[a][w] << bits) | (dp[a][w-1] >> (64 - bits));
                }
            }
            for(int w=0; w<WORDS; w++) {
                dp[a][w] |= shifted[w];
            }
        }
    }
    double max_area = -1.0;
    for(int a=1; a < S/2; a++){
        // Calculate minimum b
        double half_S = S / 2.0;
        int min_b = (int)ceil(half_S - a + 1e-9);
        if(min_b <1) min_b =1;
        for(int b = min_b; b < S/2; b++){
            if(a + b <= half_S) continue;
            // Check if dp[a][b] is set
            int word_idx = b / 64;
            int bit_idx = b % 64;
            if( (dp[a][word_idx] >> bit_idx) &1 ){
                int c = S - a - b;
                // Check c < S/2
                if(c >= half_S) continue;
                double p = S / 2.0;
                double area = sqrt(p * (p - a) * (p - b) * (p - c));
                if(area > max_area){
                    max_area = area;
                }
            }
        }
    }
    if(max_area <0){
        printf("-1");
    }
    else{
        long long result = (long long)(max_area * 100.0);
        printf("%lld", result);
    }
}