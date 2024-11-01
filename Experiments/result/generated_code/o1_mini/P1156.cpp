#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int T;
    int F;
    int H;
} Garbage;

// Comparison function for sorting by T
int compare(const void *a, const void *b){
    Garbage *ga = (Garbage *)a;
    Garbage *gb = (Garbage *)b;
    if(ga->T != gb->T){
        return ga->T - gb->T;
    }
    return 0;
}

int main(){
    int D, G;
    scanf("%d %d", &D, &G);
    Garbage garb[100];
    for(int i=0;i<G;i++){
        scanf("%d %d %d", &garb[i].T, &garb[i].F, &garb[i].H);
    }
    qsort(garb, G, sizeof(Garbage), compare);
    // Initialize dp
    // dp[h] = max deadline
    // h from 0 to D
    long long INF = 1e9;
    int dp_current[D+1];
    for(int i=0;i<=D;i++) dp_current[i] = -1;
    dp_current[0] = 10;
    long long escape_time_min = INF;
    long long survival_max = 0;
    for(int i=0;i<G;i++){
        int T = garb[i].T;
        int F = garb[i].F;
        int H = garb[i].H;
        int dp_new[D+1];
        for(int j=0; j<=D; j++) dp_new[j] = -1;
        for(int h=0; h<=D; h++){
            if(dp_current[h]==-1) continue;
            int deadline = dp_current[h];
            if(T > deadline){
                if(deadline > survival_max){
                    survival_max = deadline;
                }
                continue;
            }
            // Option 1: Pile
            int new_h = h + H;
            if(new_h >= D){
                if(T < escape_time_min){
                    escape_time_min = T;
                }
            }
            else{
                if(new_h <= D && dp_new[new_h] < deadline){
                    dp_new[new_h] = deadline;
                }
            }
            // Option 2: Eat
            int new_deadline = deadline + F;
            if(h <= D && dp_new[h] < new_deadline){
                dp_new[h] = new_deadline;
            }
        }
        // Update dp_current
        for(int j=0; j<=D; j++) dp_current[j] = dp_new[j];
    }
    // After all garbage, check survival
    for(int h=0; h<=D; h++){
        if(dp_current[h] != -1){
            if(dp_current[h] > survival_max){
                survival_max = dp_current[h];
            }
        }
    }
    if(escape_time_min != INF){
        printf("%d\n", (int)escape_time_min);
    }
    else{
        printf("%d\n", (int)survival_max);
    }
    return 0;
}