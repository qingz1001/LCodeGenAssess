#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef unsigned long long ull;

#define MAX_S 1600
#define WORDS ((MAX_S + 63) / 64)

int main(){
    int n;
    scanf("%d", &n);
    int l[n];
    int S = 0;
    for(int i=0;i<n;i++){
        scanf("%d", &l[i]);
        S += l[i];
    }
    // Initialize DP
    ull dp[MAX_S +1][WORDS];
    memset(dp, 0, sizeof(dp));
    dp[0][0] |= 1ULL;
    // Shift left function
    // Shift src by shift bits, store in dest
    // Assumes dest is already zeroed
    // shift <= 64
    // Implemented inside the loop
    for(int i=0;i<n;i++){
        int plank = l[i];
        for(int a=S; a>=0; a--){
            // Check if dp[a] has any bit set
            int has = 0;
            for(int w=0; w<WORDS; w++) {
                if(dp[a][w]) { has =1; break;}
            }
            if(!has) continue;
            // Assign to group A
            if(a + plank <= S){
                for(int w=0; w<WORDS; w++){
                    dp[a + plank][w] |= dp[a][w];
                }
            }
            // Assign to group B by shifting left plank bits
            ull temp[WORDS];
            memset(temp, 0, sizeof(temp));
            int shift_bits = plank;
            int shift_words = shift_bits / 64;
            int rem_bits = shift_bits % 64;
            for(int w=WORDS-1; w>=0; w--){
                if(w < shift_words) continue;
                temp[w] |= dp[a][w - shift_words] << rem_bits;
                if(rem_bits !=0 && (w - shift_words -1) >=0){
                    temp[w] |= dp[a][w - shift_words -1] >> (64 - rem_bits);
                }
            }
            for(int w=0; w<WORDS; w++){
                dp[a][w] |= temp[w];
            }
        }
    }
    double max_area = 0.0;
    for(int a=1; a<=S-2; a++){
        for(int w=0; w<WORDS; w++){
            ull bits = dp[a][w];
            if(bits ==0) continue;
            int base = w * 64;
            while(bits){
                ull t = bits & -bits;
                int bit_pos = __builtin_ctzll(bits);
                int b = base + bit_pos;
                bits ^= t;
                if(b <1 || b > S -a -1) continue;
                int c = S - a - b;
                if(a + b > c && a + c > b && b + c > a){
                    double s = (a + b + c) / 2.0;
                    double area_sq = s * (s -a) * (s -b) * (s -c);
                    if(area_sq < 0.0) continue;
                    double area = sqrt(area_sq);
                    if(area > max_area){
                        max_area = area;
                    }
                }
            }
        }
    }
    if(max_area ==0.0){
        printf("-1\n");
    }
    else{
        long long result = (long long)(floor(max_area * 100.0 + 1e-6));
        printf("%lld\n", result);
    }
    return 0;
}