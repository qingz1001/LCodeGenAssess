#include <stdio.h>
#include <math.h>
#include <stdint.h>

#define MAX_K 60
#define PRECISION 1e-18

int main(){
    int T;
    scanf("%d", &T);
    
    // Precomputed Zeta function values for k=2 to k=60
    // Values obtained from mathematical tables
    double zeta_vals[MAX_K+1];
    zeta_vals[2] = 1.6449340668482264;
    zeta_vals[3] = 1.2020569031595942;
    zeta_vals[4] = 1.0823232337111381;
    zeta_vals[5] = 1.0369277551433699;
    zeta_vals[6] = 1.0173430619844491;
    zeta_vals[7] = 1.0083492773819236;
    zeta_vals[8] = 1.0040773561979443;
    zeta_vals[9] = 1.0020083928260822;
    zeta_vals[10] = 1.0009945751278181;
    zeta_vals[11] = 1.0004941886041195;
    zeta_vals[12] = 1.0002460865533082;
    zeta_vals[13] = 1.0001227133475785;
    zeta_vals[14] = 1.0000612481350587;
    zeta_vals[15] = 1.0000305882363075;
    zeta_vals[16] = 1.0000152822594084;
    zeta_vals[17] = 1.0000076336764483;
    zeta_vals[18] = 1.0000038164559637;
    zeta_vals[19] = 1.0000019082127165;
    zeta_vals[20] = 1.0000009544675087;
    for(int k=21; k<=MAX_K; k++) {
        // For k >=21, zeta(k) approaches 1
        // Using zeta(k) ≈ 1 + 1/(2^k) for approximation
        zeta_vals[k] = 1.0 + 1.0 / pow(2.0, k);
    }
    
    while(T--){
        unsigned long long n;
        scanf("%llu", &n);
        double sum = 0.0;
        
        for(int k=2; k<=MAX_K; k++){
            // Compute m_k = floor(n^(1/k))
            double mk_f = pow((double)n, 1.0 / (double)k);
            unsigned long long mk = (unsigned long long)(mk_f + PRECISION);
            
            if(mk < 2) continue;
            
            // Compute pow(mk, k-1) and pow(mk, k) carefully to avoid overflow
            double mk_km1 = pow((double)mk, (double)(k-1));
            double mk_k = mk_km1 * mk;
            
            // Compute the tail approximation: 1/((k-1)*mk^(k-1)) + 1/(2*mk^k)
            double tail = 1.0 / ((double)(k-1) * mk_km1) + 1.0 / (2.0 * mk_k);
            
            // Add the contribution for this k
            sum += zeta_vals[k] - 1.0 - tail;
        }
        
        // Print the result with 14 decimal places
        printf("%.14lf\n", sum);
    }
    
    return 0;
}