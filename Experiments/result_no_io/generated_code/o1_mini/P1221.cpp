#include <stdio.h>

typedef struct {
    long long number;
    int divisors;
} HCNumber;

int main(){
    long long L, U;
    scanf("%lld %lld", &L, &U);
    
    HCNumber hc[] = {
        {1, 1}, {2, 2}, {4, 3}, {6, 4}, {12, 6}, {24, 8},
        {36, 9}, {48, 10}, {60, 12}, {120, 16}, {180, 18},
        {240, 20}, {360, 24}, {720, 30}, {840, 32}, {1260, 36},
        {1680, 40}, {2520, 48}, {5040, 60}, {7560, 64},
        {10080, 72}, {15120, 80}, {20160, 84}, {25200, 90},
        {27720, 96}, {45360, 100}, {50400, 108}, {55440, 120},
        {83160, 128}, {110880, 144}, {166320, 160}, {221760, 180},
        {277200, 192}, {332640, 224}, {498960, 240}, {554400, 288},
        {665280, 300}, {720720, 320}, {1081080, 384}, {1441440, 448},
        {2162160, 480}, {2882880, 576}, {3603600, 640}, {4324320, 768},
        {6486480, 896}, {7207200, 960}, {8648640, 1152}, {10810800, 1344},
        {14414400, 1536}, {17297280, 1792}, {21621600, 2048},
        {32432400, 2304}, {36756720, 2688}, {43243200, 3072},
        {61261200, 3456}, {73513440, 4032}, {110270160, 4608},
        {122522400, 5376}, {147026880, 6144}, {183783600, 6912},
        {245044800, 7680}, {294053760, 9216}, {367567200, 10240},
        {551350800, 12288},
        // Add more if necessary up to 1e9
    };
    int hc_size = sizeof(hc)/sizeof(hc[0]);
    
    long long P = 0;
    int D = 0;
    for(int i=0;i<hc_size;i++){
        if(hc[i].number < L) continue;
        if(hc[i].number > U) break;
        if(hc[i].divisors > D){
            D = hc[i].divisors;
            P = hc[i].number;
        }
        else if(hc[i].divisors == D && hc[i].number < P){
            P = hc[i].number;
        }
    }
    
    if(P == 0){
        // If no highly composite number in range, find smallest number in range
        P = L;
        // Calculate number of divisors for P
        int maxD = 0;
        for(long long n = L; n <= U && n - L < 1000000; n++){ // limit to 1e6 for performance
            int cnt = 0;
            for(long long d=1; d*d<=n; d++){
                if(n%d == 0){
                    cnt++;
                    if(d != n/d) cnt++;
                }
            }
            if(cnt > maxD){
                maxD = cnt;
                P = n;
            }
            else if(cnt == maxD && n < P){
                P = n;
            }
        }
        // Recount divisors
        D = 0;
        for(long long d=1; d*d<=P; d++){
            if(P%d == 0){
                D++;
                if(d != P/d) D++;
            }
        }
    }
    
    printf("Between %lld and %lld, %lld has a maximum of %d divisors.\n", L, U, P, D);
    return 0;
}